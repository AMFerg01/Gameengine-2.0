//MovementSystem.cpp
#include "MovementSystem.h"

MovementSystem::MovementSystem()
{
    //Set Component Mask
    componentMask = Position::getMask() | Sprite::getMask();
}

MovementSystem::~MovementSystem()
{
}


void MovementSystem::update()
{
    //Loop through all entities
    for( Entity& entity : Entity::getEntityList()  )
    {
        //Check if entity has required components
        if( ( entity.getComponentMask() & componentMask ) == componentMask )
        {
            Position& position = entity.getComponent<Position>();
            
            if( Input::getKeyPress( Keys::LEFT ) )
            {
                position.x -= 0.1f;
            }
            
            if( Input::getKeyPress( Keys::RIGHT ) )
            {
                position.x += 0.1f;
            }
            
            if( Input::getKeyPress( Keys::UP ) )
            {
                position.y -= 0.1f;
            }

            if( Input::getKeyPress( Keys::DOWN ) )
            {
                position.y += 0.1f;
            }
        }
    }
}
