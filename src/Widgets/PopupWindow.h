#ifndef HULI_POPUPWINDOW_H
#define HULI_POPUPWINDOW_H

#include <QtWebEngineWidgets>
#include <QtWidgets>

class PopupWindow: public QWidget {
Q_OBJECT;

public:
	explicit PopupWindow(QWebEngineProfile* profile);
	
	QWebEngineView* view;
	QAction* favicon;
	QAction* exitFullScreenAction;

private:
	QLineEdit* urlBar;

private slots:
	void handleGeometryChangeRequested(const QRect &newGeometry);
	void fullScreenRequest(QWebEngineFullScreenRequest request);
};


#endif //HULI_POPUPWINDOW_H
