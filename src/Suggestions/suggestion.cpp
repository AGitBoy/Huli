#include <suggestion.h>
#include <utility>

suggestion::suggestion(QString txt, QString snip, QIcon ico)
	: QObject(),
	  text(std::move(txt)),
	  snippet(std::move(snip)),
	  icon(std::move(ico)) {
};
