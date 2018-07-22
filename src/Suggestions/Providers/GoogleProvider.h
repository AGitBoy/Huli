//
// Created by aidan on 7/2/18.
//

#ifndef HULI_GOOGLEPROVIDER_H
#define HULI_GOOGLEPROVIDER_H

#include <AbstactSuggestionProvider.h>


// Pulls suggestions from google
class GoogleProvider: public AbstractSuggestionProvider {
public:
	QUrl getFmtUrl(QString inp) override;
	QVector<suggestion*> getSuggestions(QNetworkReply* reply) override;
};


#endif //HULI_GOOGLEPROVIDER_H
