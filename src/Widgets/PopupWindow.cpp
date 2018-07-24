#include "PopupWindow.h"

PopupWindow::PopupWindow(QWebEngineProfile* profile)
	: QWidget(), view(new QWebEngineView(this)), urlBar(new QLineEdit(this)), favicon(new QAction(this)),
	  exitFullScreenAction(new QAction(this)) {
	auto* layout = new QVBoxLayout;
	setLayout(layout);
	
	setAttribute(Qt::WA_DeleteOnClose);
	
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(urlBar);
	layout->addWidget(view);

	urlBar->setReadOnly(true);
	urlBar->addAction(favicon, QLineEdit::LeadingPosition);
	
	view->setPage(new QWebEnginePage(profile, view));
	view->setFocus();
	
	view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
	
	exitFullScreenAction->setShortcut(Qt::Key_Escape); // Press escape when fullscreen to exit fullscreen
	exitFullScreenAction->setDisabled(isFullScreen());
	
	connect(
		exitFullScreenAction, &QAction::triggered,
		[this](bool) { view->triggerPageAction(QWebEnginePage::ExitFullScreen); }
	);
	
	connect(
		this->view->page(), SIGNAL(fullScreenRequested(QWebEngineFullScreenRequest)),
		this, SLOT(fullScreenRequest(QWebEngineFullScreenRequest))
	);
	
	connect(
		view, &QWebEngineView::titleChanged,
		this, &QWidget::setWindowTitle
	);
	
	connect(
		view, &QWebEngineView::urlChanged,
		[this](const QUrl &url) { urlBar->setText(url.toDisplayString()); } // Prettify url?
	);
	
	connect(
		view, &QWebEngineView::iconChanged,
		favicon, &QAction::setIcon
	);
	
	connect(
		view->page(), &QWebEnginePage::geometryChangeRequested,
		this, &PopupWindow::handleGeometryChangeRequested
	);
	
	connect(
		view->page(), &QWebEnginePage::windowCloseRequested,
		this, &QWidget::close
	);
	
}

void PopupWindow::fullScreenRequest(QWebEngineFullScreenRequest request) {
	if(request.toggleOn()) {
		// Hides urlBar and makes webview fullscreen
		// Probably not the best way to do this
		urlBar->hide();
		view->showFullScreen();
		showFullScreen();
		// todo: add fullscreen notification
		exitFullScreenAction->setDisabled(false);
	} else {
		// Returns to normal
		urlBar->show();
		showNormal();
		exitFullScreenAction->setDisabled(true);
	}
	request.accept(); // Are there any cases in which we want to reject this request? Maybe check for focus?
}

// I forget what this does and I'm scared to touch it.
void PopupWindow::handleGeometryChangeRequested(const QRect &newGeometry) {
	if(QWindow* window = windowHandle()) {
		setGeometry(newGeometry.marginsRemoved(window->frameMargins()));
	}
	
	show();
	view->setFocus();
}
