#ifndef HULI_SUGGESTION_H
#define HULI_SUGGESTION_H

#include <QtWidgets>

class suggestion: public QObject {
Q_OBJECT;

public:
	explicit suggestion(
		QString txt,
		QString snip = "Search",
		QIcon ico = QIcon::fromTheme(
			"search",
			QIcon(":/res/icons/actions/search.svg")
		)
	);
	
	QString text; // Main text of suggestion
	QString snippet; // Snippet for display, currently of no use.
	QIcon icon; // Icon to display
};


#endif //HULI_SUGGESTION_H
