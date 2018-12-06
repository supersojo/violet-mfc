#include <iostream>
#include "abstract/id.h"
#include "node/notenode.h"
#pragma comment(lib,"ole32.lib")

int main() {
    violet::VContext context;
    violet::NoteNode node;
    node.Draw(context);
    return 0;
}