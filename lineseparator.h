#ifndef LINESEPARATOR_H
#define LINESEPARATOR_H
#include "separator.h"

namespace violet {
	class LineSeparator : public Separator {
		public:
			LineSeparator() {
				m_color = VColor(0,0,0);//black
			}
			LineSeparator(VColor&color) {
				m_color = color;
			}
			void SetColor(VColor& color) {
				m_color = color;
			}
			virtual void Draw(VContext& context, VPoint& start,VPoint& end) {// logical position
				VColor oldColor = context.GetColor();
				context.SetColor(m_color);
				VPoint location = context.GetLocation();
				context.DrawLine(start+location,end+location);
				context.SetColor(oldColor);
			}
		private:
			VColor m_color;
	};
}


#endif
