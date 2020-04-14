#include <iostream>
#include "gamestate.hpp"
#include "galaxy.hpp"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "debug_functions.hpp"

Galaxy *g;

void my_handler(int s)
{
    DBG_LOG(LOW, "Signal erhalten");
    g->stop();
}

int main(int argc, char **argv)
{
    g = new Galaxy();
    std::signal(SIGINT, my_handler);
    DBG_LOG(MEDIUM, "Starte Galaxie");
    g->run();
    DBG_LOG(LOW, "Programm endet");
    delete g;
    return 0;
}
