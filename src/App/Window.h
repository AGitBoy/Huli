#ifndef HULI_WINDOW_H
#define HULI_WINDOW_H

#include <QtWidgets>

#include "Tabs.h"

// Main window. Handles some parameter passing to others
class Window: public QMainWindow {
Q_OBJECT

public:
	Window();
	Window(const QString &link, bool isPrivate, bool search, bool deduce);
	Tabs* tabs = nullptr; // Main widget of program
};

#endif