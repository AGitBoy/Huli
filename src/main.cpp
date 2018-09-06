#include <QtWidgets>
#include "Window.h"
#include "CLIParser.h"

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
	
	QApplication::setWindowIcon(
		QIcon::fromTheme(
			"huli",
			QIcon(":/res/icons/app/logo.svg")
		)
	);
	
	// Show window
	mainWindow->setWindowTitle("Huli");
	mainWindow->showMaximized();
	
	return QApplication::exec();
}