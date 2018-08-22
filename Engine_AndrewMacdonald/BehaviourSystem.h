//BehaviourSystem.h
#pragma once
#include "System.h"

#include <fstream>
#include <iostream>

#include <luacppinterface.h>

#include "Entity.h"
#include "Input.h"
#include "Position.h"

class BehaviourSystem : System< BehaviourSystem >
{
public:
    BehaviourSystem(void);
    ~BehaviourSystem(void);

    void update();

private:
    Lua lua;
    std::string scriptFile;
    std::string scriptContents;
};

