//Position.h
#pragma once

#include <SDL.h>

#include "Component.h"

class Position : public Component< Position >
{
public:
    Position() : x( 0.0f ), y( 0.0f ) {};
    float x, y;

    template <typename Writer>
    void serialize( Writer& writer ) {
        writer.String( getComponentName().c_str() );
        writer.StartObject();
            writer.String("x"); writer.Double( x );
            writer.String("y"); writer.Double( y );
        writer.EndObject();
    }
};