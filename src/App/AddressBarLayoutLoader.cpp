#include "AddressBarLayoutLoader.h"

QString AddressBarLayoutLoader::getFile() {
	if(!Config::loadCustomLayout() ||
	   QStandardPaths::locate(QStandardPaths::GenericDataLocation, "toolbar.xml").isEmpty()) {
		return ":/res/data/defaultToolbarLayout.xml";
	}
	return QStandardPaths::locate(QStandardPaths::GenericDataLocation, "toolbar.xml");
}

QVector<layoutItems> AddressBarLayoutLoader::getLayout() {
	QFile* file = new QFile(getFile());
	file->open(QIODevice::ReadOnly);
	auto* xml = new QXmlStreamReader(file);
	QVector<layoutItems> layout;
	
	// Parse the XML file
	while(!xml->atEnd()) {
		xml->readNext();
		if(xml->tokenType() == QXmlStreamReader::StartElement && xml->name() == "button") {
			QString buttonType = xml->attributes().value("type").toString();
			if(buttonType == "back") {
				layout.append(Back);
			} else if(buttonType == "forward") {
				layout.append(Forward);
			} else if(buttonType == "reload") {
				layout.append(Reload);
			} else if(buttonType == "downloads") {
				layout.append(Downloads);
			} else {
				qWarning() << "Error in parsing toolbar XML: invalid button type " << buttonType << " in: " << xml->name();
			}
		} else if(xml->tokenType() == QXmlStreamReader::StartElement && xml->name() == "urlbar") {
			layout.append(UrlBar);
		}
	}
	
	return layout;
}

