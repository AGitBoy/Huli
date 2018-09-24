#include "AddressBar.h"
#include "AddressBarInput.h"
#include "ViewContainer.h"
#include "urlValidation.h"
#include "Config.h"
#include "iconProvider.h"

AddressBar::AddressBar(ViewContainer* container)
	: QWidget(), HBox(new QHBoxLayout()), input(new AddressBarInput(this)), view(container),
	  manager(new DownloadManager(this)) {
	setMaximumHeight(200);
	WebView* webView = view->view;
	
	backButton.setIcon(iconProvider::getBackIcon());
	
	nextButton.setIcon(iconProvider::getForwardIcon());
	
	reloadButton.setIcon(iconProvider::getReloadIcon());
	
	downloadsButton.setIcon(iconProvider::getDownloadIcon());
	
	connect(
		webView->page()->profile(), &QWebEngineProfile::downloadRequested,
		manager, &DownloadManager::downloadRequested
	);
	
	connect(
		&downloadsButton, &QPushButton::clicked,
		manager, &DownloadManager::toggleHidden
	);
	
	connect(
		&backButton, &QPushButton::clicked,
		webView, &QWebEngineView::back
	);
	
	connect(
		&nextButton, &QPushButton::clicked,
		webView, &QWebEngineView::forward
	);
	
	connect(
		&reloadButton, &QPushButton::clicked,
		webView, &QWebEngineView::reload
	);
	
	connect(
		webView, &QWebEngineView::urlChanged,
		this, &AddressBar::urlChange
	);
	
	connect(
		webView, &WebView::fullScreenRequested,
		this, &AddressBar::hider
	);
	
	connect(
		input, &QLineEdit::returnPressed,
		this, &AddressBar::search
	);
	
	HBox->addWidget(&backButton);
	HBox->addWidget(&nextButton);
	HBox->addWidget(&reloadButton);
	HBox->addWidget(input);
	HBox->addWidget(&downloadsButton);
	
	setLayout(HBox);
};

void AddressBar::urlChange(QUrl url) {
	input->setText(url.toString());
};

void AddressBar::search() {
	searchFromInput(input->text());
}

void AddressBar::hider(bool on) {
	if(on) {
		hide();
	} else {
		show();
	}
}

void AddressBar::searchForce() {
	searchForce(input->text());
}

void AddressBar::searchForce(const QString &query) {
	QString search = Config::getCurrentEngine()->url;
	view->view->load(search.arg(query));
}

void AddressBar::searchFromInput(const QString &query) {
	QString search = Config::getCurrentEngine()->url;
	if(urlValidation(query)) {
		view->view->load(query);
	} else {
		view->view->load(search.arg(query));
	}
	view->setFocus();
};