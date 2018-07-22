#ifndef HULI_WEBVIEW_H
#define HULI_WEBVIEW_H

#include <QtCore>
#include <QtWebEngineWidgets>


class Tabs;

class WebView: public QWebEngineView {
Q_OBJECT;

public:
	explicit WebView(Tabs* tab);
	
	Tabs* tabs;
	
	int index;
	bool fullScreen = false;
	QAction exitFullScreen;

signals:
	void fullScreenRequested(bool on);
	void changed(WebView* view);

public slots:
	void fullScreenRequest(QWebEngineFullScreenRequest request);
	void loadStartSlot();
	QWebEngineView* createWindow(QWebEnginePage::WebWindowType type) override;

private slots:
	void changedSlot(bool ok);
};

#endif