#ifndef HULI_GLOBALS_H
#define HULI_GLOBALS_H

#include <QtGlobal>
#include "config.h"

// Globals not defined by cmake in config.h.in

#if PLATFORM_X11 and defined(ENABLE_X11_ICONS)
	#define USE_X11_ICONS true
#else
	#define USE_X11_ICONS false
#endif

#endif //HULI_GLOBALS_H
