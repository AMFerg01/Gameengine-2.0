//RenderingSystem.h
#pragma once

#include <iostream>

#include <SDL.h>

#include "System.h"

class RenderingSystem : public System<RenderingSystem>
{
public:
    RenderingSystem( SDL_Window* window );
    ~RenderingSystem(void);

    void update();

private:
    SDL_Renderer* renderer;
};