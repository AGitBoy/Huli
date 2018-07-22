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
	
	exitFullScreenAction->setShortcut(Qt::Key_Escape);
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
		[this](const QUrl &url) { urlBar->setText(url.toDisplayString()); }
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
		urlBar->hide();
		view->showFullScreen();
		showFullScreen();
		exitFullScreenAction->setDisabled(false);
	} else {
		urlBar->show();
		showNormal();
		exitFullScreenAction->setDisabled(true);
	}
	request.accept();
}

void PopupWindow::handleGeometryChangeRequested(const QRect &newGeometry) {
	if(QWindow* window = windowHandle()) {
		setGeometry(newGeometry.marginsRemoved(window->frameMargins()));
	}
	
	show();
	view->setFocus();
}
