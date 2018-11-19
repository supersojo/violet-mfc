#include "abstractnode.h"
#include "inode.h"
#include "iedge.h"
#include "vpoint.h"
#include "vrect.h"
#include "vcontent.h"
#include "vcontentinrectangle.h"
namespace violet {
    namespace abstract {
        AbstractNode::AbstractNode() {
            m_id = new Id;
            m_revision = 0;
            m_location = new VPoint;
            m_content = new VContent;
        }
        AbstractNode::AbstractNode(const AbstractNode& node) {
        }
        AbstractNode::~AbstractNode() {
            delete m_id;
            delete m_location;
            delete m_content;
        }
        /* IIdentifiable interface */
        Id& AbstractNode::GetId() {
            return (*m_id);
        }
        void AbstractNode::SetId(Id& id) {
            m_id->SetValue(id.GetValue());
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
            BeforeReconstruction();

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
            
            INode& p = GetParent();
            if (&p!=nullptr) {
                parents->push_front(&p);
                while(&p.GetParent()!=nullptr){
                    INode& q = p.GetParent();
                    parents->push_front(&q);
                }
            }
            return (*parents);
        }
        void AbstractNode::SetParent(INode& parent) {
            m_parent = &parent;
        }
        void AbstractNode::SetGraph(IGraph& g) {
            m_graph = &g;
        }
        IGraph& AbstractNode::GetGraph() {
            return (*m_graph);
        }
        void AbstractNode::Translate(double dx,double dy) {
            m_location->SetX(m_location->GetX()+dx);
            m_location->SetY(m_location->GetY()+dy);
        }
        bool AbstractNode::Contains(VPoint& point) {
            return true;
        }
        VPoint& AbstractNode::GetConnectionPoint(IEdge&edge) {
            return (*(new VPoint()));
        }
        void AbstractNode::SetLocation(VPoint& point) {
            m_location->SetX(point.GetX());
            m_location->SetY(point.GetY());
            if (m_parent!=nullptr)
                (reinterpret_cast<AbstractNode*>(m_parent))->onChildChangeLocation( (*this) );
        }
        VPoint& AbstractNode::GetLocation() {
            return (*m_location);
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
        /* others */
        void AbstractNode::onChildChangeLocation(INode& child) {
        }
        void AbstractNode::CreateContentStructure() {
            //SetBorder();
            new VContentInRectangle(*this);
            //SetBackground();
            SetContent(GetBackground());
        }
    }
}    