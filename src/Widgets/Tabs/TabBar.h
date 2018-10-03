#ifndef HULI_TABBAR_H
#define HULI_TABBAR_H

#include <QtWidgets>

class TabBar: public QTabBar {
Q_OBJECT;

public:
	explicit TabBar(QWidget* parent = nullptr);
	QPushButton* addTabButton;

private:
	int getTabLength() const;
	int getTabBarMaxLength() const;
	const int maxTabLength = 200;

public slots:
	void moveAddTabButton();

protected slots:
	void resizeEvent(QResizeEvent* event) override;
	void tabLayoutChange() override;
	QSize sizeHint() const override;
	QSize tabSizeHint(int index) const override;
};


#endif //HULI_TABBAR_H
