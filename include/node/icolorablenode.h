#ifndef ICOLORABLENODE_H
#define ICOLORABLENODE_H

namespace violet {
    class VColor;
    class IColorableNode{
        public:
            virtual void SetBackgroundColor(VColor& bgColor) = 0;
            virtual VColor& GetBackgroundColor() = 0;
            virtual void SetBorderColor(VColor& borderColor) = 0;
            virtual VColor& GetBorderColor() = 0;
            virtual void SetTextColor(VColor& textColor) = 0;
            virtual VColor& GetTextColor() = 0;
    };
}

#endif
