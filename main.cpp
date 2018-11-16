#include <iostream>
#include "id.h"
//#include "iedge.h"
#include "inode.h"

#pragma comment(lib,"ole32.lib")
int main() {
    violet::abstract::Id id;
    violet::abstract::Id id1;
    id.SetValue(id1.GetValue());
    std::cout<<id.GetValue()<<std::endl;
    std::cout<<id1.GetValue()<<std::endl;
    std::cout<<id.Equal(id1)<<std::endl;
    return 0;
}