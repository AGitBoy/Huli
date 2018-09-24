#ifndef HULI_ICONPROVIDER_H
#define HULI_ICONPROVIDER_H

#include <QtWidgets>

class iconProvider { // Convert into namespace?
public:
	// Prefer symbolic icons, for greater compatibility with Ubuntu's new icon theme "Suru"
	static QIcon getLogo() { return getIcon("huli", ":/res/icons/app/logo.svg"); }
	static QIcon getNewTabIcon() { return getIcon("tab-new-symbolic", ":/res/icons/actions/plus.svg", {"tab-new"}); }
	static QIcon getReloadIcon() { return getIcon("view-refresh-symbolic", ":/res/icons/actions/refresh.svg", {"view-refresh"}); }
	static QIcon getBackIcon() { return getIcon("go-previous-symbolic", ":/res/icons/actions/arrow-left.svg", {"go-previous"}); }
	static QIcon getForwardIcon() { return getIcon("go-next-symbolic", ":/res/icons/actions/arrow-right.svg", {"go-next"}); }
	static QIcon getSearchIcon() { return getIcon("search-symbolic", ":/res/icons/actions/search.svg", {"search"}); }
	static QIcon getCancelIcon() { return getIcon("dialog-cancel", ":/res/icons/actions/cancel.svg"); }
	static QIcon getDownloadIcon() {
		return getIcon(
			"downloads-emblem",
			":/res/icons/actions/download.svg",
			{"download", "folder-download-symbolic"}
		);
	}
	static QIcon getPauseIcon() { return getIcon("media-playback-pause-symbolic", ":/res/icons/actions/pause.svg", {"media-playback-pause"}); }
	static QIcon getPlayIcon() { return getIcon("media-playback-start-symbolic", ":/res/icons/actions/play.svg", {"media-playback-start"}); }
	static QIcon getSecurityIcon() { return getIcon(
		"dialog-password",
		":/res/icons/actions/security.svg",
		{ "security-alert", "security-high" });
	}
	
	static QIcon getIcon(QString iconName, QString iconPath = nullptr, QStringList fallbackIcons = {});
};

#endif //HULI_ICONPROVIDER_H
