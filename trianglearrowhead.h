#ifndef TRIANGLEARROWHEAD_H
#define TRIANGLEARROWHEAD_H

#include "arrowhead.h"
#include "vrelativepath.h"
namespace violet {
    namespace abstract {
        class TriangleArrowHead : public ArrowHead{
            public:
                TriangleArrowHead(VColor& filledColor) : ArrowHead(filledColor) {
                }
                VRelativePath& GetPath() {
                    if (m_path==nullptr) {
                        VRelativePath* p = new VRelativePath;
                        double x = ARROW_LENGTH* cos(ARROW_ANGLE);
                        double y = ARROW_LENGTH* sin(ARROW_ANGLE);
                        p->MoveTo(0,0);
                        p->LineTo(x,y);
                        p->LineTo(x,-y);
                        p->LineTo(0,0);
                        m_path = p;
                        return *p;
                    }
                    return *m_path;
                }
        };
    }
}

#endif
