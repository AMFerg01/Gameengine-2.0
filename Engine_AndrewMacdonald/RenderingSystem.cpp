//RenderingSystem.cpp
#include "RenderingSystem.h"

#include "Entity.h"
#include "Position.h"
#include "Sprite.h"

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

    //Set Component Mask
    componentMask = Position::getMask() | Sprite::getMask();
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

    //Loop through all entities
    for( Entity& entity : Entity::getEntityList()  )
    {
        //Check if entity has required components
        if( ( entity.getComponentMask() & componentMask ) == componentMask )
        {
            Position& positon = entity.getComponent<Position>();
            Sprite& sprite = entity.getComponent<Sprite>();
        }
    }
   
    //Update screen
    SDL_RenderPresent( renderer );
}
