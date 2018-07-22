#include "Window.h"

Window::Window(): QMainWindow() {
	tabs = new Tabs();
	setCentralWidget(tabs);
}

Window::Window(const QString &link, bool isPrivate, bool search, bool deduce): QMainWindow() {
	tabs = isPrivate ? new Tabs(new QWebEngineProfile()) : new Tabs;
	
	setCentralWidget(tabs);
	
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wincompatible-pointer-types"
	ViewContainer* view = qobject_cast<ViewContainer*>(tabs->currentWidget()); // NOLINT
	#pragma clang diagnostic pop
	
	if(!search && !deduce) {
		view->view->load(link);
	} else if(search) {
		view->bar->searchForce(link);
	} else {
		view->bar->searchFromInput(link);
	}
}
