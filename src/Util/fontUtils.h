#ifndef HULI_FONTUTILS_H
#define HULI_FONTUTILS_H

#include <QtWidgets>

// Various utilities for manipulating rich text
class fontUtils {
public:
	static QString setTextColor(QString text, QColor color);
	static QString bold(QString text);
};


#endif //HULI_FONTUTILS_H
