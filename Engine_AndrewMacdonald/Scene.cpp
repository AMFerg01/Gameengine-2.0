//Scene.cpp
#include "Scene.h"

namespace Scene
{
void load( const char* scene )
{
    //Open Scene File
    std::fstream sceneFile( scene );
    if( !sceneFile )
    {
        std::cerr << "ERROR: Could not open \"" << scene << "\"" << std::endl;
        system("pause");
        exit( EXIT_FAILURE );
    }

    //Copy scene FileStream into StringStream
    std::stringstream ss;
    ss << sceneFile.rdbuf();
        
    //Close scene file
    sceneFile.close();

    //Parse scene StringStream into JSON Document
    rapidjson::Document document;
    if( document.Parse( ss.str().c_str() ).HasParseError() )
    {            
        std::cerr << scene << " parsing ERROR: " << rapidjson::GetParseError_En( document.GetParseError() ) << std::endl;
        system("pause");
        exit( EXIT_FAILURE );
    }

    //Check that Entities arrays exits
    if( !( document.HasMember("Entities") && document["Entities"].IsArray() ) )
    {
        std::cerr << "JSON Parsing ERROR: " << scene << " does not appear to have an Entities array." << std::endl;
        system("pause");
        exit( EXIT_FAILURE );
    }

    //Create Entities
    for( auto entitiesIter = document["Entities"].Begin(); entitiesIter != document["Entities"].End(); ++entitiesIter )
    {
        Entity& newEntity = Entity::create();

        //Attach Components
        for( auto componentsIter = entitiesIter->MemberBegin(); componentsIter != entitiesIter->MemberEnd(); ++componentsIter )
        {
            std::string componentTypeName = componentsIter->name.GetString();
            if( componentTypeName == "Position" )
            {
                Position& position = newEntity.addComponent<Position>();
                if( componentsIter->value.HasMember("x") && componentsIter->value["x"].IsNumber() )
                {
                    position.x = (float)componentsIter->value["x"].GetDouble();
                }

                if( componentsIter->value.HasMember("y") && componentsIter->value["y"].IsNumber() )
                {
                    position.y = (float)componentsIter->value["y"].GetDouble();
                }

            }
            else if( componentTypeName == "Sprite" )
            {
                Sprite& sprite = newEntity.addComponent<Sprite>();
                if( componentsIter->value.HasMember("texture") && componentsIter->value["texture"].IsString() )
                {
                    sprite.texture = componentsIter->value["texture"].GetString();
                }
            }
        }
    }        
}
}