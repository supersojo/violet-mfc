#include "separator.h"
#include "lineseparator.h"

namespace violet {
	Separator* Separator::EMPTY = new EmptySeparator;
	Separator* Separator::LINE = new LineSeparator;
}
