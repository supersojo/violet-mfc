#ifndef VERTICALLAYOUT_H
#define VERTICALLAYOUT_H

namespace violet { 
	class VerticalLayout : public Layout {
		public:
			virtual VPoint GetNextOffset(VPoint& beforeOffset,VContent& content) {
				return VPoint(beforeOffset.GetX(),beforeOffset.GetY()+content.GetHeight());
			}
			virtual VPoint GetStartPointSeparator(VPoint& offset) {
				return VPoint(0,offset.GetY());
			}
			virtual VPoint GetEndPointSeparator(VPoint& offset) {
				return VPoint(GetWidth(),offset.GetY());
			} 
			virtual void RefreshUp() {
				VRect minimalBounds = GetMinimalBounds();
				SetHeight(minimalBounds.GetHeight());
				SetWidth(minimalBounds.GetWidth());
				
				SetContentsWidth(minimalBounds.GetWidth());
				Layout::RefreshUp();
			}
			virtual VRect GetMinimalBounds() {
				VRect selfMinimalBounds = Layout::GetMinimalBounds();
				std::cout<<"self bounds:"<<selfMinimalBounds<<std::endl;
				double width = 0;
				double height = 0;
				std::vector<VContent*>& contents = GetContents();
				for (int i=0;i<contents.size();i++) {
					VRect contentMinimalBounds = contents[i]->GetMinimalBounds();
					height += contentMinimalBounds.GetHeight();
					if (width < contentMinimalBounds.GetWidth()) {
						width = contentMinimalBounds.GetWidth();
					}
				}
				if (height<selfMinimalBounds.GetHeight())
					height = selfMinimalBounds.GetHeight();
				if (width<selfMinimalBounds.GetWidth())
					width = selfMinimalBounds.GetWidth();
				std::cout<<"new bounds:"<<VRect(GetX(),GetY(),width,height)<<std::endl;
				return VRect(GetX(),GetY(),width,height);			
			}
			virtual void SetContentsWidth(double width) {
				std::vector<VContent*>& contents = GetContents();
				for (int i=0;i<contents.size();i++) {
					contents[i]->SetWidth(width);
					contents[i]->RefreshDown();
				}
			}
		private:
		
	};
}

#endif
