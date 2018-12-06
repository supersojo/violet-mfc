#ifndef XARROWHEAD_H
#define XARROWHEAD_H

#include "arrowhead.h"
#include "../graph/vrelativepath.h"
namespace violet {
    namespace abstract {
        class XArrowHead : public ArrowHead{
            public:
                XArrowHead():ArrowHead(){
                    GetPath();
                    SetName("X");
                }
                XArrowHead(const XArrowHead& arrowHead) : ArrowHead(arrowHead) {
                    SetName("X");
                }
                XArrowHead& operator=(const XArrowHead& arrowHead) {
                    ArrowHead::operator=(arrowHead);
                    SetName("X");
                    return *this;
                }
                ArrowHead* Clone() {
                    XArrowHead* t = new XArrowHead;
                    *t = *this;
                    return t;
                }
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
