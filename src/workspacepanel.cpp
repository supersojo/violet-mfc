#include "workspace/workspacepanel.h"
#include "workspace/isidebar.h"
#include "graph/vrect.h"
#include "graph/vcontext.h"
#include "abstract/igraph.h"
#include "violet.h"

namespace violet {

WorkspacePanel::WorkspacePanel():VComponent() {
    m_workspace = nullptr;
    m_editorPart = nullptr;
    m_sideBar = nullptr;
}

WorkspacePanel::WorkspacePanel(Workspace& workspace,CWnd* parent):VComponent(*parent) {
    m_workspace = &workspace;
    m_editorPart = nullptr;
    m_sideBar = nullptr;
}

WorkspacePanel::WorkspacePanel(Workspace& workspace,CWnd* parent,VRect& rect) :VComponent(*parent,rect) {
    m_workspace = &workspace;
    m_editorPart = nullptr;
    m_sideBar = nullptr;
}

void WorkspacePanel::PrepareLayout() {
}

VComponent& WorkspacePanel::GetEditorPart() {
    if (m_editorPart==nullptr) {
        //IEditorPart* editorPart = m_workspace->GetEditorPart();
    }
    return *m_editorPart;
}

VComponent& WorkspacePanel::GetSiderBar() {
    if (m_sideBar==nullptr) {
        ISideBar* sideBar = &(m_workspace->GetSideBar());
    }
    return *m_sideBar;
}

BEGIN_MESSAGE_MAP(violet::WorkspacePanel, VComponent)
    ON_WM_PAINT()
END_MESSAGE_MAP()

afx_msg void WorkspacePanel::OnPaint() {
#if 0    
    violet::VContext context;
    
    if(m_workspace==nullptr)
        return;
    
    IGraphFile& gf = m_workspace->GetGraphFile();
    if (&gf==nullptr)
        return;
    
    abstract::IGraph& g = gf.GetGraph();
    if (&g==nullptr)
        return;
    
    

    CDC *pDC=CWnd::GetDC();
    
    Gdiplus::Graphics graphics(pDC->GetSafeHdc());
    context.Attach(graphics);
    
    g.Draw(context);
    // Draw what ?
    // get nodes and edge from workspace 
    
    CWnd::ReleaseDC(pDC);
#endif
    HDC         hdc;
    PAINTSTRUCT ps;
    violet::NoteNode node;
    violet::abstract::IGraph* g;
    g = &(node.GetGraph());
    violet::VContext context;
    hdc = ::BeginPaint (GetSafeHwnd(), &ps);
    Gdiplus::Graphics graphics(hdc);
    context.Attach(graphics);
    
    violet::NoteNode node1;
    violet::NoteNode node2;
    violet::LabeledLineEdge edge;

    node1.SetText(std::string("node1"));
    node2.SetText(std::string("node2"));
    g->AddNode(node1,violet::VPoint(50,50));
    g->AddNode(node2,violet::VPoint(150,150));
    violet::VPoint points[] = {
        violet::VPoint(),violet::VPoint()
    };
    edge.SetStartArrowHead(*violet::property::ArrowHeadChoiceList::DIAMOND_WHITE);
    edge.SetEndArrowHead(*violet::property::ArrowHeadChoiceList::DIAMOND_BLACK);
    edge.SetStartLabel(std::string("1..n"));
    edge.SetCenterLabel(std::string("center"));
    edge.SetEndLabel(std::string("1"));
    g->Connect(edge,node1,violet::VPoint(1,1),node2,violet::VPoint(1,1),points);
    g->Draw(context);
    ::EndPaint (GetSafeHwnd(), &ps) ;
}

}
