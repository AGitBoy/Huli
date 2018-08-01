#include <iostream>
#include "Tabs.h"
#include "WebPage.h"

Tabs::Tabs(QWebEngineProfile* profile): QTabWidget(), myProfile(profile), tabRow(new TabBar(this)) {
	setTabBar(tabRow);
	
	setElideMode(Qt::ElideRight);
	setDocumentMode(true);
	setTabsClosable(true);
	
	if(myProfile->isOffTheRecord()) {
		qDebug() << "Private Browsing Mode On" << "\n";
	}
	
	connect(
		tabRow->addTabButton, &QPushButton::clicked,
		[this](bool) { newTab(); }
	);
	
	connect(
		this, &QTabWidget::tabCloseRequested,
		this, &Tabs::removeTabRequest
	);
	
	connect(
		this, &QTabWidget::currentChanged,
		this, &Tabs::changedHandler
	);
	
	previous = newTab();
};

WebView* Tabs::getWebViewFromSender(QObject* senderObj) {
	return dynamic_cast<WebView*>(senderObj);
}

void Tabs::fullScreenRequest(bool on) {
	hideTabBar(on);
}

WebView* Tabs::newTab(QString str) {
	WebView* view = makeTab(str);
	setCurrentWidget(view);
	return view;
};

void Tabs::hideTabBar(bool on) {
	on ? tabBar()->hide() : tabBar()->show();
}

void Tabs::removeTabRequest(int index) {
	removeTab(index);
	if(count() > 0) {
		if(index == currentIndex()) {
			setCurrentIndex(0);
		}
	} else {
		window()->close();
	}
};

void Tabs::changedHandler(int index) {
	if(index != -1) {
		if(previous != nullptr && previous->fullScreen) {
			previous->triggerPageAction(QWebEnginePage::ExitFullScreen);
		}
		updateWindowTitle();
		previous = getView(index);
	}
}

WebView* Tabs::getView(int index) {
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wincompatible-pointer-types"
	#pragma ide diagnostic ignored "CannotResolve"
	return qobject_cast<ViewContainer*>(widget(index))->view;
	#pragma clang diagnostic pop
}

void Tabs::viewTitleUpdate(QString title) {
	int index = indexOfWebView(getWebViewFromSender(sender()));
	setTabText(index, title);
	
	updateWindowTitle();
}

void Tabs::viewIconUpdate(QIcon icon) {
	int index = indexOfWebView(getWebViewFromSender(sender()));
	
	setTabIcon(index, icon);
}

void Tabs::updateWindowTitle() {
	QString title = myProfile->isOffTheRecord() ? QString("Huli <%1>").arg(tr("Private Browsing")) : "Huli";
	
	if(getView(currentIndex())->title().isEmpty() || getView(currentIndex())->title().isNull()) {
		window()->setWindowTitle(title);
	} else {
		auto fmtStr = QString("%1 - %2");
		window()->setWindowTitle(fmtStr.arg(getView(currentIndex())->title(), title));
	}
	
}

int Tabs::indexOfWebView(WebView* w) {
	for(int i = 0; i < count(); ++i) {
		if(w == dynamic_cast<ViewContainer*>(widget(i))->view) {
			return i;
		}
	}
	return -1;
}

WebView* Tabs::makeTab(QString input) {
	auto* view(new WebView(myProfile));
	
	auto* container(new ViewContainer(view));
	int i = addTab(container, view->title());
	
	view->load(QUrl(input));
	
	connect(
		view, &QWebEngineView::titleChanged,
		this, &Tabs::viewTitleUpdate
	);
	
	connect(
		view, &QWebEngineView::iconChanged,
		this, &Tabs::viewIconUpdate
	);
	
	connect(
		view, &BrowserBase::fullScreenRequested,
		this, &Tabs::fullScreenRequest
	);
	
	return view;
}

WebView* Tabs::newBackgroundTab(QString str) {
	return makeTab(str);
}
