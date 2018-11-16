#ifndef VPOINT_H
#define VPOINT_H

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
        private:
            int m_x;
            int m_y;
    };
    
}

#endif
