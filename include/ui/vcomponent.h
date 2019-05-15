#ifndef VCOMPONENT_H
#define VCOMPONENT_H

#include "config.h"
#include "ui/isizer.h"

namespace violet {
    
    class VComponent : public CWnd, public ISizer{
        public:
            VComponent() {
                m_parent = nullptr;
            }
            VComponent(CWnd& parent);
            VComponent(CWnd& parent,VRect& rect);
            
            virtual VRect GetBounds();
            
            virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
            
            afx_msg void VComponent::OnPaint();
            
            
            static BOOL RegisterClass();
            static BOOL m_classRegistered;
            static LPCTSTR m_className;
        private:
            CWnd* m_parent;
            VRect m_rect;
            
            
            DECLARE_MESSAGE_MAP()
    };
}

#endif
