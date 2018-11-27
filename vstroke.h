#ifndef VSTROKE_H
#define VSTROKE_H
#include <string>
namespace violet {

    class VStroke {
        public:
            VStroke(){}
            VStroke(std::string name):m_name(name){}
            VStroke(const VStroke& stroke){
                m_name = stroke.m_name;
            }
            VStroke& operator=(const VStroke& stroke) {
                m_name = stroke.m_name;
                return *this;
            }
            void SetName(std::string name) {
                m_name = name;
            }
            bool operator==(const VStroke& stroke) {
                return GetName().compare(stroke.m_name)==0;
            }
            std::string GetName() {
                return m_name;
            }
        private:
            std::string m_name;
    };
}

#endif

