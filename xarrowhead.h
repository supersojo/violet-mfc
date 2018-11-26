#ifndef XARROWHEAD_H
#define XARROWHEAD_H

#include "arrowhead.h"
#include "vrelativepath.h"
namespace violet {
    namespace abstract {
        class XArrowHead : public ArrowHead{
            public:
                VRelativePath& GetPath() {
                    double CROSS_ANGLE = M_PI / 4;
                    if (m_path==nullptr) {
                        /*
                        +---->
                        |
                        |
                        V   /
                           /
                           \
                            \
                        */
                        VRelativePath* p = new VRelativePath;
                        double x = 0.75*ARROW_LENGTH* cos(CROSS_ANGLE);
                        double y = 0.75*ARROW_LENGTH* sin(CROSS_ANGLE);
                        p->MoveTo(x,y);
                        p->LineTo(-x,-y);
                        p->MoveTo(x,-y);
                        p->LineTo(-x,y);
                        m_path = p;
                        return *p;
                    }
                    return *m_path;
                }
        };
    }
}
#endif
