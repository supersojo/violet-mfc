#ifndef VCONTEXT_H
#define VCONTEXT_H
#include "config.h"
#include "vpoint.h"
#include "vstroke.h"
#include "vcolor.h"
namespace violet {
    class VShape;
    class VColor;
    class VPoint;
    class VRect;
    /*
    context for draw something
    */
    class VContext {
        public:
            VContext();
            virtual void Draw(VShape& shape);
            virtual void Fill(VShape& shape);
            VPoint& GetLocation() {
                return m_location;
            }
            void SetLocation(VPoint& point) {
                m_location = point;
            }
            VColor& GetColor() {
                return m_color;
            }
            void SetColor(VColor& color) {
                m_color = color;
            }
            VStroke& GetStroke() {
                return m_stroke;
            }
            void SetStroke(VStroke& stroke) {
                m_stroke = stroke;
            }
            void SetLineWidth(int lineWidth) {
                m_lineWidth = lineWidth;
            }
            int GetLineWidth() {
                return m_lineWidth;
            }
            void Translate(double dx,double dy) {
                SetLocation(m_location+VPoint(dx,dy));
                //m_graphics->TranslateTransform(dx,dy);
            }
            void Rotate(VPoint& point,double angle);
            void Attach(Gdiplus::Graphics& graphics) {
                m_graphics = &graphics;
            }
            void DrawLine(VPoint& start,VPoint& end);
            void DrawString(std::string& str);
            void DrawString(std::string& str,VRect& layoutRect);
            VRect MeasureString(std::string& str);
            VRect MeasureString(std::string& str,VRect& layoutRect);
            void FillRectangle(VPoint& location,VPoint& size,VColor& color);
            void FillPolygon(VPoint& location,VPoint* points,int count);
            ~VContext();
        private:
            ULONG_PTR gdiplusToken;
            VPoint m_location;
            VColor m_color;
            VStroke m_stroke;
            Gdiplus::Graphics* m_graphics;
            int m_lineWidth;// for DrawString & MeasureString
    };

}

#endif


