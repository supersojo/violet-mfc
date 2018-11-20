#ifndef VDIAMOND_H
#define VDIAMOND_H
#include <iostream>
#include "vrectangle.h"

/*
 /|\
 -+-
 \|/
*/
namespace violet {
    class VDiamond : public VRectangle {
        public:
            VDiamond(double w,double h) : VRectangle(0,0,w,h){
            }
            virtual bool Contains(VPoint& point) {
                double result;
                result = point.GetY() + (GetWidth()/GetHeight())*point.GetX()-GetHeight()/2;
                if (result<0)
                    return false;
                result = point.GetY()+(GetHeight()/GetWidth())*point.GetX()-(3/2)*GetHeight();
                if (result>0)
                    return false;
                result = point.GetY()-(GetHeight()/GetWidth())*point.GetX()+(1/2)*GetHeight();
                if (result<0)
                    return false;
                result = point.GetY()-(GetHeight()/GetWidth())*point.GetX()-(1/2)*GetHeight();
                if (result>0)
                    return false;
                return true;
            }
            virtual void Draw(VContext& context,VPoint& location,VColor& color) {
                std::cout<<"Draw diamond"<< std::endl;
            }
            virtual void Fill(VContext& context,VPoint& location,VColor& color) {
                std::cout<<"Fill diamond"<< std::endl;
            }
        private:

    };

}

#endif
