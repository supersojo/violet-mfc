#ifndef LAYOUT_H
#define LAYOUT_H
#include <vector>
#include "vcontent.h"
#include "separator.h"

namespace violet {
	class Layout : public VContent {
		public:
			Layout(){
				m_separator = Separator::EMPTY;
			}
			virtual~Layout(){
				std::vector<VContent*>::iterator i;
				for (i=m_contents.begin();i!=m_contents.end();i++) {
					delete (*i);
				}
				m_contents.clear();
				
			}
			virtual VPoint GetNextOffset(VPoint& beforeOfset,VContent& content) {
				return VPoint();
			}
			virtual VPoint GetStartPointSeparator(VPoint& offset) {
				return VPoint();
			}
			virtual VPoint GetEndPointSeparator(VPoint& offset) {
				return VPoint();
			}
			virtual void Add(VContent& content) {
				if (&content==nullptr)
					return;
				content.AddParent(*this);
				m_contents.push_back(&content);
				Refresh();
			}
			virtual void Remove(VContent& content) {
				if (&content==nullptr)
					return;
				content.RemoveParent(*this);
				for (int i=0;i<m_contents.size();i++) {
					if (m_contens[i]==&content) {
						m_contents.erase(i);
						break;
					}
				}
				Refresh();
			}
			virtual Separator& GetSeparator() {
				return *m_separator;
			}
			virtual void SetSeparator(Separator& separator) {
				if (&separator==nullptr)
					return;
				m_separator = &separator;
			}
			std::vector<VContent*>& GetContents() {
				return m_contents;
			}
			virtual void RefreshDown() {
				for (int i=0;i<m_contents.size();i++) 
					m_contens[i]->RefreshDown();
				VContent::RefreshDown();
			}
			virtual void Draw(VContext& context) {
				std::<VContent*>::iterator i;
				VPoint offset(0,0);
				VContent* content;
				i = m_contents.begin();
				if (i!=m_contents.end()) {
					content = (*i);
					content->Draw(context,offset);
					i++;
				}
				while (i!=m_contents.end()) {
					offset = GetNextOffset(offset,*content);
					content = (*i);
					content->Draw(context,offset);
					m_separator->Draw(context,GetStartPointSeparator(offset),
						GetEndPointSeparator(offset));
					i++;
					
				}
			}
			VPoint GetLocation(VContent& content) {
				int index = 0;
				VPoint offset(0,0);
				for (int i=0;i<m_contents.size();i++) {
					if (m_contents[i]==&content) {
						index = i;
						break;
					}
				}
				for (int i=0;i<index;i++) {
					offset = GetNextOffset(offset,*m_contents[i]);
				}					
				return offset;
			}
		private:
			Separator* m_separator;
			std::vector<VContent*> m_contents;
	};
}

#endif
