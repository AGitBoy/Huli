#include "DownloadManager.h"
#include "AddressBar.h"
#include "ViewContainer.h"

DownloadManager::DownloadManager(AddressBar* parent): QObject(), widget_parent(parent), mainLayout(nullptr), downloadPanel(
	nullptr), downloadList({}), bar(parent) {
}

void DownloadManager::makePanelUi() {
	downloadPanel = new QWidget(widget_parent);
	mainLayout = new QVBoxLayout(downloadPanel);
	downloadPanel->setAttribute(Qt::WA_QuitOnClose, false);
	downloadPanel->setWindowFlags(Qt::Popup);
	
	downloadPanel->setMinimumWidth(300);
	
	for(auto &i : downloadList) {
		auto* downloadWidget = new DownloadItem(i);
		mainLayout->addWidget(downloadWidget);
	}

	downloadPanel->setLayout(mainLayout);
	downloadPanel->move(bar->downloadsButton.x() - downloadPanel->width(), bar->height()*2);
	downloadPanel->show();
}

void DownloadManager::downloadRequested(QWebEngineDownloadItem* download) {
	if(download && download->state() == QWebEngineDownloadItem::DownloadRequested) {
		if(possiblyHarmfulFileTypes.contains(download->mimeType())) {
			auto warningMsg = tr("The file %1 is an executable and could be harmful to your system."
			                     "Are you sure you want to download?").arg(getFilenameFromPath(download->path()));
			
			int warningStatus = QMessageBox::warning(
				widget_parent->window(),
				tr("Confirm Download"),
				warningMsg,
				QMessageBox::Save | QMessageBox::Cancel
			);
			
			if(warningStatus != QMessageBox::Save) {
				download->cancel();
				return;
			}
		}
		download->accept();
	}
	downloadList << download; // Doesn't work when inside the if statement
}

void DownloadManager::toggleHidden() {
	if(downloadPanel != nullptr) {
		if(downloadPanel->isHidden()) {
			makePanelUi();
		} else {
			downloadPanel = nullptr;
			mainLayout = nullptr;
		}
	} else {
		makePanelUi();
	}
}

