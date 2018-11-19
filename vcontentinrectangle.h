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
            virtual void RefreshUp() {
                SetShape(CreateRectangle());
                VContentInShape::RefreshUp();
            }
            virtual void RefreshDOwn() {
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
