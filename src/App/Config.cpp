#include "Config.h"
#include <QtGlobal>

QMap<QString, SearchEngine*> Config::getEngines() {
	QString path;
	
	if(!Config::loadCustomEngines() ||
	   QStandardPaths::locate(QStandardPaths::GenericConfigLocation, "huli/engines.xml").isEmpty()) {
		path = ":/res/data/defaultSearchProviders.xml";
	} else {
		path = QStandardPaths::locate(QStandardPaths::GenericConfigLocation, "huli/engines.xml");
	}
	
	QMap<QString, SearchEngine*> engines;
	
	auto file = new QFile(path);
	
	file->open(QIODevice::ReadOnly);
	
	auto xml = new QXmlStreamReader(file);
	
	QMap<QString, SearchEngine*> returnList = {
		{ "DuckDuckGo", new SearchEngine("DuckDuckGo", "https://www.duckduckgo.com/?q=%1", DuckDuckGo) },
		{ "Google",     new SearchEngine("Google", "https://www.google.com/search?q=%1", Google) }
	};
	
	while(!xml->atEnd()) {
		xml->readNext();
		if(xml->name() == "engine") {
			QString name = "";
			QString url = "";
			SuggestionEnum suggestionProvider = Google;
			while(xml->readNextStartElement()) {
				if(xml->name() == "name") {
					name = xml->readElementText();
				} else if(xml->name() == "url") {
					url = xml->readElementText();
				} else if(xml->name() == "suggestions") {
					suggestionProvider = getProviderFromString(xml->readElementText());
				} else {
					xml->skipCurrentElement();
				}
			}
			if(!name.isEmpty() && !url.isEmpty()) {
				SearchEngine* engine = new SearchEngine(name, url, suggestionProvider);
				returnList[engine->name] = engine;
			}
			
		}
	}
	
	return returnList;
}

SuggestionEnum Config::getProviderFromString(QString input) {
	if(input.toLower() == "duckduckgo") {
		return DuckDuckGo;
	} else {
		return Google;
	}
}

SearchEngine* Config::getCurrentEngine() {
	GET_SETTINGS
	return getEngines().value(settings.value("browser/searchEngine", "DuckDuckGo").toString());
}

QString Config::getHomePage() {
	GET_SETTINGS
	return settings.value("browser/homepage", "https://start.duckduckgo.com").toString();
}

QString Config::getNewTabPage() {
	GET_SETTINGS
	return settings.value("browser/newtab", "https://start.duckduckgo.com").toString();
}

AbstractSuggestionProvider* Config::getProvider(SearchEngine* engine) {
	switch(engine->provider) {
		case DuckDuckGo:
			return new DuckDuckGoProvider();
		case Google:
			return new GoogleProvider();
		default:
			return nullptr;
	}
}

int Config::getSuggestionTruncateLength() {
	GET_SETTINGS
	return settings.value("suggestions/truncate", 5).toInt();
}

bool Config::iconsFromDesktop() {
	GET_SETTINGS
	// If on linux, default is true, otherwise has to be manually set
	#ifdef Q_OS_LINUX
	return settings.value("ui/usesicontheme", true).toBool();
	#else
	return settings.value("ui/usesicontheme", false).toBool();
	#endif
}

bool Config::loadCustomLayout() {
	GET_SETTINGS
	return settings.value("ui/loadlayout", true).toBool();
}

bool Config::loadCustomEngines() {
	GET_SETTINGS
	return settings.value("search/loadCustomEngines", true).toBool();
}
