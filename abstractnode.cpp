#include<algorithm>
#include "abstractnode.h"
#include "inode.h"
#include "iedge.h"
#include "vpoint.h"
#include "vrect.h"
#include "direction.h"
#include "vcontent.h"
#include "vcontentinrectangle.h"
#include "vcontentindiamond.h"
namespace violet {
    namespace abstract {
        AbstractNode::AbstractNode() {
            m_revision = 0;
            m_content = nullptr;
            m_parent = nullptr;
            m_graph = nullptr;
            m_background = nullptr;
            m_border = nullptr;
        }
        AbstractNode::AbstractNode(const AbstractNode& node) {
        }
        AbstractNode::~AbstractNode() {
            if (m_content!=nullptr)
                delete m_content;
        }
        /* IIdentifiable interface */
        Id& AbstractNode::GetId() {
            return (m_id);
        }
        void AbstractNode::SetId(Id& id) {
            m_id.SetValue(id.GetValue());
        }
        int AbstractNode::GetRevision() {
            return m_revision;
        }
        void AbstractNode::SetRevision(int rev) {
            m_revision = rev;
        }
        void AbstractNode::IncrementRevision() {
            m_revision++;
        }
        /* INode interface */
        void AbstractNode::Reconstruction() {
            BeforeReconstruction();
            CreateContentStructure();
            AfterReconstruction();
        }
        bool AbstractNode::AddConnection(IEdge& edge) {
            INode& endNode = edge.GetEndNode();
            if (&endNode == nullptr) {
                edge.SetEndNode(edge.GetStartNode());
                edge.SetEndLocation(edge.GetStartLocation());
            }
            INode& t = edge.GetEndNode();
            return (&t!=nullptr);
        }
        void AbstractNode::RemoveConnection(IEdge& edge) {
        }
        bool AbstractNode::AddChild(INode& node, VPoint& point) {
            return false;
        }
        bool AbstractNode::AddChild(INode& node, int index) {
            int i = 0;
            std::list<INode*>::iterator iter;
            for (iter=m_children.begin();iter!=m_children.end();++iter)
                if (i==index)
                    break;
                else
                    i++;
            INode& oldParent = node.GetParent();
            if (&oldParent!=nullptr)
                oldParent.RemoveChild(node);
            if (iter!=m_children.end())
                GetChildren().insert(iter,&node);
            node.SetParent(*this);
            node.SetGraph(GetGraph());
            return true;
        }
        void AbstractNode::RemoveChild(INode& node) {
            INode& parent = node.GetParent();
            if (&parent!=this)
                return;
            std::list<INode*>::iterator iter;
            for (iter=m_children.begin();iter!=m_children.end();++iter)
                 if ((*iter)==&node) {
                     m_children.erase(iter);
                     return;
                 }
        }
        std::list<INode*>& AbstractNode::GetChildren() {
            return m_children;
        }
        INode& AbstractNode::GetParent() {
            if (m_parent)
                return (*m_parent);
            else
                return *(reinterpret_cast<INode*>(nullptr));
        }
        std::list<INode*>& AbstractNode::GetParents() {
            std::list<INode*> * parents = new std::list<INode*>;
            
            INode* p = &GetParent();
            if (p!=nullptr) {
                parents->push_front(p);
                while(&p->GetParent()!=nullptr){
                    INode* q = &p->GetParent();
                    parents->push_front(q);
                    p = q;
                }
            }
            return (*parents);
        }
        void AbstractNode::SetParent(INode& parent) {
            m_parent = &parent;
        }
        void AbstractNode::SetGraph(IGraph& g) {
            m_graph = &g;
            std::list<INode*>::iterator i;
            for (i=m_children.begin();i!=m_children.end();i++) {
                (*i)->SetGraph(g);
            }
        }
        IGraph& AbstractNode::GetGraph() {  
            if (m_graph==nullptr)
                    return *new NodeGraph;
            return (*m_graph);
        }
        void AbstractNode::Translate(double dx,double dy) {
            m_location.SetX(m_location.GetX()+dx);
            m_location.SetY(m_location.GetY()+dy);
        }
        bool AbstractNode::Contains(VPoint& point) {
            return true;
        }
        VPoint AbstractNode::GetConnectionPoint(IEdge&edge) {
			std::vector<IEdge*>& edgesOnSameSide = GetEdgesOnSameSide(edge);
			int position = 0;
			int size = edgesOnSameSide.size();
			std::cout<<"===edgesonsameside======="<<edgesOnSameSide.size()<<std::endl;
			for (int i=0;i<size;i++) {
				if (edgesOnSameSide[i] == &edge) {
					
					position = i;
					std::cout<<"===edgesonsameside position ======="<<position<<std::endl;
					break;
				}
			}

			Direction edgeDirection = edge.GetDirection(*this);
			VPoint startingNodeLocation = GetLocation();

			double x = startingNodeLocation.GetX();
			double y = startingNodeLocation.GetY();
			Direction nearestCardinalDirection = edgeDirection.GetNearestCardinalDirection();
			/*
			    0 1 2
			  +---------+
			0 |         | 0 
			1 |         | 1
			2 |         | 2
			  +---------+
			   0 1 2 
			*/
			if (nearestCardinalDirection.Equals(Direction::NORTH))
			{
				std::cout<<"for north :"<<size<<","<<position;
				x += ((double)GetContent().GetWidth() / (size + 1)) * (position + 1);
			}
			else if (nearestCardinalDirection.Equals(Direction::SOUTH))
			{
				std::cout<<"for south :"<<size<<","<<position;
				x += ((double)GetContent().GetWidth() / (size + 1)) * (position + 1);
				y += (double)GetContent().GetHeight();
			}
			else if (nearestCardinalDirection.Equals(Direction::EAST))
			{
				x += GetContent().GetWidth();
				std::cout<<"height"<<GetContent().GetHeight()<<position;
				y += ((double)GetContent().GetHeight() / (size + 1)) * (position + 1);
			}
			else if (nearestCardinalDirection.Equals(Direction::WEST))
			{
				std::cout<<VPoint(x,y)<<std::endl;
				double dy = GetContent().GetHeight() / (size + 1);
				std::cout<<GetContent().GetHeight()<<"=============dx:"<<dy<<std::endl;
				y += ((double)(GetContent().GetHeight()) / (size + 1)) * (position + 1);
			}
			std::cout<<VPoint(x,y)<<std::endl;
			return VPoint(x,y);
        }
        void AbstractNode::SetLocation(VPoint& point) {
            m_location.SetX(point.GetX());
            m_location.SetY(point.GetY());
            if (m_parent!=nullptr)
                (reinterpret_cast<AbstractNode*>(m_parent))->onChildChangeLocation( (*this) );
        }
        VPoint& AbstractNode::GetLocation() {
            return (m_location);
        }
        VPoint AbstractNode::GetLocationOnGraph() {
            INode& parent = GetParent();
            if (&parent == nullptr)
                return GetLocation();
            VPoint& parentLocationOnGraph = parent.GetLocationOnGraph();
            VPoint& relativeLocation = GetLocation();
            return VPoint(parentLocationOnGraph.GetX()+relativeLocation.GetX(),
                          parentLocationOnGraph.GetY()+relativeLocation.GetY());
        }
        VRect AbstractNode::GetBounds() {
            VPoint& location = GetLocation();
            VRect contentBounds = GetContent().GetBounds();
            return VRect(location.GetX(),
                         location.GetY(),
                         contentBounds.GetSize().GetX(),
                         contentBounds.GetSize().GetY()
                         );
        }
        void AbstractNode::Draw(VContext& context) {
            GetContent().Draw(context,GetLocationOnGraph());
        }
        int AbstractNode::GetZ() {
            return m_z;
        }
        void AbstractNode::SetZ(int z) {
            m_z = z;
        }
        std::string AbstractNode::GetToolTip() {
            return std::string("");
        }
        INode& AbstractNode::Clone() {
            return *reinterpret_cast<INode*>(nullptr);
        }
        /* IColorableNode interface */
        void AbstractNode::SetBackgroundColor(VColor& bgColor) {
            m_backgroundColor = bgColor;
            if (m_background!=nullptr)
                m_background->SetBackgroundColor(bgColor);
        }
        VColor& AbstractNode::GetBackgroundColor() {
            return m_backgroundColor;
        }
        void AbstractNode::SetBorderColor(VColor& borderColor) {
            m_borderColor = borderColor;
            if (m_border!=nullptr)
                m_border->SetBorderColor(borderColor);
        }
        VColor& AbstractNode::GetBorderColor() {
            return m_borderColor;
        }
        void AbstractNode::SetTextColor(VColor& textColor) {
            m_textColor = textColor;
        }
        VColor& AbstractNode::GetTextColor() {
            return m_textColor;
        }
        /* others */
		bool AbstractNode::SortEdgeByX( IEdge* e1, IEdge* e2) {
			Direction d1 = e1->GetDirection(*this);
			Direction d2 = e2->GetDirection(*this);
			return d1.GetX()<d2.GetX();
		}
		bool AbstractNode::SortEdgeByY( IEdge* e1, IEdge* e2) {
			Direction d1 = e1->GetDirection(*this);
			Direction d2 = e2->GetDirection(*this);
			return d1.GetY()<d2.GetY();
		}
        std::vector<IEdge*> AbstractNode::GetConnectedEdges() {
            std::vector<IEdge*> r;
            IGraph& graph = GetGraph();
            std::vector<IEdge*> edges = graph.GetAllEdges();
			std::cout<<"getalledges:"<<edges.size()<<std::endl;
            std::vector<IEdge*>::iterator i;
			std::cout<<"this : "<<this<<std::endl;
            for (i=edges.begin();i!=edges.end();i++) {
                INode& start = (*i)->GetStartNode();
                INode& end = (*i)->GetEndNode();
				std::cout<<"start and end : "<<&start<<","<<&end<<std::endl;
                if ((this == &start) ||
                    (this == &end)) {
                    r.push_back((*i));
                }
            }
			std::cout<<"getconnectededges:"<<r.size()<<std::endl;
            return r;
        }
        std::vector<IEdge*> AbstractNode::GetEdgesOnSameSide(IEdge& edge) {
            std::vector<IEdge*> r;
            std::vector<IEdge*> connectedEdges;
            Direction d = edge.GetDirection(*this);
            if (d.GetX()==0 && d.GetY()==0) {
				std::cout<<"getedgesonsameside null?"<<std::endl;
                return r;
			}
            Direction cardinalDirectionToSearch = d.GetNearestCardinalDirection();
            // continue
            connectedEdges = GetConnectedEdges();
            std::vector<IEdge*>::iterator i;
            for (i=connectedEdges.begin();i!=connectedEdges.end();i++) {
                Direction edgeDirection = (*i)->GetDirection(*this);
                Direction nearestCardinalDirection = edgeDirection.GetNearestCardinalDirection();
                if ((cardinalDirectionToSearch.GetX()==nearestCardinalDirection.GetX()) &&
                    (cardinalDirectionToSearch.GetY()==nearestCardinalDirection.GetY()))
                    r.push_back((*i));
                if (((&((*i)->GetStartNode())) == (&((*i)->GetEndNode()))) &&
                    ((&((*i)->GetStartNode())) == this)) {
                    // self loop
                    r.push_back((*i));
                }
            }
            // sort 
			#if 0
			if ((cardinalDirectionToSearch.Equals(Direction::NORTH)) ||
			    (cardinalDirectionToSearch.Equals(Direction::SOUTH)))
				sort(r.begin(),r.end());
			if ((cardinalDirectionToSearch.Equals(Direction::EAST)) ||
			    (cardinalDirectionToSearch.Equals(Direction::WEST)))
				sort(r.begin(),r.end());
			#endif
			return r;
        }
        void AbstractNode::onChildChangeLocation(INode& child) {
        }
        void AbstractNode::CreateContentStructure() {
            VContentBorder* border = new VContentBorder(
                (*(new VContentInDiamond((*(new VContentEmpty))))),
                GetBorderColor()
                );
            SetBorder(*border);
            VContentBackground* background = new VContentBackground(
                 GetBorder(),
                 GetBackgroundColor()
                 );
            
            SetBackground(*background);
            
            SetContent(GetBackground());
        }
    }
}    