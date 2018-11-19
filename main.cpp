#include <iostream>
#include "id.h"
#include "abstractnode.h"
#include "vcontentinshape.h"
#pragma comment(lib,"ole32.lib")

class Foo{
    public:
        Foo() {
            i = 1;
        }
        int i;
        void foo() {
            std::cout<<"foo()"<<std::endl;
        }
};
class Bar {
    public:
    Bar() {
        m_foo = new Foo();
    }
    Foo& get() {
        return (*m_foo);
    }
    private:
    Foo* m_foo;
    
};

int main() {
    
    Bar bar;
    return 0;
}