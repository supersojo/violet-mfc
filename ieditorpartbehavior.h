#ifndef IEDITORPARTBEHAVIOR_H
#define IEDITORPARTBEHAVIOR_H

namespace violet {
	class IEditorPartBehavior {
		class VEvent;
		class GraphTool;
		
		public:
			virtual void OnMousePressed(VEvent& evt) = 0;
			virtual void OnMouseDragged(VEvent& evt) = 0;
			virtual void OnMouseReleased(VEvent& evt) = 0;
			virtual void OnMouseClicked(VEvent& evt) = 0;
			virtual void OnMouseMoved(VEvent& evt) = 0;
			virtual void OnMouseWheelMoved(VEvent& evt) = 0;
			virtual void OnToolSelected(GraphTool& selectedTool) = 0;
			virtual void OnNodeSelected(INode& node) = 0;
			virtual void OnEdgeSelected(IEdge& edge) = 0;
			virtual void BeforeEditingNode(INode& node) = 0;
			virtual void WhileEditingNode(INode& node,VEvent& evt) = 0;
			virtual void AfterEditingNode(INode& node) = 0;
			virtual void BeforeEditingEdge(IEdge& edge) = 0;
			virtual void WhileEditingEdge(IEdge& edge,VEvent& evt) = 0;
			virtual void AfterEditingEdge(IEdge& edge) = 0;
			virtual void BeforeRemovingSelectedElements() = 0;
			virtual void AfterRemovingSelectedElements() = 0;
			virtual void BeforeAddingNodeAtPoint(INode& node,VPoint& location) = 0;
			virtual void AfterAddingNodeAtPoint(INode& node,VPoint& location) = 0;
			virtual void BeforeAddingEdgeAtPoints(INode& node,VPoint& start,VPoint& end) = 0;
			virtual void AfterAddingEdgeAtPoints(INode& node,VPoint& start,VPoint& end) = 0;
			virtual void BeforeChangingTransitionPointsOnEdge(IEdge& edge);
			virtual void AfterChangingTransitionPointsOnEdge(IEdge& edge);
			virtual void BeforeChangingColorOnElement(IColorableNode& element);
			virtual void AfterChangingColorOnElement(IColorableNode& element);
			virtual void OnPaint(VContext& context);

	};

}

#endif
