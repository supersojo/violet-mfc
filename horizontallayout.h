#ifndef HORIZONTALLAYOUT_H
#define HORIZONTALLAYOUT_H
#include "layout.h"

namespace violet {
	class HorizontalLayout:public Layout {
		public:
			HorizontalLayout(){}
			virtual VPoint GetNextOffset(VPoint& beforeOffset,VContent& content) {
				return VPoint(beforeOffset.GetX()+content.GetWidth(),beforeOffset.GetY());
			}
			virtual VPoint GetStartPointSeparator(VPoint& offset) {
				return VPoint(offset.GetX(),0);
			}
			virtual VPoint GetEndPointSeparator(VPoint& offset) {
				return VPoint(offset.GetX(),GetHeight());
			}
			virtual void RefreshUp() {
				VRect minimalBounds = GetMinimalBounds();
				SetHeight(minimalBounds.GetHeight());
				SetWidth(minimalBounds.GetWidth());
				
				SetContentsHeight(minimalBounds.GetHeight());
				Layout::RefreshUp();
			}
			virtual VRect GetMinimalBounds() {
				VRect selfMinimalBounds = Layout::GetMinimalBounds();
				double width = 0;
				double height = 0;
				std::vector<VContent*>& contents = GetContents();
				for (int i=0;i<contents.size();i++) {
					VRect contentMinimalBounds = contents[i]->GetMinimalBounds();
					width += contentMinimalBounds.GetWidth();
					if (height < contentMinimalBounds.GetHeight()) {
						height = contentMinimalBounds.GetHeight();
					}
				}
				if (height<selfMinimalBounds.GetHeight())
					height = selfMinimalBounds.GetHeight();
				if (width<selfMinimalBounds.GetWidth())
					width = selfMinimalBounds.GetWidth();
				return VRect(GetX(),GetY(),width,height);			
			}
			virtual void SetContentsHeight(double height) {
				std::vector<VContent*>& contents = GetContents();
				for (int i=0;i<contents.size();i++) {
					contents[i]->SetHeight(height);
					contents[i]->RefreshDown();
				}
			}
	};
}

#endif
