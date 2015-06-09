//Component.h
#pragma once

#include <string>
#include <typeinfo>
#include <unordered_map>

#include <SDL.h>

class BaseComponent
{
protected:
    static uint32_t _componentTypeCount;
};

template< typename Derived >
class Component : public BaseComponent
{
    friend class Entity;
public:
    template <typename Writer>
    void serialize( Writer& writer )
    {
        static_cast<Derived>(this).serialize();
    }

    static uint32_t getMask()
    {
        static uint32_t _mask = 1 << _componentTypeCount++;
        return _mask;
    }

    static std::string& getComponentName()
    {
        //Get Type Name
        static std::string _name = typeid(Derived).name();
        
        //Strip away possible prefixes
        if( _name.find( "class ") != std::string::npos ) //Don't forget the space!
        {
            _name = _name.substr(6);          
        }
        return _name;
    }

private:
    static std::unordered_map< uint32_t, Derived > componentMap;

    static Derived& addComponentWithEntityID( uint32_t entityID )
    {
        Derived newComponent;
        componentMap[ entityID ] = newComponent;
        return componentMap[ entityID ];
    }

    static Derived& getComponentWithEntityID( uint32_t entityID )
    {
        return componentMap[ entityID ];
    } 
};

//Template Statics
template< typename Derived >
std::unordered_map< uint32_t, Derived > Component<Derived>::componentMap;