#ifndef VLINETEXT_H
#define VLINETEXT_H
#include <iostream>
#include "vrect.h"
namespace violet {

    class VLineText {
        public:
            VLineText(){}
            std::string GetText() {
                return m_text;
            }
            void SetText(std::string text) {
                m_text = text;
            }
            VLineText& operator=(const VLineText& lineText) {
                m_text = lineText.m_text;
                return *this;
            }
            VRect GetBounds() {
                return VRect();
            }
            void SetTextColor(VColor& c) {
                m_color = c;
            }
            VColor& GetTextColor() {
                return m_color;
            }
            void Draw(VContext& context) {
                std::cout<<"Draw text"<<std::endl;
                context.DrawString(m_text,VPoint(0,0),m_color);
            }
        private:
            std::string m_text;
            //字体
            VColor m_color;
    };
}

#endif
