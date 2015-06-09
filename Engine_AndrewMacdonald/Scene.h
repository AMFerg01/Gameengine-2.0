//Scene.h
#pragma once

#include <fstream>
#include <sstream>
#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#include "Entity.h"
#include "Position.h"
#include "Sprite.h"

namespace Scene {
    void load( const char* scene );
}
