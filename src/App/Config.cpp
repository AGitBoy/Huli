#include "Config.h"
#include <QtGlobal>

QMap<QString, SearchEngine*> Config::getEngines() {
	QMap<QString, SearchEngine*> returnList = {
		{ "DuckDuckGo", new SearchEngine("DuckDuckGo", "https://www.duckduckgo.com/?q=%1", DuckDuckGo) },
		{ "Google",     new SearchEngine("Google", "https://www.google.com/search?q=%1", Google) }
	};
	
	QSettings settings("com.agitboy", "Huli");
	int size = settings.beginReadArray("searchengines");
	
	for(int i = 0; i < size; ++i) {
		settings.setArrayIndex(i);
		returnList[settings.value("name").toString()] = new SearchEngine(
			settings.value("name").toString(),
			settings.value("url").toString(),
			getProviderFromString(settings.value("suggestionProvider").toString())
		);
		
	}
	settings.endArray();
	
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
	QSettings settings("com.agitboy", "Huli");
	return getEngines().value(settings.value("browser/searchEngine", "DuckDuckGo").toString());
}

QString Config::getHomePage() {
	QSettings settings("com.agitboy", "Huli");
	return settings.value("browser/homepage", "https://start.duckduckgo.com").toString();
}

QString Config::getNewTabPage() {
	QSettings settings("com.agitboy", "Huli");
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
	QSettings settings("com.agitboy", "Huli");
	return settings.value("suggestions/truncate", 5).toInt();
}

bool Config::iconsFromDesktop() {
	QSettings settings("com.agitboy", "Huli");
	// If on linux, default is true, otherwise has to be manually set
	#ifdef Q_OS_LINUX
	return settings.value("ui/usesicontheme", true).toBool();
	#else
	return settings.value("ui/usesicontheme", false).toBool();
	#endif
}
