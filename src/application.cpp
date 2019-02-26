#ifndef UMLAPPLICATION_H
#define UMLAPPLICATION_H

#define _WIN32_WINNT 0x0502

#include <afxwin.h>

namespace violet {

    class UMLApplication : public CWinApp {
        public:
            virtual BOOL InitInstance();
    };
    
    class UMLMainFrame : public CFrameWnd {
        public:
            UMLMainFrame();
            
            DECLARE_MESSAGE_MAP()
    };
}

violet::UMLApplication app;

BOOL violet::UMLApplication::InitInstance() {
    violet::UMLMainFrame *frame = new violet::UMLMainFrame();
    frame->ShowWindow(SW_SHOWNORMAL);
    frame->UpdateData();
    m_pMainWnd = frame;
    
    return TRUE;
}

BEGIN_MESSAGE_MAP(violet::UMLMainFrame, CFrameWnd)
END_MESSAGE_MAP()

violet::UMLMainFrame::UMLMainFrame() {
    Create(NULL,TEXT("UML"));
}

#endif

