#ifndef HULI_GOOGLEPROVIDER_H
#define HULI_GOOGLEPROVIDER_H

#include <AbstactSuggestionProvider.h>

// Pulls suggestions from Google
class GoogleProvider: public AbstractSuggestionProvider {
	public:
		QUrl getFmtUrl(QString inp) override;
		QVector<suggestion> getSuggestions(QNetworkReply* reply) override;
};


#endif //HULI_GOOGLEPROVIDER_H
