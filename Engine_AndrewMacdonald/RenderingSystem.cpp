//RenderingSystem.cpp
#include "RenderingSystem.h"

RenderingSystem::RenderingSystem( SDL_Window* window )
{
    //Create SDL2 Renderer
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if( renderer == nullptr )
    {
        std::cerr << "Unable to Create SDL Renderer:" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        system("pause");
        exit(EXIT_FAILURE);
    }
}

RenderingSystem::~RenderingSystem(void)
{
    SDL_DestroyRenderer( renderer );
}

void RenderingSystem::update()
{
    //Set the "Clear Screen" colour to Magenta (RBGA)
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

    //Clear screen
    SDL_RenderClear( renderer );
   
    //Update screen
    SDL_RenderPresent( renderer );
}
