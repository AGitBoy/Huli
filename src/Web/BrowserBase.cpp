#include "BrowserBase.h"
#include "PopupWindow.h"
#include "Window.h"

BrowserBase::BrowserBase(QWebEngineProfile* profile)
	: QWebEngineView()
{
	auto webPage = new WebPage(profile, this);
	setPage(webPage);
	
	connect(
		page(), SIGNAL(fullScreenRequested(QWebEngineFullScreenRequest)),
		this, SLOT(fullScreenRequest(QWebEngineFullScreenRequest))
	);
	
	page()->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
	
	connect(
		this, &QWebEngineView::loadStarted,
		[this]() { setCursor(Qt::WaitCursor); }
	);
	
	connect(
		this, &QWebEngineView::loadFinished,
		[this](bool) { setCursor(Qt::ArrowCursor); }
	);
	
	connect(
		this, &QWebEngineView::renderProcessTerminated,
		this, &BrowserBase::renderProcessQuit
	);
	
	exitFullScreenAction.setShortcut(Qt::Key_Escape);
	
	connect(
		&exitFullScreenAction, &QAction::triggered,
		[this](bool) { triggerPageAction(QWebEnginePage::ExitFullScreen); }
	);
	
	addAction(&exitFullScreenAction);
	exitFullScreenAction.setDisabled(true);
}

QWebEngineView* BrowserBase::createWindow(QWebEnginePage::WebWindowType type) {
	switch(type) {
		case QWebEnginePage::WebBrowserTab: {
			return newTab();
		}
		case QWebEnginePage::WebBrowserBackgroundTab: {
			return newBackgroundTab();
		}
		case QWebEnginePage::WebDialog: {
			return newPopup();
		}
		case QWebEnginePage::WebBrowserWindow: {
			return newWindow();
		}
		default: {
			return QWebEngineView::createWindow(type);
		}
	}
}

void BrowserBase::fullScreenRequest(QWebEngineFullScreenRequest request) {
	bool on = request.toggleOn();
	
	emit fullScreenRequested(on);
	
	if(on) {
		windowGeometry = window()->geometry();
		showFullScreen();
		window()->showFullScreen();
		exitFullScreenAction.setDisabled(false);
	} else {
		exitFullScreenAction.setDisabled(true);
		showNormal();
		window()->showNormal();
	
		window()->setGeometry(windowGeometry);
	}
	request.accept();
}


void BrowserBase::renderProcessQuit(QWebEnginePage::RenderProcessTerminationStatus terminationStatus, int statusCode) {
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


#if QT_11_SUPPORT
void BrowserBase::openDevTools() {
	auto devToolsWindow = new QWebEngineView(); // TODO: Replace with subclass of BrowserBase
	devToolsWindow->setAttribute(Qt::WA_DeleteOnClose);
	
	devToolsWindow->show();
	page()->triggerAction(QWebEnginePage::InspectElement);
}
#endif


QWebEngineView* BrowserBase::newPopup() {
	auto dialog = new PopupWindow(page()->profile());
	return dialog->view;
}


QWebEngineView* BrowserBase::newWindow() {
	auto newWindow = new Window();
	newWindow->setWindowTitle("Huli");
	newWindow->show();
	
	return newWindow->tabs->getView(newWindow->tabs->currentIndex());
}

