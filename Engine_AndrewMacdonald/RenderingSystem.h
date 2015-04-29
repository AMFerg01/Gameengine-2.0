//RenderingSystem.h
#pragma once

#include <iostream>

#include <SDL.h>

#include "ISystem.h"

class RenderingSystem : ISystem
{
public:
    RenderingSystem( SDL_Window* window );
    ~RenderingSystem(void);

    void update();

private:
    SDL_Renderer* renderer;
};

