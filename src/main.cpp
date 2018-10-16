#include <QtWidgets>
#include "Window.h"
#include "CLIParser.h"
#include "iconProvider.h"


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    // Parse command line arguments
    QCommandLineParser* parser = CLIParser::newParser();
    parser->process(app);
    
    // Make main window
    Window* mainWindow = CLIParser::windowFromArgs(parser);
    
    QApplication::setOrganizationName("com.agitboy");
    QApplication::setApplicationName("Huli");
    QApplication::setApplicationVersion("1.0.0");
    
    QApplication::setWindowIcon(iconProvider::getLogo());
    
    // Show window
    mainWindow->setWindowTitle("Huli");
    mainWindow->showMaximized();
    
    return QApplication::exec();
}