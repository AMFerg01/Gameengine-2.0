//RenderingSystem.cpp
#include "RenderingSystem.h"

#include "Entity.h"
#include "Position.h"
#include "Sprite.h"

RenderingSystem::RenderingSystem( SDL_Window* window )
{
    //Create SDL2 Renderer
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if( renderer == nullptr )
    {
        std::cerr << "Unable to Create SDL Renderer:" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        system( "pause" );
        exit( EXIT_FAILURE );
    }

    //Initialize SDL2_Image
    int IMG_flags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( ( IMG_Init( IMG_flags ) & IMG_flags ) != IMG_flags )
    {
        std::cerr << "Unable to Initialize SDL_Image:" << std::endl;
        std::cerr << IMG_GetError() << std::endl;
        system( "pause" );
        exit( EXIT_FAILURE );
    }

    //Set Component Mask
    componentMask = Position::getMask() | Sprite::getMask();
}

RenderingSystem::~RenderingSystem(void)
{
    //Destroy loaded textures
    for( auto iterator = _textureMap.begin(); iterator != _textureMap.end(); iterator++ )
    {
        SDL_DestroyTexture( iterator->second );
    }

    //Destroy renderer
    SDL_DestroyRenderer( renderer );

    //Destory SDL2_image
    IMG_Quit();
}

void RenderingSystem::update()
{
    //Set the "Clear Screen" colour to Magenta (RBGA)
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

    //Clear screen
    SDL_RenderClear( renderer );

    //Loop through all entities
    for( Entity& entity : Entity::getEntityList()  )
    {
        //Check if entity has required components
        if( ( entity.getComponentMask() & componentMask ) == componentMask )
        {
            //Get components
            Position& position = entity.getComponent<Position>();
            Sprite& sprite = entity.getComponent<Sprite>();

            //Check to see if sprite's texture is loaded
            if( _textureMap.count( sprite.texture ) < 1 )
            {
                _textureMap[ sprite.texture ] = _loadTexture( sprite.texture );
            }

            //Set sprite's height and width
            SDL_QueryTexture( _textureMap[ sprite.texture ], NULL, NULL, &sprite.width, &sprite.height );
			int rendererHeight;
			SDL_GetRendererOutputSize(renderer, nullptr, &rendererHeight);
            //Create Drawing Rectangles
            SDL_Rect sourceRect = { 0, 0, sprite.width, sprite.height };
			SDL_Rect destRect = { (int)position.x, rendererHeight - (int)position.y, sprite.width, sprite.height };

            //Copy Sprite texture to screen
            SDL_RenderCopy( renderer, _textureMap[sprite.texture], &sourceRect, &destRect );
        }
    }
   
    //Update screen
    SDL_RenderPresent( renderer );
}

SDL_Texture* RenderingSystem::_loadTexture( std::string texture )
{
    //Load image at specified path
    SDL_Surface* surface = IMG_Load( texture.c_str() );
    if( surface == nullptr )
    {
        std::cerr << "Unable to load image " << texture << std::endl;
        std::cerr << IMG_GetError() << std::endl;
        system( "pause" );
        exit( EXIT_FAILURE );
    }

    //Create texture from surface pixels
    SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface( renderer, surface );
    if( spriteTexture == nullptr )
    {
        std::cerr << "Unable to create texture from surface:" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        system( "pause" );
        exit( EXIT_FAILURE );
    }

    //Get rid of temporary SDL2_Surface
    SDL_FreeSurface( surface );

    return spriteTexture;
}