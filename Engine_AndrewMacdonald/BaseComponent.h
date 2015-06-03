#pragma once

#include <SDL.h>

class BaseComponent
{
public:
    BaseComponent(void);
    ~BaseComponent(void);

private:
    uint32_t entityID;
};

