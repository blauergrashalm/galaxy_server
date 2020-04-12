#include <iostream>
#include "gamestate.hpp"
#include "galaxy.hpp"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "debug_functions.hpp"

Galaxy g;

void my_handler(int s)
{
    DBG_LOG(LOW, "Signal erhalten");
    g.stop();
}

int main(int argc, char **argv)
{
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    DBG_LOG(MEDIUM, "Starte Galaxie");
    g.run();
    DBG_LOG(LOW, "Programm endet");
    return 0;
}
