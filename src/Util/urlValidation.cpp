#include "urlValidation.h"

bool urlValidation(QString url) {
	QRegularExpression urlRegex;
	// This regex is okay, but it's not the most elegant way of doing this. Possibly look into alternatives?
	urlRegex = QRegularExpression("^(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]$");
	return urlRegex.match(url).hasMatch();
};
