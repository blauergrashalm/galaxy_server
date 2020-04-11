#include <iostream>
#include "gamestate.hpp"
#include "galaxy.hpp"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

Galaxy g;

void my_handler(int s)
{
    std::cout << "Signal erhalten" << std::endl;
    g.stop();
}

int main(int argc, char **argv)
{
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    std::cout << "Starte Galaxy" << std::endl;
    g.run();
    std::cout << "Programm endet" << std::endl;
    return 0;
}
