#ifndef HULI_CONFIG_H
#define HULI_CONFIG_H

#include <QtCore>
#include "SearchEngine.h"
#include "DuckDuckGoProvider.h"
#include "GoogleProvider.h"
#include "SuggestionEnum.h"

// Static class for getting various settings
class Config {
public:
	static QMap<QString, SearchEngine*> getEngines();
	static SearchEngine* getCurrentEngine();
	static QString getHomePage();
	static QString getNewTabPage();
	static AbstractSuggestionProvider* getProvider(SearchEngine* engine);
	static SuggestionEnum getProviderFromString(QString input);
	static int getSuggestionTruncateLength();
	static bool iconsFromDesktop();
	static bool loadCustomLayout();
};



#endif //HULI_CONFIG_H
