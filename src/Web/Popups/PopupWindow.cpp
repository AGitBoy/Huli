#include "PopupWindow.h"

PopupWindow::PopupWindow(QWebEngineProfile* profile)
	: QWidget(), view(new PopupWebView(profile)), urlBar(new QLineEdit(this)), favicon(new QAction(this)) {
	auto* layout = new QVBoxLayout;
	setLayout(layout);
	
	setAttribute(Qt::WA_DeleteOnClose);
	
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(urlBar);
	layout->addWidget(view);
	
	urlBar->setReadOnly(true);
	urlBar->addAction(favicon, QLineEdit::LeadingPosition);
	
	view->setFocus();
	
	connect(
		this->view, SIGNAL(fullScreenRequested(bool)),
		this, SLOT(fullScreenRequest(bool))
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

void PopupWindow::fullScreenRequest(bool on) {
	if(on) {
		// Hides urlBar
		urlBar->hide();
		showFullScreen();
		// todo: add fullscreen notification
	} else {
		// Returns to normal
		urlBar->show();
		showNormal();
	}
}

// I forget what this does and I'm scared to touch it.
void PopupWindow::handleGeometryChangeRequested(const QRect &newGeometry) {
	if(QWindow* window = windowHandle()) {
		setGeometry(newGeometry.marginsRemoved(window->frameMargins()));
	}
	
	show();
	view->setFocus();
}
