#ifndef HULI_PARSERFACTORY_H
#define HULI_PARSERFACTORY_H


#include <QtCore>
#include <QtWidgets>
#include <QtDebug>
#include "Window.h"

// namespace holding various command line argument processing actions
namespace CLIParser {
    QCommandLineParser* newParser(); // Generates a QCommandLineParser object
    Window* windowFromArgs(QCommandLineParser* parser); // Creates a window from the arguments passed
};


#endif //HULI_PARSERFACTORY_H
