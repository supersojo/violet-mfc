#ifndef CONFIG_H
#define CONFIG_H

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
#endif

#endif
