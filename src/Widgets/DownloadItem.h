#ifndef HULI_DOWNLOADITEM_H
#define HULI_DOWNLOADITEM_H

#include <QtWidgets>
#include <QtWebEngineWidgets>
#include "getFilenameFromPath.h"
#include "fontUtils.h"

class DownloadItem: public QWidget {
	Q_OBJECT;
	
public:
	explicit DownloadItem(QWebEngineDownloadItem *item);
	QWebEngineDownloadItem* download;
	QGridLayout* grid;
	QLabel* iconLabel;
	QLabel* textLabel;
	QProgressBar* progressBar;
	QLabel* status;
	QPushButton* cancelButton;
	QPushButton* pauseButton;
	
	const QIcon pause = QIcon::fromTheme("media-playback-pause"); // TODO: add fallback icon
	const QIcon unpause = QIcon::fromTheme("media-playback-start"); // TODO: add fallback icon
	
private:
	void updatePauseIcon();
	void setStatusText(const QString &text);
	
public slots:
	void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
	void finished();
	void isPausedChanged(bool isChanged);
	void togglePause(bool);
	void stateChanged(QWebEngineDownloadItem::DownloadState state);
	
};


#endif //HULI_DOWNLOADITEM_H