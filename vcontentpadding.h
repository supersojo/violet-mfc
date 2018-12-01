#ifndef VCONTENTPADDING_H
#define VCONTENTPADDING_H

namespace violet {

	class VContentPadding : public VContent {
		public:
			VContentPadding(VContent& content,double padding) 
			: VContentPadding(content,padding,padding){
			}
			VContentPadding(VContent& content,double vertical,double horizontal) 
			: VContentPadding(content,vertical,vertical,horizontal,horizontal) {
			}
			VContentPadding(VContent& content,double top,double bottom,double left,double right) {
				m_top = new VContentEmpty;
				m_bottom = new VContentEmpty;
				m_left = new VContentEmpty;
				m_right = new VContentEmpty;
				
				m_layout = new VerticalLayout;
				
				m_content = content;
				
				SetTopPadding(top);
				SetBottomPadding(bottom);
				SetLeftPadding(left);
				SetRightPadding(right);
				/*
				 +----------------------+
				 | m_top                |
				 +----------------------+
				 |m_left|content|m_right|  <== horizontal layout
				 +----------------------+
				 | m_bottom             |
				 +----------------------+
				 
				   ^^
				   ||
				   vertical layout
				*/
				HorizontalLayout* horizontalLayout = new HorizontalLayout;
				horizontalLayout->Add(*m_left);
				horizontalLayout->Add(content);
				horizontalLayout->Add(*m_right);
				
				m_layout->Add(*m_top);
				m_layout->Add(*horizontalLayout);
				m_layout->Add(*m_bottom);
				
				m_content->AddParent(*this);
			}
			virtual void Draw(VContext& context) {
				m_layout->Draw(context);
			}
			virtual void RefreshDown() {
				m_content->RefreshDown();
				VContent::RefreshDown();
			}
			VRect GetMinimalBounds() {
				return m_layout->GetMinimalBounds();
			}
			void SetTopPadding(double top) {
				if (top<0)
					return;
				m_top->SetMinHeight(top);
				RefreshUp();
			}
			void SetBottomPadding(double bottom) {
				if (bottom<0)
					return;
				m_bottom->SetMinHeight(bottom);
				RefreshUp();
			}
			void SetLeftPadding(double left) {
				if (left<0)
					return;
				m_left->SetMinWidth(left);
				RefreshUp();
			}
			void SetRightPadding(double right) {
				if (right<0)
					return;
				m_right->SetMinWidth(right);
				RefreshUp();
			}
		private:
			VContentPadding(){}// disallow default construct
			VContent* m_content;// the real content
			Layout* m_layout;// the top laytou
			VContentEmpty* m_top;
			VContentEmpty* m_bottom;
			VContentEmpty* m_left;
			VContentEmpty* m_right;
	};
}

#endif
