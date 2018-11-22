#ifndef VLINETEXT_H
#define VLINETEXT_H
#include <iostream>
#include "gdiplus.h"
#include "vrect.h"
#include "vcolor.h"
namespace violet {
    using namespace Gdiplus;
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
                return m_bounds;
            }
            void SetTextColor(VColor& c) {
                m_color = c;
            }
            VColor& GetTextColor() {
                return m_color;
            }
            void Draw(VContext& context) {
                VColor color = context.GetColor();
                context.SetColor(GetTextColor());
                context.DrawString(m_text);
                context.SetColor(color);
            }
            void SetContent(VContent& content) {
                m_content = &content;
            }
            VContent& GetContent() {
                return *m_content;
            }
            /*
            when string changed call UpdateBounds !!!
            */
            void UpdateBounds(VContext& context) {
                m_bounds = CalcTextBounds(context) + VRect(0,0,20,20);
            }
        private:
            VRect CalcTextBounds(VContext& context) {
                return context.MeasureString(m_text);
            }
            std::string m_text;
            //字体
            VColor m_color;
            //content
            VContent* m_content;
            //bounds
            VRect m_bounds;
            //gap 
    };
}

#endif
