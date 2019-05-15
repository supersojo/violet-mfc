#include "ui/vcomponent.h"
#include <iostream>

namespace violet {

BOOL VComponent::PreCreateWindow(CREATESTRUCT& cs) {
    cs.style |= WS_CHILD;
    return CWnd::PreCreateWindow(cs);
}

VComponent::VComponent(CWnd& parent) : VComponent(parent,VRect(0,0,100,100)){
}

VComponent::VComponent(CWnd& parent,VRect& rect) {
    BOOL ret = false;
    m_parent = &parent;
    if (!m_classRegistered) {
        ret = VComponent::RegisterClass();
        m_classRegistered = true;
        std::cout<<"register class ok!"<<std::endl;
    }
    RECT rect1{rect.GetX(),rect.GetY(),rect.GetX()+rect.GetWidth(),rect.GetY()+rect.GetHeight()};
    ret = CWnd::CreateEx(0,VComponent::m_className,"vcomponent",WS_CHILD|WS_BORDER|WS_VISIBLE,rect1,
                    m_parent,0,NULL);
    if (ret)
        std::cout<<"createex ok!"<<std::endl;
}

BOOL VComponent::RegisterClass() {
    m_className = AfxRegisterWndClass(CS_DBLCLKS,NULL,(HBRUSH)(COLOR_3DFACE+1),NULL);
    return true;
}

VRect VComponent::GetBounds() {
    return m_rect;
}

BOOL VComponent::m_classRegistered = false;
LPCTSTR VComponent::m_className = nullptr;



BEGIN_MESSAGE_MAP(violet::VComponent, CWnd)
    ON_WM_PAINT()
END_MESSAGE_MAP()

afx_msg void VComponent::OnPaint() {
   PAINTSTRUCT ps;
   CDC* pDC = BeginPaint(&ps);

   pDC->Rectangle(CRect(0, 0, 20, 30));

   EndPaint(&ps);

}

}//end violet