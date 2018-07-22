//
// Created by aidan on 7/15/18.
//

#ifndef HULI_DUCKDUCKGOPROVIDER_H
#define HULI_DUCKDUCKGOPROVIDER_H

#include "suggestion.h"
#include "AbstactSuggestionProvider.h"

// Pulls suggestions from DuckDuckGo
class DuckDuckGoProvider: public AbstractSuggestionProvider {
public slots:
	QUrl getFmtUrl(QString inp) override;
	QVector<suggestion*> getSuggestions(QNetworkReply* reply) override;
};


#endif //HULI_DUCKDUCKGOPROVIDER_H
