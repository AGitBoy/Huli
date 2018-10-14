#ifndef HULI_POPUPOBJECT_H
#define HULI_POPUPOBJECT_H

#include <QtWidgets>
#include <QtNetwork>
#include "suggestion.h"
#include "AbstactSuggestionProvider.h"
#include "Settings.h"

class AddressBarInput;

// Object for the handling and display of search suggestions
class PopupObject: public QObject {
	Q_OBJECT;

	public:
		explicit PopupObject(AddressBarInput* editor);
		~PopupObject() override;
		
		AbstractSuggestionProvider* provider; // Abstract class providing search suggestions
		
		bool eventFilter(QObject* obj, QEvent* event) override;
		void showCompletion(QVector<suggestion> choices); // Shows the popup of completions

	public slots:
		void doneCompletion();                        // Called when completion is selected
		void suggest();                               // Starts the process of showing suggestions
		void handleNetworkData(QNetworkReply* reply); // Handles replies to the suggestion requests

	private: 
		// Hack for the first item, which is in the 'search' category to bypass url validation
		QTreeWidgetItem* forcedSearchItem = nullptr;
		
		AddressBarInput* editor = nullptr; // Parent
		QTreeWidget* popup = nullptr; // Popup for showing suggestions
		QTimer timer; // Timer for scheduling
		QNetworkAccessManager networkManager; // Network access manager for requesting suggestion queries.
};


#endif //HULI_POPUPOBJECT_H
