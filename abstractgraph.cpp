#include <list>
#include "abstractgraph.h"
#include "inode.h"
#include "iedge.h"
#include "abstractnode.h"
#include "notenode.h"
namespace violet {
    namespace abstract {
    
        AbstractGraph::AbstractGraph() {
            m_gridSticker = nullptr;
        }
        std::vector<INode*> AbstractGraph::GetAllNodes() {
			std::cout<<"GetAllNodes"<<std::endl;
            std::vector<INode*> fifo;
            std::vector<INode*> r;
            for (int i=0;i<m_nodes.size();i++) {
                fifo.push_back(m_nodes[i]);
                r.push_back(m_nodes[i]);
            }
            while (!fifo.empty()) {
                
                std::vector<INode*>::iterator iter;
                iter = fifo.begin();
                
                std::list<INode*>& children = (*iter)->GetChildren();
                fifo.erase(iter);
				
                std::list<INode*>::iterator i;
                for (i=children.begin();i!=children.end();i++) {
                    fifo.push_back(*i);
                    r.push_back(*i);
                }
            }
            // maybe revserse vector
            // so find node will speed 
			for (int i=0;i<r.size();i++) {
				std::cout<<r[i]->GetLocation();
			}
			std::cout<<std::endl;
            return r;
            
        }
        std::vector<IEdge*> AbstractGraph::GetAllEdges() {
            return m_edges;
        }
        
        void AbstractGraph::RemoveEdge(IEdge &edge) {
            INode& start = edge.GetStartNode();
            INode& end = edge.GetEndNode();
            start.RemoveConnection(edge);
            end.RemoveConnection(edge);
            std::vector<IEdge*>::iterator iter;
            for (iter = m_edges.begin();iter!=m_edges.end();iter++)
                if ((*iter) == &edge) {
                    //delete edge? Need
                    m_edges.erase(iter);
                    return;
                }
        }
        void AbstractGraph::RemoveNode(INode &node) {
            // 1a direct on graph
            std::vector<INode*>::iterator iter;
            for (iter = m_nodes.begin();iter!=m_nodes.end();iter++)
                if ((*iter) == &node) {
                    //delete node? Need
                    m_nodes.erase(iter);
                }
            // 1b attached to other node on graph
            std::vector<INode*>& allNodes = GetAllNodes();
            
            std::vector<INode*>::iterator i;
            for (i = allNodes.begin();i!=allNodes.end();i++)
            {
                std::list<INode*>& children = (*i)->GetChildren();
                
                std::list<INode*>::iterator j;
                for (j = children.begin();j!=children.end();j++)
                    if ((*j)==&node) {
                        (*i)->RemoveChild(node);
                    }
            }
            // 2 disconnect edges
            std::vector<INode*>& restNodes = GetAllNodes();
            std::vector<IEdge*>::iterator i_edge;
            for (i_edge=m_edges.begin();i_edge!=m_edges.end();i_edge++) {
                //
                INode* start = &((*i_edge)->GetStartNode());
                INode* end = &((*i_edge)->GetEndNode());
                if (!(HasNode(*start) && HasNode(*end))) {
                    RemoveEdge(*(*i_edge));
                }
            }
           
        }
        
        bool AbstractGraph::AddNode(INode& node,VPoint& point) {
            node.SetGraph(*this);
            // 1 notenode
            if (dynamic_cast<NoteNode*>(&node)) {
                node.SetLocation(point);
                m_nodes.push_back(&node);
                return true;
            }
            // 2 attached to an node
            INode* potentialParentNode = &FindNode(point);
            if (potentialParentNode!=nullptr) {
                VPoint parentLocationOnGraph = potentialParentNode->GetLocationOnGraph();
                VPoint relativeLocation(point.GetX() - parentLocationOnGraph.GetX(),
                                        point.GetY() - parentLocationOnGraph.GetY());
                //
                return potentialParentNode->AddChild(node,relativeLocation);
            }
            // 3 directly on graph
            node.SetLocation(point);
            node.SetParent(*reinterpret_cast<INode*>(nullptr));
            m_nodes.push_back(&node);
            return true;
        }
        
        bool AbstractGraph::Connect(IEdge& edge,INode& start,VPoint& startLocation,
                                 INode& end,VPoint& endLocation,
                                 VPoint transitionPoints[]) {
            //
			std::cout<<"-------connect---------"<<std::endl;
            std::vector<INode*>& allNodes = GetAllNodes();
            if (&start!=nullptr && !HasNode(start))
                AddNode(start,start.GetLocation());
            if (&end!=nullptr && !HasNode(end))
                AddNode(end,end.GetLocation());
            edge.SetStartNode(start);
            edge.SetStartLocation(startLocation);
            edge.SetEndNode(end);
            edge.SetEndLocation(endLocation);
            edge.SetTransitionPoints(transitionPoints);
            if (&start!=nullptr && start.AddConnection(edge)) {
				std::cout<<&edge<<" added"<<std::endl;
                m_edges.push_back(&edge);
                AbstractNode* snode = dynamic_cast<AbstractNode*>(&start);
                if (snode!=nullptr)
                    snode->onConnectedEdge(edge);
                if (&end!=nullptr) {
                    AbstractNode* enode = dynamic_cast<AbstractNode*>(&end);
                    if (enode!=nullptr)
                        enode->onConnectedEdge(edge);
                }
                return true;
            }
            return false;
        }
        
        INode& AbstractGraph::FindNode(Id& id) {
            std::vector<INode*>& allNodes = GetAllNodes();
            std::vector<INode*>::iterator i;
            for (i=allNodes.begin();i!=allNodes.end();i++) {
                if(&((*i)->GetId())==&id)
                    return *(*i);
            }
            return *reinterpret_cast<INode*>(nullptr);
        }
        INode& AbstractGraph::FindNode(VPoint& point) {
            std::vector<INode*>& allNodes = GetAllNodes();
            std::vector<INode*>::iterator i;
            for (i=allNodes.begin();i!=allNodes.end();i++) {
                VPoint locationOnGraph = (*i)->GetLocationOnGraph();
                VRect bounds = (*i)->GetBounds();
                VRect boundsToCheck(locationOnGraph.GetX(),
                                    locationOnGraph.GetY(),
                                    bounds.GetSize().GetX(),
                                    bounds.GetSize().GetY()
                                    );
                if (boundsToCheck.Contains(point))
                    return *(*i);
            }
            return *reinterpret_cast<INode*>(nullptr);
        }
       
        IEdge& AbstractGraph::FindEdge(Id& id) {
            std::vector<IEdge*>::iterator i;
            for (i=m_edges.begin();i!=m_edges.end();i++) {
                if(&((*i)->GetId())==&id)
                    return *(*i);
            }
            return *reinterpret_cast<IEdge*>(nullptr);
        }
        IEdge& AbstractGraph::FindEdge(VPoint& point) {
            std::vector<IEdge*>::iterator i;
            for (i=m_edges.begin();i!=m_edges.end();i++) {
                if((*i)->Contains(point))
                    return *(*i);
            }
            return *reinterpret_cast<IEdge*>(nullptr);
        }
        
        void AbstractGraph::Draw(VContext& context) {
            std::vector<INode*> specialNodes;
            int count = 0;
            int z = 0;
            std::vector<INode*>& allNodes = GetAllNodes();
            while (count<allNodes.size()) {
                std::vector<INode*>::iterator i;
                for (i=allNodes.begin();i!=allNodes.end();i++) {
                    if ((*i)->GetZ() == z) {
                        //
                        if (dynamic_cast<NoteNode*>(*i)) {
							std::cout<<"speical node???"<<std::endl;
                            specialNodes.push_back(*i);
                        } else {
							std::cout<<"==== node???"<<std::endl;
                            if (&((*i)->GetParent())==nullptr)
                                (*i)->Draw(context);
                        }
                        count++;
                    }
                }
                z++;
            }
			std::cout<<"draw edges"<<std::endl;
            // edges
            std::vector<IEdge*>::iterator i;
            for (i=m_edges.begin();i!=m_edges.end();i++) {
                (*i)->Draw(context);
            }
			std::cout<<"draw special nodes"<<std::endl;
            // special nodes
            std::vector<INode*>::iterator j;
            for (j=specialNodes.begin();j!=specialNodes.end();j++) {
                //VPoint nodeLocationOnGraph = (*j)->GetLocationOnGraph();
                //VPoint nodeLocation = (*j)->GetLocation();
                //translate ?
                (*j)->Draw(context);
            }
        }
        
        VRect AbstractGraph::GetClipBounds() {
            std::vector<INode*>::iterator i;
            for (i=m_nodes.begin();i!=m_nodes.end();i++) {
                VRect b = (*i)->GetBounds();
                UpdateMinBounds(b);
            }
            std::vector<IEdge*>::iterator j;
            for (j=m_edges.begin();j!=m_edges.end();j++) {
                VRect b = (*j)->GetBounds();
                UpdateMinBounds(b);
            }
            return m_minBounds;
        }
        void AbstractGraph::SetBounds(VRect& rect) {
            m_minBounds = rect;
        }
        
        IGridSticker& AbstractGraph::GetGridSticker() {
            return *reinterpret_cast<IGridSticker*>(nullptr); 
        }
        void AbstractGraph::SetGridSticker(IGridSticker& gridSticker) {
            m_gridSticker = &gridSticker;
        }
        /* others */
        bool AbstractGraph::HasNode(INode& node) {
            std::vector<INode*>& allNodes = GetAllNodes();
            std::vector<INode*>::iterator i;
            for (i=allNodes.begin();i!=allNodes.end();i++)
                if ((*i) == &node)
                    return true;
            return false;
        }
        void AbstractGraph::UpdateMinBounds(VRect& b) {
            int x = m_minBounds.GetLocation().GetX();
            int y = m_minBounds.GetLocation().GetY();
            int x1;
            int y1;
            int x2;
            int y2;
            int w;
            int h;
            if (m_minBounds.GetLocation().GetX() > b.GetLocation().GetX())
                x = b.GetLocation().GetX();
            if (m_minBounds.GetLocation().GetY() > b.GetLocation().GetY())
                y = b.GetLocation().GetY();
            x1 = m_minBounds.GetLocation().GetX() + m_minBounds.GetSize().GetX();
            y1 = m_minBounds.GetLocation().GetY() + m_minBounds.GetSize().GetY();
            x2 = b.GetLocation().GetX() + b.GetSize().GetX();
            y2 = b.GetLocation().GetY() + b.GetSize().GetY();
            w = x1;
            h = y1;
            if (x1<x2)
                w = x2;
            if (y1<y2)
                h = y2;
            m_minBounds.SetLocation(x,y);
            m_minBounds.SetSize(w-x,h-y);
        }
    }
}