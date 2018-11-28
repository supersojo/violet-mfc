#ifndef ARROWHEAD_H
#define ARROWHEAD_H
#include <cmath>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "config.h"
#include "vcolor.h"
#include "vpoint.h"
#include "vcontext.h"
#include "vrelativepath.h"

namespace violet {
    namespace abstract {
        class ArrowHead {
            public:
                ArrowHead() {
                    m_borderColor = VColor(0,0,0);// black
                    m_path = nullptr;
                    m_needFill = false;
                    SetName("");
                }
				ArrowHead(const ArrowHead& arrowHead) {
					m_borderColor = arrowHead.m_borderColor;
					m_filledColor = arrowHead.m_filledColor;
					m_needFill = arrowHead.m_needFill;
					VRelativePath* path = arrowHead.m_path;
					m_path = nullptr;
					if (path!=nullptr) {
						m_path = new VRelativePath;
						*m_path = *path;
					}
                    SetName(arrowHead.m_name);
				}
                std::string GetName() {
                    return m_name;
                }
                void SetName(std::string name) {
                    m_name = name;
                }
                bool operator==(const ArrowHead& arrow) {
                    return GetName().compare(arrow.m_name)==0;
                }
				
                ArrowHead& operator=(const ArrowHead& arrowHead) {
                    m_borderColor = arrowHead.m_borderColor;
					m_filledColor = arrowHead.m_filledColor;
					m_needFill = arrowHead.m_needFill;
					VRelativePath* path = arrowHead.m_path;
					if (m_path!=nullptr)
                        delete m_path;
                    m_path = nullptr;
					if (path!=nullptr) {
						m_path = new VRelativePath;
						*m_path = *path;
					}
                    m_name = arrowHead.m_name;
                    return *this;
                }
                ArrowHead(const VColor& filledColor) {
                    m_borderColor = VColor(0,0,0);// black
                    m_filledColor = filledColor;
                    m_path = nullptr;
                    m_needFill = true;
                }
                
                virtual ArrowHead* Clone() {
                    ArrowHead* t = new ArrowHead;
                    *t = *this;
                    return t;
                }
                VColor& GetBorderColor() {
                    return m_borderColor;
                }
                void SetBorderColor(VColor& color) {
                    m_borderColor = color;
                }
                VColor& GetFilledColor() {
                    return m_filledColor;
                }
                void SetFilledColor(VColor& color) {
                    if (m_needFill)
                        m_filledColor = color;
                }
                virtual VRect GetBounds() {
                    if (m_path!=nullptr)
                        return m_path->GetBounds();
                    return VRect();
                }
                virtual VRelativePath& GetPath() {
                    if (m_path!=nullptr)
                        return *m_path;
                    return *(reinterpret_cast<VRelativePath*>(nullptr));
                }
                virtual void Draw(VContext& context,VPoint& p,VPoint& q) {
                    if (m_path==nullptr)
                        return;
                    VColor oldColor = context.GetColor();
                    VRelativePath& path = GetPath();
                    RotatePath(path,CalculateAngle(q,p));
                    std::cout<<"line "<<p<<"-->"<<q<<std::endl;
                    context.SetColor(GetBorderColor());
                    //context.DrawLine(p,q);no need redraw
                    VPoint oldLocation = context.GetLocation();
                    context.Translate(
                        q.GetX()-oldLocation.GetX(),
                        q.GetY()-oldLocation.GetY());
                    if (m_needFill) {
                        context.SetColor(m_filledColor);
                        context.Fill(path);
                    }
                    context.SetColor(m_borderColor);
                    context.Draw(path);
                    context.Translate(
                        oldLocation.GetX()-q.GetX(),
                        oldLocation.GetY()-q.GetY());
                    context.SetColor(oldColor);
                }
                virtual ~ArrowHead() {
                    if (m_path!=nullptr)
                        delete m_path;
                }
                static double ARROW_ANGLE;
                static double ARROW_LENGTH;
            private:
                double CalculateAngle(VPoint&p, VPoint& q) {
                    std::cout<<atan2((double)(q.GetY()-p.GetY()), (double)(q.GetX()-p.GetX()))<<std::endl;
                    return atan2((double)(q.GetY()-p.GetY()), (double)(q.GetX()-p.GetX()));
                }
                void RotatePath(VRelativePath& path, double angle) {
                    path.Transform(angle);
                }
                VColor m_borderColor;
                VColor m_filledColor;
                bool m_needFill;
                std::string m_name;
            protected:
                VRelativePath* m_path;/* for arrow path */
        };
    }
}

#endif
