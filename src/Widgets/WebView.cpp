#include "WebView.h"
#include "Tabs.h"
#include "Window.h"
#include "PopupWindow.h"

WebView::WebView(Tabs* tab): QWebEngineView() {
	tabs = tab;
	
	connect(
		this, &QWebEngineView::loadFinished,
		this, &WebView::changedSlot
	);
	
	connect(
		this, &QWebEngineView::titleChanged,
		[this](QString) { emit changed(this); }
	);
	
	connect(
		this, &QWebEngineView::iconChanged,
		[this](QIcon) { emit changed(this); }
	);
	
	connect(
		this, &WebView::changed,
		tabs, &Tabs::updateTab
	);
	
	connect(
		this, &QWebEngineView::loadStarted,
		this, &WebView::loadStartSlot
	);
	
	connect(
		this->page(), SIGNAL(fullScreenRequested(QWebEngineFullScreenRequest)),
		this, SLOT(fullScreenRequest(QWebEngineFullScreenRequest))
	);
	
	connect(
		this, &QWebEngineView::renderProcessTerminated,
		this, &WebView::renderProcessTerminatedHandler
	);
	
	exitFullScreen.setShortcut(Qt::Key_Escape);
	
	connect(
		&exitFullScreen, &QAction::triggered,
		[this](bool) { triggerPageAction(QWebEnginePage::ExitFullScreen); }
	);
	
	addAction(&exitFullScreen);
	
}

void WebView::changedSlot(bool) {
	setCursor(Qt::ArrowCursor);
	emit changed(this);
}

void WebView::loadStartSlot() {
	this->setCursor(Qt::WaitCursor);
}

void WebView::fullScreenRequest(QWebEngineFullScreenRequest request) {
	emit fullScreenRequested(request.toggleOn());
	if(request.toggleOn()) {
		tabs->hideTabBar(true);
		exitFullScreen.setDisabled(false);
		showFullScreen();
		window()->showFullScreen();
		fullScreen = true;
	} else {
		tabs->hideTabBar(false);
		showNormal();
		window()->showNormal();
		exitFullScreen.setDisabled(true);
		fullScreen = false;
	}
	request.accept();
}

QWebEngineView* WebView::createWindow(QWebEnginePage::WebWindowType type) {
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wincompatible-pointer-types"
	Window* mainWindow = qobject_cast<Window*>(window()); // NOLINT
	#pragma clang diagnostic pop
	if(!mainWindow) {
		return nullptr;
	}
	
	switch(type) {
		case QWebEnginePage::WebBrowserTab: {
			return mainWindow->tabs->newTab();
		}
		case QWebEnginePage::WebBrowserBackgroundTab: {
			WebView* tab = mainWindow->tabs->newTab();
			mainWindow->tabs->setCurrentIndex(this->index);
			return tab;
		}
		case QWebEnginePage::WebDialog: {
			auto dialog = new PopupWindow(page()->profile());
			return dialog->view;
		}
		case QWebEnginePage::WebBrowserWindow: {
			auto newWindow = new Window();
			newWindow->setWindowTitle("Huli");
			newWindow->show();
			
			return newWindow->tabs->tabList[newWindow->tabs->currentIndex()];
		}
		default: {
			return QWebEngineView::createWindow(type);
		}
	}
}

void WebView::renderProcessTerminatedHandler(QWebEnginePage::RenderProcessTerminationStatus terminationStatus,
                                             int statusCode) {
	QString statusMessage;
	switch(terminationStatus) {
		case QWebEnginePage::NormalTerminationStatus:
			statusMessage = "Render process normal exit";
			break;
		
		case QWebEnginePage::AbnormalTerminationStatus:
			statusMessage = "Render process abnormal exit";
			break;
		
		case QWebEnginePage::CrashedTerminationStatus:
			statusMessage = "Render process crash";
			break;
		
		case QWebEnginePage::KilledTerminationStatus:
			statusMessage = "Render process killed";
			break;
	}
	
	QMessageBox::StandardButton btn = QMessageBox::question(
		window(),
		statusMessage,
		tr("Render process has crashed with exit code: %1\nReload the page?").arg(statusCode)
	);
	
	if(btn == QMessageBox::Yes) {
		QTimer::singleShot(0, [this] { reload(); });
	}
}

void WebView::contextMenuEvent(QContextMenuEvent* event) {
	QMenu* menu = page()->createStandardContextMenu();
	const QList<QAction*> actions = menu->actions();
	
	auto inspectElement = std::find(actions.cbegin(), actions.cend(), page()->action(QWebEnginePage::InspectElement));
	
	if(inspectElement == actions.cend()) {
		auto viewSource = std::find(actions.cbegin(), actions.cend(), page()->action(QWebEnginePage::ViewSource));
		if(viewSource == actions.cend()) {
			menu->addSeparator();
		}
		
		auto* action = new QAction(menu);
		action->setText("Open inspector in new window");
		
		connect(
			action, &QAction::triggered,
			[this](bool) { openDevTools(); }
		);
		
		QAction* before(inspectElement == actions.cend() ? nullptr : *inspectElement);
		menu->insertAction(before, action);
	} else {
		(*inspectElement)->setText(tr("Inspect element"));
	}
	menu->popup(event->globalPos());
}

void WebView::openDevTools() {
	auto devToolsWindow = new QWebEngineView();
	devToolsWindow->setAttribute(Qt::WA_DeleteOnClose);
	
	page()->setDevToolsPage(devToolsWindow->page());
	devToolsWindow->show();
	page()->triggerAction(QWebEnginePage::InspectElement);
}

