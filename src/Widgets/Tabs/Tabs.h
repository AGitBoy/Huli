#ifndef HULI_TABS_H
#define HULI_TABS_H

#include <QtWidgets>
#include <QtCore>

#include "WebView.h"
#include "ViewContainer.h"
#include "TabBar.h"
#include "Settings.h"

class Tabs: public QTabWidget {
    Q_OBJECT;

    public:
        explicit Tabs(QWebEngineProfile* profile = QWebEngineProfile::defaultProfile());
        
        QWebEngineProfile* myProfile;
        TabBar* tabRow;
        
        WebView* getView(int index);
        int indexOfWebView(WebView* w);

    private:
        void updateWindowTitle();
        WebView* makeTab(QString input);
        WebView* previous = nullptr;
        WebView* getWebViewFromSender(QObject* senderObj);

    public slots:
        WebView* newTab(const QString &str = Settings::getNewTabPage());
        WebView* newBackgroundTab(QString str = Settings::getNewTabPage());
        void hideTabBar(bool on);
        void removeTabRequest(int index);
        void changedHandler(int index);
        void fullScreenRequest(bool on);
        void viewTitleUpdate(QString title);
        void viewIconUpdate(QIcon icon);
};

#endif