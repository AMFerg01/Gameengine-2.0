//Engine.h
#pragma once

#include <fstream>
#include <iostream>

#include <SDL.h>

#include "Entity.h"
#include "MovementSystem.h"
#include "RenderingSystem.h"
#include "PhysicsSystem.h"
#include "Scene.h"
#include "Input.h"

class PhysicsSystem;

class Engine
{
private:
    SDL_Window* window;
    bool quit;

    //Systems
    RenderingSystem* renderingSystem;
    MovementSystem* movementSystem;

    Engine(void);                       //Private Constructor
    ~Engine(void);                      //Private Destructor

    //Don't Implement
    Engine( Engine& copy );             //Hide Copy Constructor.
    Engine( Engine&& other);            //Hide Move Constructor
    Engine& operator= (Engine& copy);   //Hide Assignment Operator.

public:
    static Engine& instance(void);      //Return the one Engine instance
	float physicsScale; // Pixels per meter
    void start(void);
    void update(void);
};
