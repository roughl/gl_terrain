// main.h

#ifndef __MAIN_H
#define __MAIN_H




class Config {
public:
    Config():width(800),height(600),fullscreen(1),fps(30),
        configFilename("Lua/config.lua"),
        TerrainFilename("Lua/terrainconfig.lua")
        {}
   // ~Config();
    int width, height;
    bool fullscreen;
    int fps;
    const char *configFilename;
    const char *TerrainFilename;
private:    
};

typedef struct CONFIG {
    int width, height;
    bool fullscreen;
    int fps;
    const char *configFilename;
    const char *TerrainFilename;
}CONFIG;

#endif // __MAIN_H
