//Input.cpp
#include "Input.h"

bool Input::getKeyPress( Keys key )
{
    const Uint8* _keyboardState = SDL_GetKeyboardState( NULL );
    return  ( _keyboardState[ (Uint8)key ] != 0 );
}

bool Input::getMousePress( MouseButtons mouseButton )
{
    //Convert mouseButton to an SDL-compatible button mask
    Uint32 mouseButtonMask = SDL_BUTTON( (Uint32)mouseButton );
    return ( SDL_GetMouseState( NULL, NULL ) & mouseButtonMask ) != 0;
}

int Input::getMouseX()
{
    int x;
    SDL_GetMouseState( &x, NULL );
    return x;
}

int Input::getMouseY()
{
    int y;
    SDL_GetMouseState( NULL, &y );
    return y;
}
