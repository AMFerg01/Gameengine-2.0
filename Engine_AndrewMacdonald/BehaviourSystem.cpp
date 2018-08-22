//BehaviourSystem.cpp
#include "BehaviourSystem.h"

BehaviourSystem::BehaviourSystem(void)
{
    //Load Lua script
    scriptFile = "Assets/Scripts/myScript.lua";
    std::ifstream file( scriptFile );
    if( !file )
    {
        std::cerr << "ERROR: Could not open \"" << scriptFile << "\"" << std::endl;
        system("pause");
        exit( EXIT_FAILURE );
    }
    scriptContents = std::string( ( std::istreambuf_iterator< char >( file ) ), std::istreambuf_iterator< char >() );
  
    lua.LoadStandardLibraries();

    //Run the script to check for errors
    std::string luaErrors = lua.RunScript( scriptContents );
    if( luaErrors != "No errors" )
    {
        std::cerr << luaErrors << std::endl;
    }    
    
    componentMask = Position::getMask();    
}

BehaviourSystem::~BehaviourSystem(void)
{
}

void BehaviourSystem::update()
{
    //Loop through all entities
    for( Entity& entity : Entity::getEntityList()  )
    {
        //Check if entity has required components
        if( ( entity.getComponentMask() & componentMask ) == componentMask )
        {
            Position& position = entity.getComponent< Position >();

            LuaTable global = lua.GetGlobalEnvironment();

            //Get access to the "update" function in the Lua script
            auto scriptUpdate = global.Get< LuaFunction< void( void ) > >( "update" );

            //Create a Lua Table from the Position Component
            LuaTable positionTable = lua.CreateTable();
            positionTable.Set( "x", position.x );
            positionTable.Set( "y", position.y );
            
            //Put the Position Lua Table in the script's global scope
            global.Set( "position", positionTable );

            //Run the script's "update" function 
            scriptUpdate.Invoke();
            
            //Get the updated Position Table from the global scope
            LuaTable newPositionTable = global.Get< LuaTable >( "position" );

            //Update the in-engine Position Component
            position.x = newPositionTable.Get< float >("x");
            position.y = newPositionTable.Get< float >("y");
        }
    }

    //lua.CollectGarbage();
}