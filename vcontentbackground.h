#ifndef VCONTENTBACKGROUND_H
#define VCONTENTBACKGROUND_H
#include "vcontentinshape.h"
#include "vcolor.h"
#include "vcontext.h"
#include "vshape.h"
namespace violet {
    class VContentBackground : public VContentInShape {
        public:
            VContentBackground(VContentInShape& contentShape,VColor& color) {
                //set color?
                SetContent(contentShape);
            }
            void SetBackgroundColor(VColor& color) {
                // color?
            }
            virtual void Draw(VContext& context) {
                // real draw
                
                GetContent().Draw(context);
                
            }
            VShape& GetShape() {
                return reinterpret_cast<VContentInShape*>(&GetContent())->GetShape();
            }
            
        private:
            VColor m_color;
    };
    
}


#endif
