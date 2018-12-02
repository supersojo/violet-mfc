#ifndef SEPARATOR_H
#define SEPARATOR_H
#include "vcontext.h"
#include "vpoint.h"

namespace violet {
	class Separator {
		public:
			virtual void Draw(VContext& context, VPoint& start,VPoint& end) {
			}
			virtual void SetColor(VColor& color) {
			}
			static Separator* EMPTY;
			static Separator* LINE;
	};
	class EmptySeparator : public Separator {
	};
}

#endif
