#ifndef ABSTRACTNODE_H
#define ABSTRACTNODE_H
#include <list>
#include "inode.h"
#include "vcontent.h"
#include "vcontentbackground.h"
#include "vcontentborder.h"
namespace violet {
    class VPoint;
    class VContent;
    namespace abstract {
        class INode;
        class IGraph;
        class Id;
    }
}
/*
 +------------------+<border>
 | +------------+   |
 | |<background |   |
 | | content>   |   |
 | +------------+   |
 +------------------+
*/
namespace violet {
    namespace abstract {
        class AbstractNode : public INode {
            public:
                AbstractNode();
                AbstractNode(const AbstractNode& node);
                ~AbstractNode();
                /* IIdentifiable interface */
                virtual Id& GetId();
                virtual void SetId(Id& id);
                virtual int GetRevision();
                virtual void SetRevision(int rev);
                virtual void IncrementRevision();
                /* INode interface */
                virtual void Reconstruction();
                virtual bool AddConnection(IEdge& edge);
                virtual void RemoveConnection(IEdge& edge);
                virtual bool AddChild(INode& node, VPoint& point);
                virtual bool AddChild(INode& node, int index);
                virtual void RemoveChild(INode& node);
                virtual std::list<INode*>& GetChildren();
                virtual INode& GetParent();
                virtual std::list<INode*>& GetParents();
                virtual void SetParent(INode& parent);
                virtual void SetGraph(IGraph& g);
                virtual IGraph& GetGraph();
                virtual void Translate(double dx,double dy);
                virtual bool Contains(VPoint& point);
                virtual VPoint& GetConnectionPoint(IEdge&edge);
                virtual void SetLocation(VPoint& point);
                virtual VPoint& GetLocation();
                virtual VPoint GetLocationOnGraph();
                virtual VRect GetBounds();
                virtual void Draw(VContext& context);
                virtual int GetZ();
                virtual void SetZ(int z);
                virtual std::string GetToolTip();
                virtual INode& Clone();
                /* others */
                virtual void onChildChangeLocation(INode& child);
                
                virtual void BeforeReconstruction() {
                }
                virtual void AfterReconstruction() {
                    GetContent().Refresh();
                }
                void CreateContentStructure();
                void SetBorder(VContentBorder& border) {
                    m_border = &border;
                }
                VContentBorder& GetBorder() {
                    if (m_border==nullptr)
                        GetContent();
                    return *m_border;
                }
                
                VContent& GetContent() {
                    if (m_content==nullptr)
                        Reconstruction();
                    return *m_content;
                }
                void SetContent(VContent& content) {
                    m_content = &content;
                }
                void SetBackground(VContentBackground& background) {
                    m_background = &background;
                }
                VContentBackground& GetBackground() {
                    if (m_background==nullptr)
                        GetContent();
                    return *m_background;
                }
            private:
                Id* m_id;
                int m_revision;
                VPoint* m_location;
                std::list<INode*> m_children;
                INode* m_parent;
                IGraph* m_graph;
                int m_z;
                VContent* m_content;
                
                VContentBackground* m_background;
                VContentBorder* m_border;
                
                VColor m_backgroundColor;
                VColor m_borderColor;
                VColor m_textColor;
        };
    }
}

#endif
