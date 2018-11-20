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
    
}

void NoteNode::Draw(VContext& context) {
    AbstractNode::Draw(context);
    // additional draw
}
void NoteNode::SetTextColor(VColor& color) {
    AbstractNode::SetTextColor(color);
    m_lineText->SetTextColor(color);
}


}