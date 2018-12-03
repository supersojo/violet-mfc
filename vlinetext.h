#ifndef VLINETEXT_H
#define VLINETEXT_H
#include <iostream>
#include "gdiplus.h"
#include "vrect.h"
#include "vcolor.h"
#include "vcontent.h"
namespace violet {
    using namespace Gdiplus;
    // always one line 
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
            virtual VRect GetBounds() {
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
                context.DrawString(m_text,m_bounds);
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
                if (m_bounds.GetWidth()>MAX_LINE_WIDTH) {
                    m_bounds.SetSize(MAX_LINE_WIDTH,m_bounds.GetHeight()-20);
                }
            }
            const static int MAX_LINE_WIDTH = 200;
            const static int MAX_LINE_HEIGHT = 500;// limit ? for now not support
        private:
            VRect CalcTextBounds(VContext& context) {
                return context.MeasureString(m_text,VRect(0,0,-1,-1));
            }
            std::string m_text;
            //字体
            VColor m_color;
            //content
            VContent* m_content;// needed???
            //bounds
            VRect m_bounds;
            //gap 
    };
}

#endif
