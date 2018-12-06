#ifndef VCONTENTBORDER_H
#define VCONTENTBORDER_H

#include "vcontentinshape.h"
#include "../graph/vcolor.h"
#include "../graph/vshape.h"
#include "../graph/vcontext.h"

namespace violet {
    class VContentBorder : public VContentInShape {
        public:
            VContentBorder(VContentInShape& contentShape,VColor& color) {
                contentShape.AddParent(*this);
                SetBorderColor(color);
                SetContent(contentShape);
            }
            virtual ~VContentBorder() {
            }
            VColor& GetBorderColor() {
                return m_color;
            }
            void SetBorderColor(VColor& color) {
                m_color = color;
            }
            void Draw(VContext& context) {
                // real draw border
                VColor color = context.GetColor();
                context.SetColor(GetBorderColor());
                
                context.Draw(GetShape());
                context.SetColor(color);
                
                // draw content
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
