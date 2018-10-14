#ifndef HULI_SEARCHENGINE_H
#define HULI_SEARCHENGINE_H

#include <QtCore>
#include "AbstactSuggestionProvider.h"
#include "SuggestionEnum.h"


class SearchEngine: public QObject {
	Q_OBJECT;

	public:
		SearchEngine(QString Name, QString Url, SuggestionEnum Provider);
		QString name;
		QString url;
		SuggestionEnum provider;
		
};


#endif //HULI_SEARCHENGINE_H
