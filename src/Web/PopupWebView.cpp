#include "PopupWebView.h"

PopupWebView::PopupWebView(QWebEngineProfile* profile): BrowserBase(profile) {

}

QWebEngineView* PopupWebView::newTab() {
	return this; // Disables open in new tab
}

QWebEngineView* PopupWebView::newBackgroundTab() {
	return this; // Disables open in new background tab
}
