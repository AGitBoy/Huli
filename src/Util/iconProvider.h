#ifndef HULI_ICONPROVIDER_H
#define HULI_ICONPROVIDER_H

#include <QtWidgets>

class iconProvider {
public:
	static QIcon getNewTabIcon() { return QIcon::fromTheme("tab-new", QIcon(":/res/icons/actions/plus.svg")); }
	static QIcon getReloadIcon() { return QIcon::fromTheme("view-refresh", QIcon(":/res/icons/actions/refresh.svg")); }
	static QIcon getBackIcon() { return QIcon::fromTheme("go-previous", QIcon(":/res/icons/actions/arrow-left.svg")); }
	static QIcon getForwardIcon() { return QIcon::fromTheme("go-next", QIcon(":/res/icons/actions/arrow-right.svg")); }
	static QIcon getSearchIcon() { return QIcon::fromTheme("search", QIcon(":/res/icons/actions/search.svg")); }
	static QIcon getCancelIcon() { return QIcon::fromTheme(""); }
};

#endif //HULI_ICONPROVIDER_H
