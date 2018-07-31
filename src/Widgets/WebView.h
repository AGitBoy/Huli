#ifndef HULI_WEBVIEW_H
#define HULI_WEBVIEW_H

#include <QtCore>
#include <QtWebEngineWidgets>
#include "WebPage.h"

class Tabs;

class WebView: public QWebEngineView {
Q_OBJECT;

public:
	explicit WebView(Tabs* tab, QWebEngineProfile* profile);
	
	Tabs* tabs;
	
	int index;
	bool fullScreen = false;
	QAction exitFullScreen;
	WebPage *webPage;
	
signals:
	void fullScreenRequested(bool on);
	void changed(WebView* view);

public slots:
	void fullScreenRequest(QWebEngineFullScreenRequest request);
	void loadStartSlot();
	QWebEngineView* createWindow(QWebEnginePage::WebWindowType type) override;
	void
	renderProcessTerminatedHandler(QWebEnginePage::RenderProcessTerminationStatus terminationStatus, int statusCode);
	void contextMenuEvent(QContextMenuEvent* event) override;
	void openDevTools();

private slots:
	void changedSlot(bool);

private:
	QRect windowGeometry;
};

#endif