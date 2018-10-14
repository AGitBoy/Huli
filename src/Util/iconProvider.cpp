#include "iconProvider.h"
#include "Settings.h"

// Loop used to find fallback icons from list given
#define FALLBACK_LOOP {                                 \
	for(int i = 0; i < fallbackIcons.length(); ++i) {   \
		if(QIcon::hasThemeIcon(fallbackIcons[i])) {     \
			icon_n = fallbackIcons[i];                  \
			break;                                      \
		}                                               \
	}                                                   \
}

QIcon iconProvider::getIcon(
	QString iconName,
	QString iconPath,
	QStringList fallbackIcons
) {
	if(!Settings::iconsFromDesktop()) {
		return QIcon(iconPath);
	} else {
		if(iconPath == nullptr) { // If no fallback icon file given
			QString icon_n = "";
			
			if(fallbackIcons.isEmpty()) {
				return QIcon::fromTheme(iconName);
			} else {
				if(QIcon::hasThemeIcon(iconName)) {
					icon_n = iconName;
				} else {
					FALLBACK_LOOP
				}
			}
			
			return QIcon::fromTheme(icon_n);
			
		} else {
			QString icon_n = "";
			
			if(fallbackIcons.isEmpty()) {
				return QIcon::fromTheme(iconName);
			} else {
				if(QIcon::hasThemeIcon(iconName)) {
					icon_n = iconName;
				} else {
					FALLBACK_LOOP
				}
			}
			
			return QIcon::fromTheme(icon_n, QIcon(iconPath));
		}
	}
}