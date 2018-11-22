#ifndef VCONTENT_H
#define VCONTENT_H
#include <list>
#include "vrect.h"
#include "vcontext.h"

namespace violet {
    class VContent {
        public:
            VContent() {
                m_width = 0;
                m_height = 0;
                m_minWidth = 0;
                m_minHeight = 0;
            }
            virtual ~VContent() {
            }
            virtual bool Contains(VPoint& point) {
                VRect rect = GetBounds();
                
                if(((point.GetX() > rect.GetLocation().GetX()) &&
                    (point.GetX() < rect.GetLocation().GetX()+rect.GetSize().GetX())) &&
                   ((point.GetY() > rect.GetLocation().GetY()) &&
                    (point.GetY() < rect.GetLocation().GetY()+rect.GetSize().GetY())))
                    return true;
                
                return false;
            }
            virtual void Draw(VContext& context) {
            }
            virtual void Draw(VContext& context,VPoint& offset) {
                context.Translate(offset.GetX(),offset.GetY());
                Draw(context);
                context.Translate(-offset.GetX(),-offset.GetY());
            }
            double GetX() {
                return 0;
            }
            double GetY() {
                return 0;
            }
            double GetWidth() {
                return m_width>m_minWidth?m_width:m_minWidth;
            }
            void SetWidth(double w) {
                m_width = w;
            }
            void SetHeight(double h) {
                m_height = h;
            }
            double GetHeight() {
                return m_height>m_minHeight?m_height:m_minHeight;
            }
            VRect GetBounds() {
                return VRect(GetX(),GetY(),GetWidth(),GetHeight());
            }
            virtual VRect GetMinimalBounds() {
                return VRect(GetX(),GetY(),m_minWidth,m_minHeight);
            }
            void SetMinWidth(double w) {
                m_minWidth = w;
                RefreshUp();
            }
            void SetMinHeight(double h) {
                m_minHeight = h;
                RefreshUp();
            }
            void Refresh() {
                RefreshUp();
                RefreshDown();
            }
            virtual void RefreshUp() {
                std::list<VContent*>::iterator iter;
                for(iter = m_parents.begin(); iter!=m_parents.end();++iter)
                    (*iter)->RefreshUp();
            }
            virtual void RefreshDown() {
            }
            void AddParent(VContent& parent) {
                m_parents.push_front(&parent);
            }
            void RemoveParent(VContent& parent) {
                std::list<VContent*>::iterator iter;
                for(iter = m_parents.begin(); iter!=m_parents.end();++iter)
                    if((*iter) == &parent) {
                        m_parents.erase(iter);
                        return;
                    }
                Refresh();
            }
            
        private:
            std::list<VContent*> m_parents;
            double m_width;
            double m_height;
            double m_minWidth;
            double m_minHeight;
    };
}

#endif
