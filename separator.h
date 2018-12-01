#ifndef SEPARATOR_H
#define SEPARATOR_H
#include "vontext.h"
#include "vpoint.h"

namespace violet {
	class Separator {
		public:
			virtual void Draw(VContext& context, VPoint& start,Vpoint& end) {
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
