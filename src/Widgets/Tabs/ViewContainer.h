#ifndef HULI_VIEWCONTAINER_H
#define HULI_VIEWCONTAINER_H

#include <QtWidgets>
#include "AddressBar.h"

class WebView;

class ViewContainer: public QWidget {
    Q_OBJECT;

    public:
        explicit ViewContainer(WebView* view);
        WebView* view;
        AddressBar* bar;
        QVBoxLayout VBox;
        
};

#endif