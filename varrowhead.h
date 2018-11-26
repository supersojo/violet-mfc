#ifndef VARROWHEAD_H
#define VARROWHEAD_H
#include "arrowhead.h"
#include "vrelativepath.h"
namespace violet {
    namespace abstract {
        class VArrowHead : public ArrowHead{
            public:
                VRelativePath& GetPath() {
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
                        double x = ARROW_LENGTH* cos(ARROW_ANGLE);
                        double y = ARROW_LENGTH* sin(ARROW_ANGLE);
                        p->MoveTo(x,y);
                        p->LineTo(0,0);
                        p->LineTo(x,-y);
                        m_path = p;
                        return *p;
                    }
                    return *m_path;
                }
        };
    }
}
#endif
