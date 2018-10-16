#ifndef HULI_SUGGESTION_H
#define HULI_SUGGESTION_H

#include <QtWidgets>
#include "iconProvider.h"

struct suggestion {
    QString text; // Main text of suggestion
    QString snippet = "Search"; // Snippet for display
    QIcon icon = iconProvider::getSearchIcon(); // Icon to display
};


#endif //HULI_SUGGESTION_H
