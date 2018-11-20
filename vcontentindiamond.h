#ifndef VCONTENTINDIAMOND_H
#define VCONTENTINDIAMOND_H
#include "vcontentinshape.h"
#include "vdiamond.h"
namespace violet {

    class VContentInDiamond : public VContentInShape {
        public:
            VContentInDiamond(VContent& content) {
                SetContent(content);
            }
            virtual ~VContentInDiamond() {
            }
            virtual void RefreshUp() {
                if (&GetShape()==nullptr)
                    SetShape(CreateDiamond());
                VContentInShape::RefreshUp();
            }
            virtual void RefreshDown() {
                if (&GetShape()==nullptr)
                    SetShape(CreateDiamond());
                VContentInShape::RefreshDown();
            }
        private:
            VShape& CreateDiamond() {
                return *(new VDiamond(GetContent().GetWidth(),GetContent().GetHeight()));
            }
    };

}

#endif
