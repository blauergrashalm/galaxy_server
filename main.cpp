#include <iostream>
#include "player.h"

int main(int argc, char **argv) {
    Player p("Humba", "Täterä");
    std::cout << p.name << std::endl;
    return 0;
}
