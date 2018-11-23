#ifndef INODE_H
#define INODE_H

#include <list>
#include "iidentifiable.h"

namespace violet {
    
    class VPoint;
    class VRect;
    class VContext;
    
    namespace abstract {
        class IEdge;
        class IGraph;
    }
}

namespace violet {
    namespace abstract {
        class INode : public IIdentifiable{
            public:
                virtual void Reconstruction() = 0;
                virtual bool AddConnection(IEdge& edge) = 0;
                virtual void RemoveConnection(IEdge& edge) = 0;
                virtual bool AddChild(INode& node, VPoint& point) = 0;
                virtual bool AddChild(INode& node, int index) = 0;
                virtual void RemoveChild(INode& node) = 0;
                virtual std::list<INode*>& GetChildren() = 0;
                virtual INode& GetParent() = 0;
                virtual std::list<INode*>& GetParents() = 0;
                virtual void SetParent(INode& parent) = 0;
                virtual void SetGraph(IGraph& g) = 0;
                virtual IGraph& GetGraph() = 0;
                virtual void Translate(double dx,double dy) = 0;
                virtual bool Contains(VPoint& point) = 0;
                virtual VPoint GetConnectionPoint(IEdge&edge) = 0;
                virtual void SetLocation(VPoint& point) = 0;
                virtual VPoint& GetLocation() = 0;
                virtual VPoint GetLocationOnGraph() = 0;
                virtual VRect GetBounds() = 0;
                virtual void Draw(VContext& context) = 0;
                virtual int GetZ() = 0;
                virtual void SetZ(int z) = 0;
                virtual std::string GetToolTip() = 0;
                virtual INode& Clone() = 0;
        };
    }

}

#endif

