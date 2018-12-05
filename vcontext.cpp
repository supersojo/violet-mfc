#include "config.h"
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
void VContext::Rotate(VPoint& point,double angle) {
    m_graphics->TranslateTransform(point.GetX(),point.GetY());
    m_graphics->RotateTransform(angle);
    m_graphics->TranslateTransform(-point.GetX(),-point.GetY());
}
void VContext::DrawLine(VPoint& start,VPoint& end) {
    /*
    DashStyleSolid
    DashStyleDash
    DashStyleDot
    DashStyleDashDot
    DashStyleDashDotDot
    DashStyleCustom
    */
    
    REAL dashVals[2] = {
	5.0f,   //线长5个像素
	2.0f   //间隔2个像素
    };
    
    Pen pen(Color(GetColor().GetR(), GetColor().GetG(), GetColor().GetB()), 1);
    if (GetStroke().GetName().compare("SOLID")==0) {
        pen.SetDashStyle(DashStyleSolid);
    } else if (GetStroke().GetName().compare("DOTTED")==0) {
        pen.SetDashPattern(dashVals, 2);
    }
    m_graphics->DrawLine(&pen,start.GetX(),start.GetY(),end.GetX(),end.GetY());
}
void VContext::FillRectangle(VPoint& location,VPoint& size,VColor& color) {
    m_graphics->FillRectangle(
        &SolidBrush(Color(color.GetR(),color.GetG(),color.GetB())),
        location.GetX(),location.GetY(),
        size.GetX(),size.GetY()
    );
}
void VContext::FillPolygon(VPoint& location,VPoint* points,int count){
    PointF* p = new PointF[count];
    for(int i=0;i<count;i++) {
        *(p+i) = PointF((points+i)->GetX(),(points+i)->GetY());
    }
    m_graphics->FillPolygon(
        &SolidBrush(Color(GetColor().GetR(),GetColor().GetG(),GetColor().GetB())),
        p,
        count
    );
    delete[] p;
}
VRect VContext::MeasureString(std::string& str,VRect& layoutRect) {
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
    rectLayer.Width = layoutRect.GetWidth();
    rectLayer.Height = layoutRect.GetHeight(); 
    RectF boundingBox; 
    m_graphics->MeasureString(wstr.c_str(), -1, &font, rectLayer, &boundingBox ); 
    return VRect(0,0,boundingBox.Width+1,boundingBox.Height+1);// must +1 maybe long truncate the return value of float
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
    rectLayer.Width = 50;//GetLineWidth(); //default 
    rectLayer.Height = 50; 
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
void VContext::DrawString(std::string& str,VRect& layoutRect) {
    std::wstring wstr;
    wchar_t* t;
    t = (wchar_t*)wstr.c_str();
    StringUtil::string_to_wstring(str,wstr);
    
    FontFamily fontfamily(L"Arial");
	Font font(&fontfamily,8,FontStyleRegular,UnitPoint);
 
	m_graphics->SetTextRenderingHint(TextRenderingHintSystemDefault);
    
    VRect rect = layoutRect;
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