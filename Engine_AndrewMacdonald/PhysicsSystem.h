//PhysicsSystem.h
#pragma once
#include "System.h"

#include <chrono>
#include <iostream>
#include <unordered_map>

#include <Box2D/Box2D.h>

#include "CircleCollider.h"
#include "Engine.h"
#include "Entity.h"
#include "Events.h"
#include "Position.h"
#include "RectangleCollider.h"
#include "RigidBody.h"

using namespace std::chrono;

class PhysicsSystem : public System< PhysicsSystem >
{
public:
    float timeStep;
    int velocityIterations;
    int positionIterations;

    PhysicsSystem(void);
    ~PhysicsSystem(void);

    void update(); 
private:
    b2Vec2 _gravity;
    b2World* _world;

    time_point< system_clock > _lastWorldStepTime;

    std::unordered_map< size_t, b2Body* > _bodies;

   b2Body* createBody( size_t entityID, Position& position, float physicsScale );
};