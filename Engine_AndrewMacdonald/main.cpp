//main.cpp
#include <iostream>
#include <SDL.h>
#include "Engine.h"

//Example.h
class Example
{
public:
    static int staticNum;
    int num;

    Example( int num );
};

Example::Example( int num )
    : num( num )
{
}

int Example::staticNum = 0;
    
int main( int argc, char *args[] )
{

    Example a(1);
    Example b(2);
    
    std::cout << a.staticNum << std::endl;          //0
    std::cout << b.staticNum << std::endl;          //0

    a.staticNum = 10;

    std::cout << a.staticNum << std::endl;          //10
    std::cout << b.staticNum << std::endl;          //10

    b.staticNum = 15;

    std::cout << a.staticNum << std::endl;          //15
    std::cout << b.staticNum << std::endl;          //15

    std::cout << Example::staticNum << std::endl;   //15

    std::cout << a.num << std::endl;                //1
    std::cout << b.num << std::endl;                //2
    
    Engine::instance().start();
    return EXIT_SUCCESS;
}
