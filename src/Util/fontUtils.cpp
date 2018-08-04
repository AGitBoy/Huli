#include "fontUtils.h"

QString fontUtils::setTextColor(QString text, QColor color) {
	return QString("<font color=%1>%2</font>").arg(color.name(QColor::HexArgb), text.toHtmlEscaped());
}

QString fontUtils::bold(QString text) {
	return QString("<b>%1</b>").arg(text.toHtmlEscaped());
}
