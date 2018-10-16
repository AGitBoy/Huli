#include "Window.h"


Window::Window(): QMainWindow() {
    tabs = new Tabs();
    setCentralWidget(tabs);
}


Window::Window(const QString &link, bool isPrivate, bool search, bool deduce): QMainWindow() {
    tabs = isPrivate ? new Tabs(new QWebEngineProfile()) : new Tabs;
    
    setCentralWidget(tabs);
    
    ViewContainer* view = qobject_cast<ViewContainer*>(tabs->currentWidget()); // NOLINT
    
    if(!search && !deduce) {
        view->view->load(link);
    } else if(search) {
        view->bar->searchForce(link);
    } else {
        view->bar->searchFromInput(link);
    }
}
