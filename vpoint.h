#ifndef VPOINT_H
#define VPOINT_H
#include <iostream>
namespace violet {
    /*
    for a point
    */
    class VPoint {
        public:
            VPoint() {
                m_x = 0;
                m_y = 0;
            }
            VPoint(int x,int y) {
                m_x = x;
                m_y = y;
            }
            int GetX() {
                return m_x;
            }
            int GetY() {
                return m_y;
            }
            void SetX(int x) {
                m_x = x;
            }
            void SetY(int y) {
                m_y = y;
            }
            VPoint& operator=(const VPoint& point) {
                m_x = point.m_x;
                m_y = point.m_y;
                return *this;
            }
            VPoint operator+(const VPoint& point) {
                return VPoint(m_x+point.m_x,m_y+point.m_y);
            }
            friend std::ostream& operator<<(std::ostream& out,const VPoint& point) {
                out<<"("<<point.m_x<<","<<point.m_y<<")";
                return out;
            }
        private:
            int m_x;
            int m_y;
    };
    
}

#endif
