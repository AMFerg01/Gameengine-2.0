//main.cpp
#include <iostream>
#include <SDL.h>
#include "Engine.h"

int main( int argc, char *args[] )
{    
    Engine::instance().start();
    return EXIT_SUCCESS;
}
