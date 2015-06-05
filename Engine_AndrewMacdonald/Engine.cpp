//Engine.cpp
#include "Engine.h"
#include <iostream>

#include "Position.h"
#include "Sprite.h"

#include "System.h"


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

     //Initialize Systems
     renderingSystem = new RenderingSystem( window );
}

Engine::~Engine(void)
{
    //Destroy Systems
    delete renderingSystem;

    //Destroy the window
    SDL_DestroyWindow( window );

    //Shut Down SDL
    SDL_Quit();
}

void Engine::start(void)
{
    for( int i = 0; i < 4; ++i)
    {
        Entity& e = Entity::create();
        Position& position = e.addComponent<Position>();
        position.x = 150 * i;
        position.y = 75 * i;
        Sprite& sprite = e.addComponent<Sprite>();
        sprite.texture = "Assets/test.png";
    }
    

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

    //Update Systems
    renderingSystem->update();
}