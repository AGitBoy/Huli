#include "getFilenameFromPath.h"

QString getFilenameFromPath(QString path) {
    return QFileInfo(path).fileName();
}