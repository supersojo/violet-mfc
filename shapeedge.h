#ifndef SHAPEEDGE_H
#define SHAPEEDGE_H
#include "colorableedge.h"
#include "vshape.h"
namespace violet {

    class ShapeEdge : public ColorableEdge {
        public:
            virtual ~ShapeEdge() {
            }
            virtual VShape& GetShape() = 0;
            virtual VRect GetBounds() {
                return GetShape().GetBounds();
            }
            virtual bool Contains(VPoint& point) {
                //???
                return false;
            }
    };
}

#endif
