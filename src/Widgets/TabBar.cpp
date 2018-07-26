//
// Created by aidan on 7/25/18.
//

#include "TabBar.h"

TabBar::TabBar(QWidget* parent): QTabBar(parent), addTabButton(new QPushButton(this)) {
	addTabButton->setIcon(QIcon::fromTheme("tab-new", QIcon(":/res/icons/actions/plus.svg")));
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
		addTabButton->move(w - 57, h);
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
	return { sizeH.width()+25, sizeH.height() };
}

int TabBar::getTabLength() const {
	if(getTabBarMaxLength() <= width()) {
		return maxTabLength;
	} else {
		return (width() / count()) - 25;
	}
}

int TabBar::getTabBarMaxLength() const {
	int tabSize = 0;
	for(int i = 0; i < count(); ++i) {
		tabSize += maxTabLength;
	}
	return tabSize;
}
