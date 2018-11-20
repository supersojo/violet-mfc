#ifndef VSHAPE_H
#define VSHAPE_H
#include "vrect.h"
#include "vpoint.h"

namespace violet {
    class VShape {
        public:
            virtual bool Contains(VPoint& point) {
                return false;
            }
            virtual VRect GetBounds() {
                return VRect();
            }
            virtual void Draw(VContext& context,VPoint& location,VColor& color) {
            }
            virtual void Fill(VContext& context,VPoint& location,VColor& color) {
            }
    };
}

#endif
