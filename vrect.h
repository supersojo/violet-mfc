#ifndef VRECT_H
#define VRECT_H

#include "vpoint.h"

namespace violet {
    /*
    for a rectangle
    */
    class VRect {
        public:
            VRect() {
            }
            VRect(VPoint& location,VPoint& size) {
                m_location.SetX(location.GetX());
                m_location.SetY(location.GetY());
                m_size.SetX(size.GetX());
                m_size.SetY(size.GetY());
            }
            VRect(int x, int y, int width, int height) {
                m_location.SetX(x);
                m_location.SetY(y);
                m_size.SetX(width);
                m_size.SetY(height);
            }
            VPoint& GetLocation() {
                return m_location;
            }
            void SetLocation(VPoint& location) {
                m_location.SetX(location.GetX());
                m_location.SetY(location.GetY());
            }
            void SetSize(int w,int h) {
                m_size.SetX(w);
                m_size.SetY(h);
            }
            void SetLocation(int x,int y) {
                m_location.SetX(x);
                m_location.SetY(y);
            }
            void SetSize(VPoint& size) {
                m_size.SetX(size.GetX());
                m_size.SetY(size.GetY());
            }
            VPoint& GetSize() {
                return m_size;
            }
        private:
            VPoint m_location;
            VPoint m_size;
    };

}


#endif
