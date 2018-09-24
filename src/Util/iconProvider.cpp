#include "iconProvider.h"
#include "Config.h"

QIcon iconProvider::getIcon(QString iconName, QString iconPath, QStringList fallbackIcons) {
	if(!Config::iconsFromDesktop()) {
		return QIcon(iconPath);
	} else {
		if(iconPath == nullptr) {
			QString icon_n = "";
			if(fallbackIcons.isEmpty()) {
				return QIcon::fromTheme(iconName);
			} else {
				if(QIcon::hasThemeIcon(iconName)) {
					icon_n = iconName;
				} else {
					for(int i = 0; i < fallbackIcons.length(); ++i) {
						if(QIcon::hasThemeIcon(fallbackIcons[i])) {
							icon_n = fallbackIcons[i];
							break;
						}
					}
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
					for(int i = 0; i < fallbackIcons.length(); ++i) {
						if(QIcon::hasThemeIcon(fallbackIcons[i])) {
							icon_n = fallbackIcons[i];
							break;
						}
					}
				}
			}
			
			return QIcon::fromTheme(icon_n, QIcon(iconPath));
		}
	}
}