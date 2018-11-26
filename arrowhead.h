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
				}
				
                ArrowHead(const VColor& filledColor) {
                    m_borderColor = VColor(0,0,0);// black
                    m_filledColor = filledColor;
                    m_path = nullptr;
                    m_needFill = true;
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
                virtual VRelativePath& GetPath() {
                    if (m_path!=nullptr)
                        return *m_path;
                    return *(reinterpret_cast<VRelativePath*>(nullptr));
                }
                virtual void Draw(VContext& context,VPoint& p,VPoint& q) {
                    std::cout<<"arrowhead draw begin()"<<std::endl;
                    VColor oldColor = context.GetColor();
                    VRelativePath& path = GetPath();
                    RotatePath(path,CalculateAngle(q,p));
                    std::cout<<"arrowhead draw calc end"<<std::endl;
                    context.DrawLine(p,q);
                    context.Translate(
                        q.GetX()-context.GetLocation().GetX(),
                        q.GetY()-context.GetLocation().GetY());
                    if (m_needFill) {
                        context.SetColor(m_filledColor);
                        context.Fill(path);
                    }
                    std::cout<<"arrowhead draw fill end"<<std::endl;
                    context.SetColor(m_borderColor);
                    context.Draw(path);
                    context.Translate(
                        context.GetLocation().GetX()-q.GetX(),
                        context.GetLocation().GetY()-q.GetY());
                    context.SetColor(oldColor);
                    std::cout<<"arrowhead draw end()"<<std::endl;
                }
                static double ARROW_ANGLE;
                static double ARROW_LENGTH;
            private:
                double CalculateAngle(VPoint&p, VPoint& q) {
                    std::cout<<atan2((double)(q.GetY()-p.GetY()), (double)(q.GetX()-p.GetX()))<<std::endl;
                    return atan2((double)(q.GetY()-p.GetY()), (double)(q.GetX()-p.GetX()));
                }
                void RotatePath(VRelativePath& path, double angle) {
                    std::cout<<"arrowhead Transform begin"<<std::endl;
                    path.Transform(angle);
                    std::cout<<"arrowhead Transform end"<<std::endl;
                }
                VColor m_borderColor;
                VColor m_filledColor;
                bool m_needFill;
            protected:
                VRelativePath* m_path;/* for arrow path */
        };
    }
}

#endif
