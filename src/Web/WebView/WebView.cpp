#include "WebView.h"
#include "Window.h"

WebView::WebView(QWebEngineProfile* profile): BrowserBase(profile) { }

QWebEngineView* WebView::newTab() {
	Window* mainWindow = qobject_cast<Window*>(window()); // NOLINT
	if(!mainWindow) {
		return nullptr;
	}
	return mainWindow->tabs->newTab();
}

QWebEngineView* WebView::newBackgroundTab() {
	Window* mainWindow = qobject_cast<Window*>(window()); // NOLINT
	if(!mainWindow) {
		return nullptr;
	}
	
	WebView* tab = mainWindow->tabs->newBackgroundTab();

	return tab;
}

void WebView::contextMenuEvent(QContextMenuEvent* event) {
	QMenu* menu = page()->createStandardContextMenu();
	const QList<QAction*> actions = menu->actions();
	#if QT_11_SUPPORT
	auto inspectElement = std::find(actions.cbegin(), actions.cend(), page()->action(QWebEnginePage::InspectElement));
	
	if(inspectElement == actions.cend()) {
		auto viewSource = std::find(actions.cbegin(), actions.cend(), page()->action(QWebEnginePage::ViewSource));
		if(viewSource == actions.cend()) {
			menu->addSeparator();
		}
		
		auto* action = new QAction(menu);
		action->setText(tr("Inspect element"));
		
		connect(
			action, &QAction::triggered,
			[this](bool) { openDevTools(); }
		);
		
		QAction* before(inspectElement == actions.cend() ? nullptr : *inspectElement);
		menu->insertAction(before, action);
	} else {
		(*inspectElement)->setText(tr("Inspect element"));
	}
	#endif
	menu->popup(event->globalPos());
}
