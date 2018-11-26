#ifndef VRELATIVEPATH_H
#define VRELATIVEPATH_H
#include <iostream>
#include "vpath.h"
namespace violet {
    class VRelativePath : public VPath {
        public:
			VRelativePath(){}
			VRelativePath(const VRelativePath& path):VPath(path){
			}
			VRelativePath& operator=(const VRelativePath& path) {
				VPath::operator=(path);
				return *this;
			}
            /* for arrow head */
            void Transform(double angle) {
                std::cout<<"VRelativePath transform begin"<<m_path.size()<<std::endl;
                /*
                cos(a) -sin(a) 0  ||  (x)
                sin(a) cos(a)  0  ||  (y)
                0      0       1  ||  (1)
                
                ==>
                (x*cos(a)-y*cos(a), x*sin(a)+y*cos(a),1)
                */
                for (int i=0;i<m_path.size();i++) {
                    std::cout<<"VRelativePath 111"<<std::endl;
                    double x0 = m_path[i]->m_point.GetX();
                    double y0 = m_path[i]->m_point.GetY();
                    double x1 = x0*cos(angle)-y0*sin(angle);
                    double y1 = x0*sin(angle)+y0*cos(angle);
                    std::cout<<"VRelativePath 222"<<std::endl;
                    m_path[i]->m_point.SetX(x1);
                    m_path[i]->m_point.SetY(y1);
                    std::cout<<"VRelativePath 333"<<std::endl;
                }
                std::cout<<"VRelativePath transform end"<<std::endl;
            }
            virtual void Draw(VContext& context) {
                std::cout<<"vrelativepath draw"<<std::endl;
                VPoint origin = context.GetLocation();
                for (int i=0;i<m_path.size();i++) {

                    std::cout<<VPoint(m_path[i]->m_point)<<std::endl;
                    if (m_path[i]->m_action == DO_LINETO) {
                        context.DrawLine(context.GetLocation(),origin+m_path[i]->m_point);
                        context.Translate(
                         origin.GetX()+m_path[i]->m_point.GetX()-context.GetLocation().GetX(),
                         origin.GetY()+m_path[i]->m_point.GetY()-context.GetLocation().GetY());
                    }
                    // move to 
                    if (m_path[i]->m_action == DO_MOVETO) {
                        context.Translate(
                             origin.GetX()+m_path[i]->m_point.GetX()-context.GetLocation().GetX(),
                             origin.GetY()+m_path[i]->m_point.GetY()-context.GetLocation().GetY());
                    }
                }
                
				std::cout<<"vrelativepath draw end"<<std::endl;
            }
    };
}

#endif
