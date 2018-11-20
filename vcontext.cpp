#include <windows.h>
#include <gdiplus.h>
#include "vcontext.h"
#include "vshape.h" 
#pragma comment(lib, "gdiplus.lib")

namespace violet {

VContext::VContext() {
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    // 初始化GDI+.
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}
void VContext::Fill(VShape& shape, VColor& color) {
    shape.Fill(*this,GetLocation(),color);
}
void VContext::Draw(VShape& shape, VColor& color) {
    shape.Draw(*this,GetLocation(),color);
}
void VContext::DrawLine(VPoint& start,VPoint& end,VColor& color) {
    Gdiplus::Pen red(Gdiplus::Color(255, 255, 0, 0), 1);
    m_graphics->DrawLine(&red,start.GetX(),start.GetY(),end.GetX(),end.GetY());
}
void VContext::DrawString(std::string& str,VPoint& location, VColor&color) {
    Gdiplus::FontFamily fontfamily(L"宋体");
	Gdiplus::Font font(&fontfamily,60,Gdiplus::FontStyleRegular,Gdiplus::UnitPixel);
 
	//使用与系统相同的处理方式
	m_graphics->SetTextRenderingHint(Gdiplus::TextRenderingHintSystemDefault);
	m_graphics->DrawString(
    L"hello",
    -1,
    &font,
    Gdiplus::PointF(0,0),
    &Gdiplus::SolidBrush(Gdiplus::Color::Green)
    );
}
VContext::~VContext() {
    Gdiplus::GdiplusShutdown(gdiplusToken);
}

}//end violet