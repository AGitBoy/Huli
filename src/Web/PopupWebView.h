#ifndef HULI_POPUPWEBVIEW_H
#define HULI_POPUPWEBVIEW_H

#include <QtWebEngineWidgets>
#include <QtWidgets>
#include "BrowserBase.h"

class PopupWebView: public BrowserBase {
	
	Q_OBJECT;

public:
	explicit PopupWebView(QWebEngineProfile* profile);

private:
	QWebEngineView* newTab() override;
	QWebEngineView* newBackgroundTab() override;
};


#endif //HULI_POPUPWEBVIEW_H
