//System.h
#pragma once

#include <SDL.h>

template< typename Derived >
class System
{
public:
    uint32_t componentMask;

    void update()
    {
        static_cast<Derived>(this).update();
    }
};