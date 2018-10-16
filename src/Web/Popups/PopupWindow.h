#ifndef HULI_POPUPWINDOW_H
#define HULI_POPUPWINDOW_H

#include <QtWebEngineWidgets>
#include <QtWidgets>
#include "PopupWebView.h"

class PopupWindow: public QWidget {
    Q_OBJECT;

    public:
        explicit PopupWindow(QWebEngineProfile* profile);
        
        PopupWebView* view;
        QAction* favicon;

    private:
        QLineEdit* urlBar;

    private slots:
        void handleGeometryChangeRequested(const QRect &newGeometry);
        void fullScreenRequest(bool on);
};


#endif //HULI_POPUPWINDOW_H
