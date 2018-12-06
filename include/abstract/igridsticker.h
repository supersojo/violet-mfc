#ifndef IGRIDSTICKER_H
#define IGRIDSTICKER_H

namespace violet {
    class VPoint;
    class VRect;
    namespace abstract {
        class IGridSticker {
            public:
                virtual VPoint Snap(VPoint& point) = 0;
                virtual VRect Snap(VRect& rect) = 0;
        };
    }
}
#endif
