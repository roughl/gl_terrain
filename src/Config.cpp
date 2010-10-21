// Config.cpp
#include "Config.hpp"

Option::Option():
    set(false),
    type(NUMBER)
{
    this->value.number=0.0;
}

double Option::getNumber()
{
    if(set && type==NUMBER)
        return value.number;
    return 0.0;
}
double Option::getNumber(bool *ok)
{
    if(set && type==NUMBER)
    {
        *ok=true;
        return value.number;
    }
    else
    {
        *ok=false;
        return 0.0;
    }
}

bool Option::getBoolean()
{
    if(set && type==BOOLEAN)
        return value.boolean;
    return false;
}
bool Option::getBoolean(bool *ok)
{
    if(set && type==BOOLEAN)
    {
        *ok=true;
        return value.boolean;
    }
    else
    {
        *ok=false;
        return false;
    }
}

const char *Option::getString()
{
    if(set && type==STRING)
        return value.string;
    return NULL;
}
const char *Option::getString(bool *ok)
{
    if(set && type==STRING)
    {
        *ok=true;
        return value.string;
    }
    else
    {
        *ok=false;
        return NULL;
    }
}
