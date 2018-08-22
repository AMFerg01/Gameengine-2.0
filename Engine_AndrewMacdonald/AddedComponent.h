//AddedComponent.h
#pragma once

//Forward Declarations
class Entity;

namespace Event
{
    template< typename C >
    class AddedComponent
    {
    public:
        AddedComponent( Entity& entity, C& component ) : entity(entity), component( component )
        {
        };

        Entity& entity;
        C& component;
    }; 
}