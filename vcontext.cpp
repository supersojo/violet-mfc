#include <windows.h>
#include <gdiplus.h>
#include "vcontext.h"
#include "vshape.h"
#include "vcolor.h"
#include "vrect.h"
#include "stringutil.h" 
#pragma comment(lib, "gdiplus.lib")


namespace violet {

using namespace Gdiplus;

VContext::VContext() {
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    
    m_lineWidth = 50;//default
}
void VContext::Fill(VShape& shape) {
    shape.Fill(*this);
}
void VContext::Draw(VShape& shape) {
    shape.Draw(*this);
}
void VContext::DrawLine(VPoint& start,VPoint& end) {
    Pen pen(Color(GetColor().GetR(), GetColor().GetG(), GetColor().GetB()), 1);
    m_graphics->DrawLine(&pen,start.GetX(),start.GetY(),end.GetX(),end.GetY());
}
void VContext::FillRectangle(VPoint& location,VPoint& size,VColor& color) {
    m_graphics->FillRectangle(
        &SolidBrush(Color(color.GetR(),color.GetG(),color.GetB())),
        location.GetX(),location.GetY(),
        size.GetX(),size.GetY()
    );
}
VRect VContext::MeasureString(std::string& str) {
    std::wstring wstr;
    wchar_t* t;
    t = (wchar_t*)wstr.c_str();
    StringUtil::string_to_wstring(str,wstr);
    
    FontFamily fontfamily(L"Arial");//default
	Font font(&fontfamily,8,FontStyleRegular,UnitPoint);
    m_graphics->SetTextRenderingHint(TextRenderingHintSystemDefault);
    RectF rectLayer; 
    rectLayer.X = 0;
    rectLayer.Y = 0; 
	std::cout<<str<<std::endl;
    std::cout<<"linewidth:"<<GetLineWidth()<<std::endl;
    rectLayer.Width = GetLineWidth(); //default 
    rectLayer.Height = -1; 
    RectF boundingBox; 
    m_graphics->MeasureString(wstr.c_str(), -1, &font, rectLayer, &boundingBox ); 
    return VRect(0,0,boundingBox.Width+1,boundingBox.Height+1);// must +1 maybe long truncate the return value of float
}
void VContext::DrawString(std::string& str) {
    std::wstring wstr;
    wchar_t* t;
    t = (wchar_t*)wstr.c_str();
    StringUtil::string_to_wstring(str,wstr);
    
    FontFamily fontfamily(L"Arial");
	Font font(&fontfamily,8,FontStyleRegular,UnitPoint);
 
	m_graphics->SetTextRenderingHint(TextRenderingHintSystemDefault);
    
    VRect rect = MeasureString(str);
    std::cout<<"realrect:"<<rect<<std::endl;
	m_graphics->DrawString(wstr.c_str(),
                        -1,
                        &font,
                            RectF(GetLocation().GetX(),GetLocation().GetY(),rect.GetSize().GetX(),rect.GetSize().GetY()),
                            NULL,
                            &SolidBrush(Color(GetColor().GetR(),GetColor().GetG(),GetColor().GetB()))
                        );
}
VContext::~VContext() {
    GdiplusShutdown(gdiplusToken);
}

}//end violet