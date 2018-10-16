#include "ViewContainer.h"


ViewContainer::ViewContainer(WebView* view)
    : QWidget()
    , view(view)
    , bar(new AddressBar(this))
{
    VBox.addWidget(bar);
    VBox.addWidget(view);
    
    VBox.setSpacing(0);
    VBox.setMargin(0);
    VBox.setContentsMargins(0, 0, 0, 0);
    VBox.setStretch(1, 2);
    
    setLayout(&VBox);
};
