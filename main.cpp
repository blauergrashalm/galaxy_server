#include <iostream>
#include "gamestate.h"


int main(int argc, char **argv) {
    std::cout << "Humba" << std::endl;
    GameState state(10,10);
    std::cout << state.toJson().dump(4) << std::endl;
    
//     std::shared_ptr<Field> f;
//     f.reset(new Field(0,0));
    return 0;
}
