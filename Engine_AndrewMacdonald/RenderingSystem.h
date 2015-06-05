//RenderingSystem.h
#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include <SDL.h>
#include <SDL_image.h>

#include "System.h"

class RenderingSystem : public System<RenderingSystem>
{
public:
    RenderingSystem( SDL_Window* window );
    ~RenderingSystem(void);

    void update();

private:
    SDL_Renderer* renderer;
    std::unordered_map< std::string, SDL_Texture* > _textureMap;

    SDL_Texture* _loadTexture( std::string texture );
};