#include "urlValidation.h"

bool urlValidation(QString url) {
	QRegularExpression urlRegex;
	urlRegex = QRegularExpression("^(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]$");
	
	return urlRegex.match(url).hasMatch();
};
