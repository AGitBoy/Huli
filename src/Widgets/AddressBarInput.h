#include <utility>

#ifndef HULI_ADDRESSBARINPUT_H
#define HULI_ADDRESSBARINPUT_H

#include <QtWidgets>
#include "PopupObject.h"

class AddressBar;

class AddressBarInput: public QLineEdit {
Q_OBJECT;

public:
	explicit AddressBarInput(AddressBar* parent);
	
	PopupObject popup;
	AddressBar* bar;
	
public slots:
	void searchAction(QString text) { emit search(std::move(text)); }

signals:
	void search(QString text);
};

#endif