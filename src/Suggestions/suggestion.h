#ifndef HULI_SUGGESTION_H
#define HULI_SUGGESTION_H

#include <QtWidgets>

struct suggestion {
	QString text; // Main text of suggestion
	QString snippet = "Search"; // Snippet for display, currently of no use.
	QIcon icon = QIcon::fromTheme(
		"search",
		QIcon(":/res/icons/actions/search.svg")
	); // Icon to display
};


#endif //HULI_SUGGESTION_H
