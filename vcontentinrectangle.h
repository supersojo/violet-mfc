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
                VContentInShape::RefreshUp();
            }
            virtual void RefreshDown() {
                if (&GetShape()==nullptr)
                    SetShape(CreateRectangle());
                VContentInShape::RefreshDown();
            }
        private:
            VShape& CreateRectangle() {
                return *(new VRectangle(0,0,GetContent().GetWidth(),GetContent().GetHeight()));
            }
    };
}

#endif
