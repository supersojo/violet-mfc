#ifndef VPATH_H
#define VPATH_H
#include <vector>
#include <iostream>
#include "vpoint.h"
#include "vcontext.h"
namespace violet {

    class VPath : public VShape {
        public:
            VPath(){
            }
            void MoveTo(int x, int y) {
                m_path.push_back(new Entry(DO_MOVETO,VPoint(x,y)));
            }
            void LineTo(int x,int y) {
                m_path.push_back(new Entry(DO_LINETO,VPoint(x,y)));
            }
            virtual ~VPath(){
                for(int i=0;i<m_path.size();i++)
                    delete (m_path[i]);
                m_path.clear();
            }
            virtual void Draw(VContext& context) {
                std::cout<<"vpath draw"<<std::endl;
                for (int i=0;i<m_path.size();i++) {
                    std::cout<<m_path[i]->m_point<<"->";
                }
                std::cout<<std::endl;
				for (int i=0;i<m_path.size()-1;i++) {
					context.DrawLine(m_path[i]->m_point,m_path[i+1]->m_point);
                }
				std::cout<<"vpath draw end"<<std::endl;
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
            std::vector<Entry*> m_path;
        
    };
}

#endif
