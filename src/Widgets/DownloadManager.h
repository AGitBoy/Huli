#ifndef HULI_DOWNLOADMANAGER_H
#define HULI_DOWNLOADMANAGER_H

#include <QtWidgets>
#include <QtWebEngineWidgets>
#include "getFilenameFromPath.h"
#include "DownloadItem.h"

class AddressBar;

class DownloadManager: public QObject {
	Q_OBJECT;

public:
	explicit DownloadManager(AddressBar* parent = nullptr);
	QVBoxLayout* mainLayout;
	QWidget* widget_parent;
	QWidget* downloadPanel;
	AddressBar* bar;
	QList<QWebEngineDownloadItem*> downloadList;
	
public slots:
	void downloadRequested(QWebEngineDownloadItem *download);
	void toggleHidden();
	void makePanelUi();

private:
	const QStringList possiblyHarmfulFileTypes = {
		// Windows executables
		"application/x-ms-dos-executable",
		"application/x-msi",
		
		// OS X Applications
		"application/x-apple-diskimage",
        "application/x-xar",
		
		// Debian Based Linux Distros
		"application/vnd.debian.binary-package",
		
		// RPM Based Linux Distros
		"application/x-rpm",
		"application/x-source-rpm",
		
		// Linux Snappy Packages
		"application/vnd.snap",
		
		// Linux Appimages
		"application/vnd.appimage",
		
		// Linux Flatpaks
		"application/vnd.flatpak",
		"application/vnd.flatpak.ref",
		"application/vnd.flatpak.repo",
		
        // OpenSUSE One Click Install
		"application/x-suse-ymp",
  
        // Java Executables
        "application/x-java-archive"
	};
};


#endif //HULI_DOWNLOADMANAGER_H
