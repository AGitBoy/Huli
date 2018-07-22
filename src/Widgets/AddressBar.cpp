#include <iostream>
#include "src/Widgets/AddressBar.h"
#include "src/Widgets/AddressBarInput.h"
#include "src/Widgets/ViewContainer.h"
#include "src/Util/urlValidation.h"

AddressBar::AddressBar(ViewContainer* container)
	: QWidget(), HBox(new QHBoxLayout()), input(new AddressBarInput(this)), view(container) {
	setMaximumHeight(200);
	
	WebView* webView = view->view;
	
	backButton.setIcon(
		QIcon::fromTheme(
			"go-previous",
			QIcon(":/res/icons/actions/arrow-left.svg")
		)
	);
	
	nextButton.setIcon(
		QIcon::fromTheme(
			"go-next",
			QIcon(":/res/icons/actions/arrow-right.svg")
		)
	);
	
	reloadButton.setIcon(
		QIcon::fromTheme(
			"view-refresh",
			QIcon(":/res/icons/actions/refresh.svg")
		)
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
	
	setLayout(HBox);
};

void AddressBar::urlChange(QUrl url) {
	input->setText(url.toString());
};

void AddressBar::search() {
	searchFromInput(input->text());
}

void AddressBar::hider(bool on) {
	on ? hide() : show();
}

void AddressBar::searchForce() {
	searchForce(input->text());
}

void AddressBar::searchForce(const QString &query) {
	QString search = "https://www.duckduckgo.com/?q=%1"; // todo: load from config
	view->view->load(search.arg(query));
}

void AddressBar::searchFromInput(const QString &query) {
	QString search = "https://www.duckduckgo.com/?q=%1"; // todo: load from config
	if(urlValidation(query)) {
		view->view->load(query);
	} else {
		view->view->load(search.arg(query));
	}
};