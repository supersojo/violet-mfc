#include "content/separator.h"
#include "content/lineseparator.h"

namespace violet {
	Separator* Separator::EMPTY = new EmptySeparator;
	Separator* Separator::LINE = new LineSeparator;
}
