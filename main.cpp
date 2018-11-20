#include <iostream>
#include "id.h"
#include "notenode.h"
#pragma comment(lib,"ole32.lib")

int main() {
    violet::VContext context;
    violet::NoteNode node;
    node.Draw(context);
    return 0;
}