#ifndef HULI_DOWNLOADITEM_H
#define HULI_DOWNLOADITEM_H

#include <QtWidgets>
#include <QtWebEngineWidgets>
#include "getFilenameFromPath.h"
#include "fontUtils.h"
#include "iconProvider.h"

class DownloadItem: public QWidget {
    Q_OBJECT;

    public:
        explicit DownloadItem(QWebEngineDownloadItem* item);
        QWebEngineDownloadItem* download;
        QGridLayout* grid;
        QLabel* iconLabel;
        QLabel* textLabel;
        QProgressBar* progressBar;
        QLabel* status;
        QPushButton* cancelButton;
        QPushButton* pauseButton;
        
        const QIcon pause = iconProvider::getPauseIcon();
        const QIcon unpause = iconProvider::getPlayIcon();

    private:
        #if QT_10_SUPPORT
            void updatePauseIcon();
        #endif
        void setStatusText(const QString &text);

    public slots:
        void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
        void finished();
        #if QT_10_SUPPORT
            void isPausedChanged(bool isChanged);
                void togglePause(bool);
        #endif
        void stateChanged(QWebEngineDownloadItem::DownloadState state);
        
};


#endif //HULI_DOWNLOADITEM_H
