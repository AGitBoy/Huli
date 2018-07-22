#include <iostream>
#include "Tabs.h"
#include "WebPage.h"

Tabs::Tabs(QWebEngineProfile* profile): QTabWidget(), myProfile(profile) {
	setElideMode(Qt::ElideRight);
	setDocumentMode(true);
	setTabsClosable(true);
	
	// Doesn't work with Kvantum styling engine
	setStyleSheet("QTabBar::tab { width: 150px; }");
	
	if(myProfile->isOffTheRecord()) {
		qDebug() << "Private Browsing Mode On" << "\n";
	}
	
	auto* addTabButton = new QPushButton();
	addTabButton->setIcon(QIcon::fromTheme("tab-new", QIcon(":/res/icons/actions/plus.svg")));
	
	// TODO: Make move next to last tab
	setCornerWidget(addTabButton);
	
	connect(
		addTabButton, &QPushButton::clicked,
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


WebView* Tabs::newTab(QString str) {
	auto* view(new WebView(this));
	auto* page = new WebPage(myProfile, view);
	
	view->setPage(page);
	
	auto* container(new ViewContainer(view));
	int i = addTab(container, view->title());
	
	view->index = i;
	tabList.append(view);
	updateTabList();
	
	view->load(QUrl(str));
	setCurrentIndex(view->index);
	
	return view;
};;

void Tabs::updateTabList() {
	for(auto i = 0; i < tabList.length(); i++) {
		if(tabList[i]->index != i) {
			tabList[i]->index = i;
		};
	};
};

void Tabs::updateTab(WebView* view) {
	setTabText(view->index, view->title());
	setTabIcon(view->index, view->icon());
	setTabToolTip(view->index, view->title());
	
	updateTabList();
	
	if(view->index == currentIndex()) {
		QString fmtStr = myProfile->isOffTheRecord() ? "%1 - Huli <Private Browsing>" : "%1 - Huli";
		window()->setWindowTitle(QString(fmtStr).arg(view->title()));
	};
}

void Tabs::hideTabBar(bool on) {
	on ? tabBar()->hide() : tabBar()->show();
}

void Tabs::removeTabRequest(int index) {
	removeTab(index);
	if(count() > 0) {
		if(index == currentIndex()) {
			setCurrentIndex(0);
		}
		tabList.removeAt(index);
		updateTabList();
	} else {
		window()->close();
	}
};

void Tabs::changedHandler(int index) {
	if(index != -1) {
		if(previous != nullptr && previous->fullScreen) {
			previous->triggerPageAction(QWebEnginePage::ExitFullScreen);
		}
		window()->setWindowTitle(QString("%1 - Huli").arg(tabText(index)));
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

