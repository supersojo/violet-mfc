#ifndef VRECTANGLE_H
#define VRECTANGLE_H
#include <iostream>
#include "vshape.h"

namespace violet {
    class VRectangle : public VShape {
        public:
            VRectangle(double x,double y,double w,double h) {
                m_x = x;
                m_y = y;
                m_width = w;
                m_height = h;
            }
            void SetX(double x) {
                m_x = x;
            }
            void SetY(double y) {
                m_y = y; 
            }
            void SetWidth(double w) {
                m_width = w;
            }
            void SetHeight(double h) {
                m_height = h;
            }
            double GetX() {
                return m_x;
            }
            double GetY() {
                return m_y;
            }
            double GetWidth() {
                return m_width;
            }
            double GetHeight() {
                return m_height;
            }
            virtual bool Contains(VPoint& point) {
                if(((point.GetX() > GetX()) &&
                    (point.GetX() < GetX()+GetWidth())) &&
                   ((point.GetY() > GetY()) &&
                    (point.GetY() < GetY()+GetHeight())))
                    return true;
                
                return false;
            }
            virtual VRect GetBounds() {
                return VRect(m_x,m_y,m_width,m_height);
            }
            virtual void Draw(VContext& context) {
                VPoint location = context.GetLocation();
                context.DrawLine(location,location+VPoint(m_width,0));
                context.DrawLine(location,location+VPoint(0,m_height));
                context.DrawLine(location+VPoint(m_width,0),
                                 location+VPoint(m_width,0)+VPoint(0,m_height));
                context.DrawLine(location+VPoint(0,m_height),
                                 location+VPoint(0,m_height)+VPoint(m_width,0));
            }
            virtual void Fill(VContext& context) {
                VPoint location = context.GetLocation();
                context.FillRectangle(location,VPoint(m_width,m_height),context.GetColor());
            }
        private:
            double m_x;
            double m_y;
            double m_width;
            double m_height;
    };

}

#endif
