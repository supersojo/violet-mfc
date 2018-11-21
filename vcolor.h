#ifndef VCOLOR_H
#define VCOLOR_H
#include <iostream>
namespace violet {
    class VColor {
        public:
            VColor() {
                m_red = 0;
                m_green = 0;
                m_blue = 0;
            }
            VColor(int r,int g,int b) {
                m_red = r;
                m_green = g;
                m_blue = b;
            }
            VColor(const VColor& color) : m_red(color.GetR()), 
                                          m_green(color.GetG()), 
                                          m_blue(color.GetB())
            {
            }
            int GetR() const{
                return m_red;
            }
            int GetG() const{
                return m_green;
            }
            int GetB() const{
                return m_blue;
            }
            
            VColor& operator=(const VColor& color) {
                m_red = color.GetR();
                m_green = color.GetG();
                m_blue = color.GetB();
                return *this;
            }
            friend std::ostream& operator<<(std::ostream& out,const VColor& color) {
                out<<"("<<color.m_red<<",";
                out<<color.m_green<<",";
                out<<color.m_blue<<")";
                return out;
            }
            
            static VColor RED;
            static VColor GREEN;
            static VColor BLUE;
        private:
            int m_red;
            int m_green;
            int m_blue;
    };
}

#endif
