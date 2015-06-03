//Entity.h
#pragma once

//Standard Libraries
#include <cassert>
#include <type_traits>
#include <vector>

//Project Libraries
#include <SDL.h>

//Headers
#include "Component.h"

class Entity
{
public:
    //Instance Methods
    template< typename C >
    C& addComponent()
    {
        static_assert(
            std::is_base_of< Component<C>, C >::value,
            "ERROR: Can only add Component Types to Entities!"
           );
        _componentMask = _componentMask | C::getMask();
        return getComponent<C>();
    }

    template< typename C>
    C& getComponent()
    {
        static_assert( std::is_base_of< Component<C>, C >::value, "ERROR: Can only get Component Types from Entities!");
        return C::getComponentWithEntityID( _ID );
    }

    uint32_t getComponentMask();
    size_t getID();

    //Static Methods
    static std::vector<Entity>& getEntityList();
    static Entity& create();
    static void destroy( Entity& e );

private:
    Entity();
    Entity( size_t ID );

    size_t _ID;
    uint32_t _componentMask;

    static std::vector<Entity> _entityList;
};
