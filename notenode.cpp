#include "notenode.h"
#include "vcontenttext.h"
#include "vcontentinrectangle.h"
#include "vcontentborder.h"
#include "vcontentbackground.h"
namespace violet {
    
void NoteNode::CreateContentStructure() {
    m_lineText = new VLineText;
    VContentText* textContent = new  VContentText(*m_lineText); 
    textContent->SetMinHeight(40);
    textContent->SetMinWidth(60);
    VContentInShape* contentInShape = new  VContentInRectangle(*textContent);
    VContentBorder* border =  new  VContentBorder(*contentInShape,GetBorderColor());
    SetBorder(*border);
    VContentBackground* background =  new  VContentBackground(GetBorder(),GetBackgroundColor());
    SetBackground(*background);
    SetContent(GetBackground());
    
    SetBackgroundColor(VColor(255,255,255));
    SetBorderColor(VColor(0,0,0));
    SetTextColor(VColor(255,165,0));
    
    m_textChanged = false;
}

void NoteNode::SetText(std::string& str) {
    m_lineText->SetText(str);
    // how to calc linetext's bounds?
    // we need context
    m_textChanged = true;
}
void NoteNode::Draw(VContext& context) {
    if (m_textChanged) {
        m_lineText->UpdateBounds(context);
        std::cout<<"linetext:"<<m_lineText->GetText()<<":"<<m_lineText->GetBounds()<<std::endl;
        m_lineText->GetContent().RefreshUp();
        m_textChanged = false;
    }
    AbstractNode::Draw(context);
    // additional draw
}
void NoteNode::SetTextColor(VColor& color) {
    AbstractNode::SetTextColor(color);
    m_lineText->SetTextColor(color);
}


}