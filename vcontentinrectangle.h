#ifndef VCONTENTINRECTANGLE_H
#define VCONTENTINRECTANGLE_H
#include "vcontentinshape.h"
#include "vrectangle.h"
namespace violet {
    class VContentInRectangle : public VContentInShape {
        public:
            VContentInRectangle(VContent& content) {
                SetContent(content);
            }
            virtual ~VContentInRectangle() {
            }
            virtual void RefreshUp() {
                if (&GetShape()==nullptr)
                    SetShape(CreateRectangle());
                else
                    UpdateRectangle(0,0,GetContent().GetWidth(),GetContent().GetHeight());
                VContentInShape::RefreshUp();
            }
            virtual void RefreshDown() {
                if (&GetShape()==nullptr)
                    SetShape(CreateRectangle());
                else
                    UpdateRectangle(0,0,GetContent().GetWidth(),GetContent().GetHeight());
                VContentInShape::RefreshDown();
            }
        private:
            void UpdateRectangle(double x,double y,double w,double h) {
                VShape* shape = &GetShape();
                VRectangle* rect = reinterpret_cast<VRectangle*>(shape);
                rect->SetX(x);
                rect->SetY(y);
                rect->SetWidth(w);
                rect->SetHeight(h);
            }
            VShape& CreateRectangle() {
                return *(new VRectangle(0,0,GetContent().GetWidth(),GetContent().GetHeight()));
            }
    };
}

#endif
