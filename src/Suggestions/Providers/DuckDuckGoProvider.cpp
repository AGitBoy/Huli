//
// Created by aidan on 7/15/18.
//

#include "DuckDuckGoProvider.h"

QVector<suggestion*> DuckDuckGoProvider::getSuggestions(QNetworkReply* reply) {
	QVector<suggestion*> suggestionList;
	
	if(reply->error() == QNetworkReply::NoError) {
		QByteArray replyData = reply->readAll();
		QJsonParseError error; // NOLINT
		QJsonDocument doc = QJsonDocument::fromJson(replyData, &error);
		
		// Parse JSON
		if(error.error == QJsonParseError::NoError && doc.isArray()) {
			QJsonArray array = doc.array();
			
			for(auto &&i : array) {
				if(i.isObject()) {
					QJsonObject object = i.toObject();
					suggestion* suggest = new suggestion(object.value("phrase").toString());
					if(object.contains("snippet")) {
						suggest->snippet = object.value("snippet").toString();
					}
					suggestionList.append(suggest);
				}
			}
		}
	}
	return suggestionList;
}

QUrl DuckDuckGoProvider::getFmtUrl(QString inp) {
	return QUrl(QString("https://duckduckgo.com/ac/?q=%1").arg(inp));
}
