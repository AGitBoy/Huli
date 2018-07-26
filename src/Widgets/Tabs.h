#ifndef HULI_TABS_H
#define HULI_TABS_H

#include <QtWidgets>
#include <QtCore>

#include "WebView.h"
#include "ViewContainer.h"
#include "TabBar.h"

class Tabs: public QTabWidget {
Q_OBJECT;

public:
	explicit Tabs(QWebEngineProfile* profile = QWebEngineProfile::defaultProfile());
	
	QList<WebView*> tabList;
	QWebEngineProfile* myProfile;
	TabBar* tabRow;
	
	void updateTabList();
	WebView* getView(int index);

private:
	WebView* previous = nullptr;

public slots:
	WebView* newTab(QString str = "https://start.duckduckgo.com/");
	void updateTab(WebView* view);
	void hideTabBar(bool on);
	void removeTabRequest(int index);
	void changedHandler(int index);
};

#endif