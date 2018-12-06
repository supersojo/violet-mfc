#ifndef VPATH_H
#define VPATH_H
#include <vector>
#include <iostream>
#include "vpoint.h"
#include "vcontext.h"
#include "vshape.h"
namespace violet {

    class VPath : public VShape {
        public:
            VPath(){
            }
			VPath(const VPath& path) {
				for(int i=0;i<path.m_path.size();i++)
                {
					m_path.push_back(
						new Entry(path.m_path[i]->m_action,path.m_path[i]->m_point));
				}
			}
			VPath& operator=(const VPath& path) {
				for(int i=0;i<path.m_path.size();i++)
                {
					m_path.push_back(
						new Entry(path.m_path[i]->m_action,path.m_path[i]->m_point));
				}
				return *this;
			}
            void MoveTo(int x, int y) {
                m_path.push_back(new Entry(DO_MOVETO,VPoint(x,y)));
            }
            void LineTo(int x,int y) {
                m_path.push_back(new Entry(DO_LINETO,VPoint(x,y)));
            }
			virtual VRect GetBounds() {
                int x0,y0;// min 
				int x1,y1;// max
				if (m_path.size()<2)
					return VRect();
				x0 = m_path[0]->m_point.GetX();
				y0 = m_path[0]->m_point.GetY();
				x1 = x0;
				y1 = y0;
				
				for (int i=0;i<m_path.size();i++) {
					if (m_path[i]->m_point.GetX()<x0)
						x0 = m_path[i]->m_point.GetX();
					if (m_path[i]->m_point.GetY()<y0)
						y0 = m_path[i]->m_point.GetY(); 
					if (m_path[i]->m_point.GetX()>x1)
						x1 = m_path[i]->m_point.GetX();
					if (m_path[i]->m_point.GetY()>y1)
						y1 = m_path[i]->m_point.GetY(); 
				}
				return VRect(x0,y0,x1-x0,y1-y0);
            }
            virtual ~VPath(){
                for(int i=0;i<m_path.size();i++)
                    delete (m_path[i]);
                m_path.clear();
            }
            virtual void Draw(VContext& context) {
				//save
				VPoint oldLocation = context.GetLocation();
                for (int i=0;i<m_path.size();i++) {

                    if (m_path[i]->m_action == DO_LINETO) {
                        context.DrawLine(context.GetLocation(),m_path[i]->m_point);
                    }
                    // move to 
                    context.Translate(
                         m_path[i]->m_point.GetX()-context.GetLocation().GetX(),
                         m_path[i]->m_point.GetY()-context.GetLocation().GetY());
                }
				for (int i=0;i<m_path.size()-1;i++) {
					context.DrawLine(m_path[i]->m_point,m_path[i+1]->m_point);
                }
				//restore
				context.Translate(oldLocation.GetX()-context.GetLocation().GetX(),
								  oldLocation.GetY()-context.GetLocation().GetY());
				
            }
            static const int DO_MOVETO = 1;
            static const int DO_LINETO = 2;
        private:
            struct Entry {
                Entry(){
                    m_action = 0;
                }
                Entry(int action,VPoint& point){
                    m_action = action;
                    m_point = point;
                }
                int m_action;
                VPoint m_point;
            };
        protected:
            std::vector<Entry*> m_path;
        
    };
}

#endif
