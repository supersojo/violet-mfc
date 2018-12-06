#ifndef TRIANGLEARROWHEAD_H
#define TRIANGLEARROWHEAD_H

#include "arrowhead.h"
#include "../graph/vrelativepath.h"
namespace violet {
    namespace abstract {
        class TriangleArrowHead : public ArrowHead{
            public:
                TriangleArrowHead():ArrowHead(){
                    GetPath();
                    SetName("TRIANGLE");
                }
                TriangleArrowHead(const TriangleArrowHead& arrowHead) : ArrowHead(arrowHead){
                }
                TriangleArrowHead(VColor& filledColor) : ArrowHead(filledColor) {
                    GetPath();
                    
                    SetName("TRIANGLE");
                }
                TriangleArrowHead(VColor& filledColor,std::string name) : ArrowHead(filledColor) {
                    GetPath();
                    
                    SetName(name);
                }
                TriangleArrowHead& operator=(const TriangleArrowHead& arrowHead) {
                    ArrowHead::operator=(arrowHead);
                    return *this;
                }
                ArrowHead* Clone() {
                    TriangleArrowHead* t = new TriangleArrowHead;
                    *t = *this;
                    return t;
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
