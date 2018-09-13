#include <QtWidgets>
#include <QtNetwork>
#include "PopupObject.h"
#include "GoogleProvider.h"
#include "DuckDuckGoProvider.h"
#include "AddressBarInput.h"
#include "AddressBar.h"
#include "iconProvider.h"

PopupObject::PopupObject(AddressBarInput* editor): QObject(editor), editor(editor),
                                                   provider(Config::getProvider(Config::getCurrentEngine())) {
	
	popup = new QTreeWidget;
	popup->setWindowFlags(Qt::Popup);
	popup->setFocusPolicy(Qt::NoFocus);
	popup->setFocusProxy(editor);
	popup->setMouseTracking(true);
	
	popup->setColumnCount(2);
	popup->setUniformRowHeights(true);
	popup->setRootIsDecorated(false);
	popup->setEditTriggers(QTreeWidget::NoEditTriggers);
	popup->setSelectionBehavior(QTreeWidget::SelectRows);
	popup->setFrameStyle(QFrame::NoFrame);
	
	popup->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	popup->header()->hide();
	
	popup->installEventFilter(this);
	
	connect(
		popup, &QTreeWidget::itemClicked,
		this, &PopupObject::doneCompletion
	);
	
	timer.setSingleShot(true);
	timer.setInterval(500);
	
	connect(
		&timer, &QTimer::timeout,
		this, &PopupObject::suggest
	);
	
	connect(
		editor, SIGNAL(textEdited(QString)),
		&timer, SLOT(start())
	);
	
	connect(
		&networkManager, &QNetworkAccessManager::finished,
		this, &PopupObject::handleNetworkData
	);
}

PopupObject::~PopupObject() {
	delete popup;
}

bool PopupObject::eventFilter(QObject* obj, QEvent* event) {
	if(obj != popup) {
		return false;
	}
	
	if(event->type() == QEvent::MouseButtonPress) {
		auto mouseEvent = static_cast<QMouseEvent*>(event); // NOLINT
		if(popup->rect().contains(mouseEvent->pos())) { // Check if mouse is hovering popup or not
			popup->hide();
			editor->setFocus();
			editor->bar->search();
			return true;
		} else {
			timer.stop();
			popup->hide();
			return false;
		}
	}
	
	if(event->type() == QEvent::KeyPress) {
		bool consumed = false;
		int key = static_cast<QKeyEvent*>(event)->key(); // NOLINT
		
		switch(key) {
			case Qt::Key_Enter:
			case Qt::Key_Return:
				doneCompletion();
				consumed = true;
				
				break;
			
			case Qt::Key_Escape:
				editor->setFocus();
				popup->hide();
				consumed = true;
				
				break;
			
			case Qt::Key_Up:
			case Qt::Key_Down:
			case Qt::Key_Home:
			case Qt::Key_End:
			case Qt::Key_PageUp:
			case Qt::Key_PageDown:
				break;
			
			default:
				editor->setFocus();
				editor->event(event);
				popup->hide();
				
				break;
		}
		return consumed;
	}
	return false;
}

void PopupObject::showCompletion(QVector<suggestion> choices) {
	if(editor->text().isEmpty() || editor->text().isNull()) {
		return;
	}
	
	popup->setFixedWidth(editor->width());
	
	popup->setUpdatesEnabled(false);
	forcedSearchItem = nullptr;
	popup->clear();
	
	
	auto SearchSeparatorItem = new QTreeWidgetItem(popup);
	SearchSeparatorItem->setDisabled(true);
	
	SearchSeparatorItem
		->setText(0, tr("Search %1").arg(Config::getCurrentEngine()->name));
	
	auto searchItem = new QTreeWidgetItem(popup);
	forcedSearchItem = searchItem;
	searchItem->setText(0, editor->text());
	searchItem->setIcon(0, iconProvider::getSearchIcon());
	
	if(!choices.isEmpty()) {
		auto SuggestionSeparatorItem = new QTreeWidgetItem(popup);
		SuggestionSeparatorItem->setDisabled(true);
		SuggestionSeparatorItem->setText(0, "Suggestions");
		
		// Truncates to 5
		for(int i = 0; i < choices.length() && i < Config::getSuggestionTruncateLength(); ++i) {
			auto item = new QTreeWidgetItem(popup);
			item->setText(0, choices[i].text);
			item->setToolTip(0, choices[i].text);
			
			item->setText(1, choices[i].snippet);
			item->setTextColor(1, editor->palette().color(QPalette::Disabled, QPalette::Text));
			item->setToolTip(1, choices[i].snippet);
			
			item->setIcon(0, choices[i].icon);
		}
	}
	
	// TODO: Add bookmarks section
	// TODO: Add history section
	
	popup->setCurrentItem(popup->topLevelItem(0));
	
	double firstColumnWidthPercent = .60;
	popup->setColumnWidth(0, static_cast<int>(editor->width() * firstColumnWidthPercent));
	
	popup->setUpdatesEnabled(true);
	popup->move(editor->mapToGlobal(QPoint(0, editor->height())));
	
	popup->setFocus();
	
	popup->show();
}


void PopupObject::doneCompletion() {
	timer.stop();
	
	popup->hide();
	
	QTreeWidgetItem* item = popup->currentItem();
	
	if(item && item != forcedSearchItem) {
		editor->setText(item->text(0));
		editor->bar->search();
	} else if(item && item == forcedSearchItem) {
		editor->setText(item->text(0));
		editor->bar->searchForce();
	}
}

void PopupObject::suggest() {
	networkManager.get(QNetworkRequest(QUrl(provider->getFmtUrl(editor->text()))));
}

void PopupObject::handleNetworkData(QNetworkReply* reply) {
	QVector<suggestion> choices = provider->getSuggestions(reply);
	showCompletion(choices);
	reply->deleteLater();
}
