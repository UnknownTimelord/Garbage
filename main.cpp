#include <iostream>
#include "Garbage.h"

int main() {
    Deck mainD;
    Field mainF(mainD);

    mainF.printField();

    return 0;
}
