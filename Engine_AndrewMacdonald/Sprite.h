//Sprite.h
#pragma once

#include <string>

#include <SDL.h>

#include "Component.h"

class Sprite : public Component< Sprite >
{
public:
    Sprite() : texture( "" ), width(0), height(0) {};
    std::string texture;
    int width, height;

    template <typename Writer>
    void serialize( Writer& writer ) {
        writer.String( getComponentName().c_str() );
        writer.StartObject();
            writer.String( "texture" ); writer.String( texture.c_str() );
        writer.EndObject();
    }
};