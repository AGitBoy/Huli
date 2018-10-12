#ifndef HULI_GLOBALS_H
#define HULI_GLOBALS_H

#include <QtGlobal>
#include "config.h"

// Globals not defined in config.h

#if PLATFORM_X11 and defined(ENABLE_X11_ICONS)
	#define USE_X11_ICONS true
#else
	#define USE_X11_ICONS false
#endif

#endif //HULI_GLOBALS_H
