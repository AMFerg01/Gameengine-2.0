//Engine.h
#pragma once

#include <SDL.h>

class Engine
{
private:
    SDL_Window* window;
    bool quit;

    Engine(void);                       //Private Constructor
    ~Engine(void);                      //Private Destructor

    //Don't Implement
    Engine( Engine& copy );             //Hide Copy Constructor.
    Engine( Engine&& other);            //Hide Move Constructor
    Engine& operator= (Engine& copy);   //Hide Assignment Operator.

public:
    static Engine& instance(void);      //Return the one Engine instance

    void start(void);
    void update(void);
};
