#include "AddressBar.h"
#include "AddressBarInput.h"
#include "ViewContainer.h"
#include "urlValidation.h"
#include "Config.h"
#include "iconProvider.h"
#include "AddressBarLayoutLoader.h"

AddressBar::AddressBar(ViewContainer* container)
	: QWidget(), HBox(new QHBoxLayout()), view(container) {
	setMaximumHeight(200);
	WebView* webView = container->view;
	
	
	QVector<layoutItems> layout = AddressBarLayoutLoader::getLayout();
	
	for(int i = 0; i < layout.length(); ++i) { // NOLINT
		switch(layout[i]) {
			case layoutItems::Back: {
				auto* back = new QPushButton(this);
				back->setIcon(iconProvider::getBackIcon());
				
				connect(
					back, &QPushButton::clicked,
					webView, &QWebEngineView::back
				);
				
				HBox->addWidget(back);
				
				break;
			}
			case layoutItems::Forward: {
				auto* nextButton = new QPushButton(this); // Forward navigational button
				nextButton->setIcon(iconProvider::getForwardIcon());
				
				connect(
					nextButton, &QPushButton::clicked,
					webView, &QWebEngineView::forward
				);
				HBox->addWidget(nextButton);
				
				break;
			}
			case layoutItems::Reload: {
				auto* reloadButton = new QPushButton(this); // Reload page navigation button
				reloadButton->setIcon(iconProvider::getReloadIcon());
				
				connect(
					reloadButton, &QPushButton::clicked,
					webView, &QWebEngineView::reload
				);
				
				HBox->addWidget(reloadButton);
				
				break;
			}
			case layoutItems::UrlBar: {
				auto* input = new AddressBarInput(this); // Points to the text input
				
				connect(
					webView, &QWebEngineView::urlChanged,
					[this, input](QUrl url) { input->setText(url.toString()); }
				);
				connect(
					input, &AddressBarInput::search,
					this, &AddressBar::searchFromInput
				);
				
				HBox->addWidget(input);
				
				break;
			}
			case layoutItems::Downloads: {
				auto* downloadsButton = new QPushButton(this);
				downloadsButton->setIcon(iconProvider::getDownloadIcon());
				
				auto* manager = new DownloadManager(downloadsButton);
				
				connect(
					downloadsButton, &QPushButton::clicked,
					manager, &DownloadManager::toggleHidden
				);
				
				connect(
					webView->page()->profile(), &QWebEngineProfile::downloadRequested,
					manager, &DownloadManager::downloadRequested
				);
				
				HBox->addWidget(downloadsButton);
				break;
			}
			default: {
				break;
			}
		}
	}
	
	connect(
		webView, &WebView::fullScreenRequested,
		this, &AddressBar::hider
	);

	setLayout(HBox);
};

void AddressBar::urlChange(QUrl url) {
};

void AddressBar::hider(bool on) {
	if(on) {
		hide();
	} else {
		show();
	}
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