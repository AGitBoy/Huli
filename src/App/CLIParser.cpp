#include "CLIParser.h"

QCommandLineParser* CLIParser::newParser() {
	auto* parser = new QCommandLineParser();
	
	parser->setApplicationDescription(QCoreApplication::tr("Web Browser"));
	parser->addHelpOption();
	parser->addVersionOption();
	
	parser->addPositionalArgument("link", QCoreApplication::translate("main", "Link to open"));
	
	parser->addOptions(
		{
			{
				{ "p", "private" },
				QCoreApplication::translate("main", "Private browsing mode")
			},
			{
				{ "s", "search" },
				QCoreApplication::translate("main", "Search input, rather than open as link")
			},
			{
				{ "o", "open" },
				QCoreApplication::translate("main", "Decide if input is link or search query, then navigate")
			}
		}
	);
	
	return parser;
}

Window* CLIParser::windowFromArgs(QCommandLineParser* parser) {
	const QStringList args = parser->positionalArguments();
	
	for(int i = 0; i < parser->unknownOptionNames().length(); ++i) {
		qWarning() << "Unknown option '" << parser->unknownOptionNames()[i] << "'\n";
	} // prints error, then exits.
	
	if(args.empty()) {
		return new Window();
	} else {
		bool privateMode = parser->isSet("private");
		bool search = parser->isSet("search");
		bool open = parser->isSet("open");
		
		QString query = args.join(' ');
		
		return new Window(query, privateMode, search, open);
		
	}
}
