#ifndef HULI_FONTUTILS_H
#define HULI_FONTUTILS_H

#include <QtWidgets>

// Various utilities for manipulating rich text
namespace fontUtils {
	// sets the text color, including alpha.
	QString setTextColor(QString text, QColor color);
	
	// Bolds text
	QString bold(QString text);
};


#endif //HULI_FONTUTILS_H
