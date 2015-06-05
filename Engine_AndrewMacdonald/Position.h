//Position.h
#pragma once

#include <SDL.h>
#include "Component.h"

class Position : public Component< Position >
{
public:
    Position() : x( 0.0f ), y( 0.0f ) {};
    float x, y;
};