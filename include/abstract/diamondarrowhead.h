#ifndef DIAMONDARROWHEAD_H
#define DIAMONDARROWHEAD_H

#include "arrowhead.h"
#include "../graph/vrelativepath.h"
namespace violet {
    namespace abstract {
        class DiamondArrowHead : public ArrowHead{
            public:
                DiamondArrowHead():ArrowHead(){
                    GetPath();// create path
                    SetName("DIAMOND");
                }
                DiamondArrowHead(const DiamondArrowHead& arrowHead) : ArrowHead(arrowHead){
                }
                DiamondArrowHead(VColor& filledColor) : ArrowHead(filledColor) {
                    GetPath();// create path
                    SetName("DIAMOND");
                }
                DiamondArrowHead(VColor& filledColor,std::string name) : ArrowHead(filledColor) {
                    GetPath();// create path
                    SetName(name);
                }
                DiamondArrowHead& operator=(const DiamondArrowHead& arrowHead) {
                    ArrowHead::operator=(arrowHead);
                    return *this;
                }
                ArrowHead* Clone() {
                    DiamondArrowHead* t = new DiamondArrowHead;
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
                        p->LineTo(2*x,0);
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
