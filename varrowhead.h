#ifndef VARROWHEAD_H
#define VARROWHEAD_H
#include <iostream>
#include "arrowhead.h"
#include "vrelativepath.h"
namespace violet {
    namespace abstract {
        class VArrowHead : public ArrowHead{
            public:
                VArrowHead():ArrowHead(){
                    GetPath();
                    SetName("V");
                }
                VArrowHead(const VArrowHead& arrowHead):ArrowHead(arrowHead) {
                    SetName("V");
                    std::cout<<"new name"<<GetName()<<std::endl;
                }
                VArrowHead& operator=(const VArrowHead& arrowHead) {
                    ArrowHead::operator=(arrowHead);
                    SetName("V");
                    return *this;
                }
                ArrowHead* Clone() {
                    VArrowHead* t = new VArrowHead;
                    *t = *this;
                    SetName("V");
                    return t;
                }
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
