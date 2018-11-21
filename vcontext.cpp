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
}
void VContext::Fill(VShape& shape, VColor& color) {
    shape.Fill(*this,GetLocation(),color);
}
void VContext::Draw(VShape& shape, VColor& color) {
    shape.Draw(*this,GetLocation(),color);
}
void VContext::DrawLine(VPoint& start,VPoint& end,VColor& color) {
    
    Pen pen(Color(color.GetR(), color.GetG(), color.GetB()), 1);
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
    rectLayer.Width = 50; //default 
    rectLayer.Height = -1; 
    RectF boundingBox; 
    m_graphics->MeasureString(wstr.c_str(), -1, &font, rectLayer, &boundingBox ); 
    return VRect(0,0,boundingBox.Width,boundingBox.Height);
}
void VContext::DrawString(std::string& str,VPoint& location, VColor&color) {
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
                            &SolidBrush(Color(color.GetR(),color.GetG(),color.GetB()))
                        );
    std::cout<<color<<std::endl;
}
VContext::~VContext() {
    GdiplusShutdown(gdiplusToken);
}

}//end violet