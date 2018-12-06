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
                m_valid = true;
            }
            bool GetValid() {
                return m_valid;
            }
            void SetValid(bool v) {
                m_valid = v;
            }
            VPoint(int x,int y) {
                m_x = x;
                m_y = y;
                m_valid = true;
            }
            VPoint(int x,int y,bool v) {
                m_x = x;
                m_y = y;
                m_valid = v;
            }
            int GetX() const{
                return m_x;
            }
            int GetY() const{
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
                m_valid = true/*point.m_valid*/;
                // assign always set point valid
                return *this;
            }
            VPoint operator+(const VPoint& point) {
                return VPoint(m_x+point.m_x,m_y+point.m_y);
            }
			VPoint operator-(const VPoint& point) {
                return VPoint(m_x-point.m_x,m_y-point.m_y);
            }
            friend std::ostream& operator<<(std::ostream& out,const VPoint& point) {
                out<<"("<<point.m_x<<","<<point.m_y<<")";
                return out;
            }
        private:
            int m_x;
            int m_y;
            bool m_valid;
    };
    
}

#endif
