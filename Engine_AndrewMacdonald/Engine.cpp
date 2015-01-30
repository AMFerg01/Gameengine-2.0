//Engine.cpp
#include "Engine.h"
#include <iostream>

Engine& Engine::instance(void)
{
    static Engine instance; // Guaranteed to be destroyed.
                            // Lazilly Instantiated on first use.
    return instance;
}

Engine::Engine(void)
    : quit(false)
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) != NULL )
    {
        std::cerr << "Unable to Initialize SDL:" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        system("pause");
        exit(EXIT_FAILURE);
    }

    //Create a window
    window = SDL_CreateWindow(
        "Engine",				//Window title
        SDL_WINDOWPOS_CENTERED,	//Center window horizontally
        SDL_WINDOWPOS_CENTERED,	//Center window vertically
        800,					//Width
        600,					//Height
        NULL					//Optional flags
    );
    if( window == nullptr )
    {
        std::cerr << "Unable to Create Window:" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        system("pause");
        exit(EXIT_FAILURE);
    }
}

Engine::~Engine(void)
{
     //Destroy the window
    SDL_DestroyWindow( window );

    //Shut Down SDL
    SDL_Quit();
}

void Engine::start(void)
{
    while( !quit )
    {
        update();
    }
}

void Engine::update()
{
    //Check for SDL Events (Mouse, Keyboard, Gamepad, OS Messages, etc)
    SDL_Event e;
    while( SDL_PollEvent( &e ) != NULL )
    {
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }
    }
}