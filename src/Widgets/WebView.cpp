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
	
	settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
	exitFullScreen.setShortcut(Qt::Key_Escape);
	
	connect(
		&exitFullScreen, &QAction::triggered,
		[this](bool) { triggerPageAction(QWebEnginePage::ExitFullScreen); }
	);
	
	addAction(&exitFullScreen);
	
}

void WebView::changedSlot(bool ok) {
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


