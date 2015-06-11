//Input.h
#pragma once

#include <SDL.h>

#include "Keys.h"
#include "Mouse.h"

namespace Input
{
    bool getKeyPress( Keys key );
    bool getMousePress( MouseButtons mouseButton );
    int getMouseX();
    int getMouseY();
}
