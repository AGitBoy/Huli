//
// Created by aidan on 7/30/18.
//

#include "SearchEngine.h"

SearchEngine::SearchEngine(QString Name, QString Url, SuggestionEnum Provider)
	: QObject(), name(Name), url(Url), provider(Provider) {
	
}
