//
// Created by aidan on 7/2/18.
//

#include "GoogleProvider.h"
#include "suggestion.h"

QVector<suggestion*> GoogleProvider::getSuggestions(QNetworkReply* reply) {
	QVector<suggestion*> suggestionList;
	
	if(reply->error() == QNetworkReply::NoError) {
		QByteArray response = reply->readAll();
		QXmlStreamReader xml(response);
		
		// XML Parsing
		while(!xml.atEnd()) {
			xml.readNext();
			if(xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == "suggestion") {
				suggestion* choice = new suggestion(xml.attributes().value("data").toString());
				suggestionList.append(choice);
			}
		}
	}
	
	return suggestionList;
}

QUrl GoogleProvider::getFmtUrl(QString inp) {
	return QString("http://google.com/complete/search?output=toolbar&q=%1").arg(inp);
}

