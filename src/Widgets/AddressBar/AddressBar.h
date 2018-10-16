#ifndef HULI_ADDRESSBAR_H
#define HULI_ADDRESSBAR_H

#include <QtWidgets>
#include <QtWebEngineWidgets>
#include "WebView.h"
#include "DownloadManager.h"

class AddressBarInput;
class ViewContainer;


class AddressBar: public QWidget {
    Q_OBJECT;

    public:
        explicit AddressBar(ViewContainer* container);
        
        ViewContainer* view; // Parent
        QHBoxLayout* HBox; // Layout

    public slots:
            void searchFromInput(const QString &query);
        void searchForce(const QString &query);
        void hider(bool on);
};

#endif