#ifndef COLORABLEEDGE_H
#define COLORABLEEDGE_H
#include "abstractedge.h"
#include "icolorableedge.h"
#include "vcolor.h"
namespace violet {
    using namespace abstract;
    class ColorableEdge : public AbstractEdge, public IColorableEdge{
        public:
            ColorableEdge():AbstractEdge(){}
            virtual void CreateContentStructure() {
                SetBackgroundColor(GetBackgroundColor());
                SetBorderColor(GetBorderColor());
                SetTextColor(GetTextColor());
            }
            virtual ~ColorableEdge() {
            }
            /* IColorableEdge interface */
            virtual void SetBackgroundColor(VColor& bgColor) {
                m_backgroundColor = bgColor;
            }
            virtual VColor& GetBackgroundColor() {
                return m_backgroundColor;
            }
            virtual void SetBorderColor(VColor& borderColor) {
                m_borderColor = borderColor;
            }
            virtual VColor& GetBorderColor() {
                return m_borderColor;
            }
            virtual void SetTextColor(VColor& textColor) {
                m_textColor = textColor;
            }
            virtual VColor& GetTextColor() {
                return m_textColor;
            }
        private:
            VColor m_backgroundColor;
            VColor m_borderColor;
            VColor m_textColor;
    };
}

#endif
