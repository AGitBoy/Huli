#ifndef HULI_WEBVIEW_H
#define HULI_WEBVIEW_H

#include <QtCore>
#include <QtWebEngineWidgets>
#include "WebPage.h"
#include "BrowserBase.h"

// Main Web Browser Tabs
class WebView: public BrowserBase {
	Q_OBJECT;

	public:
		explicit WebView(QWebEngineProfile* profile);

	public slots:
		void contextMenuEvent(QContextMenuEvent* event) override;

	private:
		QWebEngineView* newTab() override;
		QWebEngineView* newBackgroundTab() override;
};

#endif