#ifndef HULI_ABSTACTSUGGESTIONPROVIDER_H
#define HULI_ABSTACTSUGGESTIONPROVIDER_H

#include <QtCore>
#include <QtNetwork>

#include "suggestion.h"

// Abstract class to be subclassed to provide search query suggestions from various providers
class AbstractSuggestionProvider: QObject {
    Q_OBJECT;

    public slots:
        // Gets the url search suggestion url for the inputted query
        virtual QUrl getFmtUrl(QString inp) = 0;
        
        // Parses the suggestions and returns a list of suggestions to display
        virtual QVector<suggestion> getSuggestions(QNetworkReply* reply) = 0;
};

#endif //HULI_ABSTACTSUGGESTIONPROVIDER_H
