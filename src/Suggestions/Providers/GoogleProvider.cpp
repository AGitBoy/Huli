#include "GoogleProvider.h"
#include "suggestion.h"

QVector<suggestion> GoogleProvider::getSuggestions(QNetworkReply* reply) {
	QVector<suggestion> suggestionList;
	
	if(reply->error() == QNetworkReply::NoError) {
		QByteArray response = reply->readAll();
		QXmlStreamReader xml(response);
		
		// XML Parsing
		while(!xml.atEnd()) {
			xml.readNext();
			if(xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == "suggestion") {
				suggestion choice;
				
				choice.text = xml.attributes().value("data").toString();
				
				choice.icon = QIcon::fromTheme(
					"search",
					QIcon(":/res/icons/actions/search.svg")
				); // Icon to display
				
				suggestionList.append(choice);
			}
		}
	}
	
	return suggestionList;
}

QUrl GoogleProvider::getFmtUrl(QString inp) {
	return QString("http://google.com/complete/search?output=toolbar&q=%1").arg(inp);
}

