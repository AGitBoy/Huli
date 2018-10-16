#ifndef HULI_BROWSERBASE_H
#define HULI_BROWSERBASE_H

#include <QtWidgets>
#include <QtWebEngineWidgets>
#include "WebPage.h"


// Base class for web browser instances, implementing common functionality
class BrowserBase: public QWebEngineView {
    Q_OBJECT;
    
    public:
        explicit BrowserBase(QWebEngineProfile* profile);
        bool fullScreen = false;
        
    signals:
        void fullScreenRequested(bool on);
        
    public slots:
        void fullScreenRequest(QWebEngineFullScreenRequest request);
        QWebEngineView* createWindow(QWebEnginePage::WebWindowType type) override;
        void renderProcessQuit(QWebEnginePage::RenderProcessTerminationStatus terminationStatus, int statusCode);
        
        #if QT_11_SUPPORT
            void openDevTools();
        #endif
        
    private:
        QRect windowGeometry;
        QAction exitFullScreenAction;
        
        virtual QWebEngineView* newTab() = 0;
        virtual QWebEngineView* newBackgroundTab() = 0;
        QWebEngineView* newPopup();
        QWebEngineView* newWindow();
};


#endif //HULI_BROWSERBASE_H
