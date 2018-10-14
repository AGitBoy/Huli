#include "TabBar.h"
#include "iconProvider.h"


TabBar::TabBar(QWidget* parent)
	: QTabBar(parent)
	, addTabButton(new QPushButton(this))
{
	addTabButton->setIcon(iconProvider::getNewTabIcon());
	addTabButton->setFlat(true);
	setUsesScrollButtons(false);
}


QSize TabBar::tabSizeHint(int index) const {
	return { getTabLength(), QTabBar::tabSizeHint(index).height() };
}


void TabBar::moveAddTabButton() {
	int tabSize = getTabBarMaxLength();
	
	int h = geometry().top();
	int w = width();
	if(tabSize <= w) {
		addTabButton->move(tabSize, h);
	} else {
		addTabButton->move(w - addTabButton->width(), h);
	}
}


void TabBar::resizeEvent(QResizeEvent* event) {
	QTabBar::resizeEvent(event);
	moveAddTabButton();
}


void TabBar::tabLayoutChange() {
	QTabBar::tabLayoutChange();
	moveAddTabButton();
}


QSize TabBar::sizeHint() const {
	QSize sizeH = QTabBar::sizeHint();
	return { sizeH.width() + addTabButton->width(), sizeH.height() };
}


int TabBar::getTabLength() const {
	if(getTabBarMaxLength() <= width()) {
		return maxTabLength;
	} else {
		return ((width() - addTabButton->width()) / count());
	}
}


int TabBar::getTabBarMaxLength() const { return maxTabLength * count(); }
