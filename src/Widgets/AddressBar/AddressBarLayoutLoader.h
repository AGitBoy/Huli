#ifndef HULI_ADDRESSBARLAYOUTLOADER_H
#define HULI_ADDRESSBARLAYOUTLOADER_H

#include <QtCore>
#include "Settings.h"


enum layoutItems {
    Back,
    Forward,
    Reload,
    UrlBar,
    Downloads
};


class AddressBarLayoutLoader {
    public:
        static QString getFile();
        static QVector<layoutItems> getLayout();
};


#endif //HULI_ADDRESSBARLAYOUTLOADER_H
