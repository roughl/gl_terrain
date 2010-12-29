// 2DFuncs.hpp
#ifndef 2DFUNCS_HPP
#define 2DFUNCS_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Object.hpp"


class 2DObject: IObject
{
public:
    Object();
    Object(World *world);
    virtual void Draw(); // Do Render
    virtual void Update(Uint32 milliseconds, Uint8 *keystate){} // per default do not any update
    
protected:
    
private:    
}

class Text
{
    
}

#endif // 2DFUNCS_HPP

