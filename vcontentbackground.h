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
                SetBackgroundColor(color);
            }
            virtual ~VContentBackground() {
            }
            VColor& GetBackgroundColor() {
                return m_color;
            }
            void SetBackgroundColor(VColor& color) {
                // color?
                m_color = color;
            }
            virtual void Draw(VContext& context) {
                // save
                VColor color = context.GetColor();
                
                context.SetColor(GetBackgroundColor());
                context.Fill(GetShape());
                
                // restore
                context.SetColor(color);
                
                GetContent().Draw(context);
            }
            virtual VShape& GetShape() {
                return reinterpret_cast<VContentInShape*>(&GetContent())->GetShape();
            }
            
        private:
            VColor m_color;
    };
    
}


#endif
