#ifndef CHOICELIST_H
#define CHOICELIST_H
#include <vector>
#include <utility> // for std::pair
/*
 this class will free all memory about key and value
 key and value 's memory must be allocated outsize
 and free in the class.
*/
namespace violet {
    namespace property {
        template<class KeyType,class ValueType>
        class ChoiceList {
            public:
                ChoiceList(std::vector<KeyType*>& keys,std::vector<ValueType*>& values) {
                    if ((keys.size()!=values.size()) ||
                        (keys.size()==0))
                        return;
                    //
                    std::vector<KeyType*>::iterator i_key;
                    std::vector<ValueType*>::iterator i_val;
                    ElementType* e=nullptr;
                    for (i_key=keys.begin(),i_val=values.begin();i_key!=keys.end();i_key++,i_val++) {
                        e = new ElementType;
                        e->first = (*i_key);
                        e->second = (*i_val);
                        m_choices.push_back(e);
                    }
                    
                    m_selectedPos = 0;
                }
                
                std::vector<KeyType*> GetKeys() {
                    std::vector<KeyType*> keys;
                    for (int i=0;i<m_choices.size();i++) {
                        keys.push_back(m_choices[i]->first);
                    }
                    return keys;
                }
                std::vector<ValueType*> GetValues() {
                    std::vector<ValueType*> values;
                    for (int i=0;i<m_choices.size();i++) {
                        values.push_back(m_choices[i]->second);
                    }
                    return values;
                }
                bool SetSelectedIndex(int index) {
                    if (index<0 || index>=m_choices.size())
                        return false;
                    m_selectedPos = index;
                    return true;
                }
                bool SetSelectedValue(ValueType& value) {
                    for (int i=0;i<m_choices.size();i++) {
                        /*
                        how to compare two value?
                        Equals ?? or address compare
                        */
                        if (&value == (m_choices[i].second)) {
                            m_selectedPos = index;
                            return true;
                        }
                    }
                    return false;
                }
                ValueType& GetSelectedValue() {
                    return *(m_choices[m_selectedPos]->second);
                }
                int GetSelectedPos() {
                    return m_selectedPos;
                }
                virtual ~ChoiceList() {
                    std::vector<ElementType*>::iterator i;
                    for (i=m_choices.begin();i!=m_choices.end();i++) {
                        delete (*i)->first;//KeyType*
                        delete (*i)->second;//ValueType8
                        delete (*i);// ElementType*
                        m_choices.erase(i);
                    }
                }
            private:
                ChoiceList(){}/* disallow default construct */
                typedef std::pair<KeyType*,ValueType*> ElementType;
                std::vector<ElementType*> m_choices;
                int m_selectedPos;
        };
        // ptr specialize
    }// property
}//violet

#endif
