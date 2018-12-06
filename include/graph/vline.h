#ifndef VLINE_H
#define VLINE_H

#include "vpoint.h"

namespace violet {
    /*
    for a line
    */
    class VLine {
        public:
            VLine() {
            }
            VLine(VPoint& start,VPoint& end) {
                m_start.SetX(start.GetX());
                m_start.SetY(start.GetY());
                m_end.SetX(end.GetX());
                m_end.SetY(end.GetY());
            }
            VLine(int x0, int y0, int x1, int y1) {
                m_start.SetX(x0);
                m_start.SetY(y0);
                m_end.SetX(x1);
                m_end.SetY(y1);
            }
            VPoint& GetStart() {
                return m_start;
            }
            void SetStart(VPoint& start) {
                m_start.SetX(start.GetX());
                m_start.SetY(start.GetY());
            }
            void SetStart(int x,int y) {
                m_start.SetX(x);
                m_start.SetY(y);
            }
            void SetEnd(int x,int y) {
                m_end.SetX(x);
                m_end.SetY(y);
            }
            void SetEnd(VPoint& end) {
                m_end.SetX(end.GetX());
                m_end.SetY(end.GetY());
            }
            VPoint& GetEnd() {
                return m_end;
            }
        private:
            VPoint m_start;
            VPoint m_end;
    };

}


#endif
