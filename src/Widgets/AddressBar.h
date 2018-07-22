#ifndef HULI_ADDRESSBAR_H
#define HULI_ADDRESSBAR_H

#include <QtWidgets>
#include <QtWebEngineWidgets>
#include "WebView.h"

class AddressBarInput;

class ViewContainer;

class AddressBar: public QWidget {
Q_OBJECT;

public:
	explicit AddressBar(ViewContainer* container);
	
	ViewContainer* view; // Parent
	QHBoxLayout* HBox; // Layout
	AddressBarInput* input; // Points to the text input
	QPushButton backButton; // Back navigational button
	QPushButton nextButton; // Forward navigational button
	QPushButton reloadButton; // Forward navigation button

public slots:
	void urlChange(QUrl url);
	void search();
	void searchForce();
	void searchFromInput(const QString &query);
	void searchForce(const QString &query);
	void hider(bool on);
};

#endif