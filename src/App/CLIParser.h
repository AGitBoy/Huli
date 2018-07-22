//
// Created by aidan on 7/16/18.
//

#ifndef HULI_PARSERFACTORY_H
#define HULI_PARSERFACTORY_H


#include <QtCore>
#include <QtDebug>
#include "Window.h"


// Static only class holding various command line argument processing actions
class CLIParser {
public:
	static QCommandLineParser* newParser(); // Generates a QCommandLineParser object
	static Window* windowFromArgs(QCommandLineParser* parser); // Creates a window from the arguments passed
};


#endif //HULI_PARSERFACTORY_H
