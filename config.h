#ifndef CONFIG_H
#define CONFIG_H

#define USING_MFC 1

#if _MSC_VER == 1400 /* vs2005 */
#include <cmath>
#define nullptr NULL
static long round(double v) {
	if (abs(v) >= 0.5) {
		if (v>0)
			return 1;
		else
			return -1;
	}
	return 0;
}
#else if _MSC_VER == 1900 /* vs2015*/

#endif// end _MSC_VER

#if USING_MFC == 1

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0603
#endif // end _WIN32_WINNT

#include <afx.h> // using mfc 
#endif // end USING_MFC

#include <gdiplus.h>
#include <objbase.h>

#endif
