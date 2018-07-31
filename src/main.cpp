#include <QtWidgets>
#include "Window.h"
#include "CLIParser.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	
	QCommandLineParser* parser = CLIParser::newParser();
	parser->process(app);
	
	Window* mainWindow = CLIParser::windowFromArgs(parser);
	
	QApplication::setOrganizationName("com.agitboy");
	QApplication::setApplicationName("Huli");
	QApplication::setApplicationVersion("1.0");
	
	QApplication::setWindowIcon(
		QIcon::fromTheme(
			"internet-web-browser",
			QIcon(":/res/icons/app/logo.svg")
		)
	);
	
	mainWindow->setWindowTitle("Huli");
	mainWindow->show();
	
	return QApplication::exec();
}