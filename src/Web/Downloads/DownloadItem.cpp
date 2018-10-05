#include "DownloadItem.h"
#include "iconProvider.h"

DownloadItem::DownloadItem(QWebEngineDownloadItem* item):
	QWidget(),
	download(item),
	grid(new QGridLayout(this)),
	iconLabel(new QLabel(this)),
	textLabel(new QLabel(this)),
	progressBar(new QProgressBar(this)),
	pauseButton(new QPushButton(this)),
	cancelButton(new QPushButton(this)),
	status(new QLabel(this)) {
	QMimeDatabase database;
	
	cancelButton->setIcon(iconProvider::getCancelIcon());
	
	setMinimumHeight(100);
	setMaximumHeight(100);
	
	QIcon icon = QIcon::fromTheme(
		database.mimeTypeForFile(download->path()).iconName(),
		QApplication::style()->standardIcon(QStyle::SP_FileIcon)
	);
	
	connect(
		download, &QWebEngineDownloadItem::downloadProgress,
		this, &DownloadItem::downloadProgress
	);
	#if QT_10_SUPPORT
	connect(
		download, &QWebEngineDownloadItem::isPausedChanged,
		this, &DownloadItem::isPausedChanged
	);
	#endif
	connect(
		download, &QWebEngineDownloadItem::stateChanged,
		this, &DownloadItem::stateChanged
	);
	
	connect(
		download, &QWebEngineDownloadItem::finished,
		this, &DownloadItem::finished
	);
	
	#if QT_10_SUPPORT
	connect(
		pauseButton, &QPushButton::clicked,
		this, &DownloadItem::togglePause
	);
	#endif
	
	connect(
		cancelButton, &QPushButton::clicked,
		[this](bool) { download->cancel(); }
	);
	
	iconLabel->setPixmap(icon.pixmap(32));
	
	status->setTextFormat(Qt::RichText);
	textLabel->setTextFormat(Qt::RichText);
	
	textLabel->setText(fontUtils::bold(getFilenameFromPath(download->path())));
	
	#if QT_10_SUPPORT
	updatePauseIcon();
	#else
		pauseButton->setIcon(pause);
		pauseButton->setEnabled(false);
		pauseButton->setToolTip(tr("Qt 5.10 or above required to pause downloads"));
	#endif

	grid->addWidget(iconLabel, 0, 0);
	grid->addWidget(textLabel, 0, 1, 1, 2);
	grid->addWidget(progressBar, 1, 2);
	grid->addWidget(status, 1, 1);
	grid->addWidget(pauseButton, 0, 3);
	grid->addWidget(cancelButton, 1, 3);
	
	setLayout(grid);
	stateChanged(download->state());
}

void DownloadItem::downloadProgress(qint64 bytesReceived, qint64 bytesTotal) {
	if(bytesTotal != 0) {
		progressBar->setMinimum(0);
		progressBar->setMaximum(static_cast<int>(bytesTotal));
		progressBar->setValue(static_cast<int>(bytesReceived));
	} else {
		progressBar->reset();
		progressBar->setMinimum(0);
		progressBar->setMaximum(0);
	}
}

void DownloadItem::finished() {
	setStatusText(tr("Finished"));
	progressBar->setRange(0, 1);
	progressBar->setValue(1);
}


void DownloadItem::stateChanged(QWebEngineDownloadItem::DownloadState state) {
	switch(state) {
		case (QWebEngineDownloadItem::DownloadRequested):
			break;
		case (QWebEngineDownloadItem::DownloadInProgress):
			pauseButton->setDisabled(false);
			cancelButton->setDisabled(false);
			progressBar->setHidden(false);
			setStatusText(tr("In Progress"));
			break;
		case (QWebEngineDownloadItem::DownloadCompleted):
			pauseButton->setDisabled(true);
			cancelButton->setDisabled(true);
			progressBar->setHidden(true);
			setStatusText("Complete");
			break;
		case (QWebEngineDownloadItem::DownloadCancelled):
			pauseButton->setDisabled(true);
			cancelButton->setDisabled(true);
			progressBar->setHidden(true);
			setStatusText(tr("Canceled"));
			break;
		case (QWebEngineDownloadItem::DownloadInterrupted):
			pauseButton->setDisabled(true);
			cancelButton->setDisabled(true);
			progressBar->setHidden(true);
			setStatusText(download->interruptReasonString());
			break;
	}
}

#if QT_10_SUPPORT
void DownloadItem::isPausedChanged(bool isPaused) {
	updatePauseIcon();
	if(isPaused) {
		setStatusText(tr("Paused"));
	} else {
		setStatusText(tr("In Progress"));
	}
}

void DownloadItem::updatePauseIcon() {
	pauseButton->setIcon(download->isPaused() ? unpause : pause);
}

void DownloadItem::togglePause(bool) {
	if(!download->isPaused()) {
		download->pause();
		updatePauseIcon();
	} else {
		download->resume();
		updatePauseIcon();
	}
}
#endif

void DownloadItem::setStatusText(const QString &text) {
	status->setText(fontUtils::setTextColor(text, QWidget::palette().color(QPalette::Disabled, QPalette::Text)));
}