#include <cstdlib>

#include <iostream>

#include <unistd.h>

#include <SDL/SDL.h>
#include <GL/gl.h>

#include <lua.hpp>
#include "main.h"
#include "LuaFuncs.h"

#include "Terrain.hpp"
#include "OpenGL.h"

#include "HMapReader.hpp"
#include "World.hpp"

static const char *VERSION="Tut6Terrain V0.1.1\nby Raphael Nestler\n";

static const char *HELP="\
\nusage: Tut6Terrain.exe [Options] \
\n--help                                show this help and exit\
\n--version                             show version information and exit\
\n--fullscreen                          start in fullscreen mode\
\n--nofullscreen                        start in windowed mode\
\n--config $FILENAME                    use specified configuration file instead\
\n                                      of the default one\
\n--terrain $FILENAME                   use specified terrain file instead\
\n                                      of the one specified in configuration file\
\n--resolution, --res $WIDEx$HEIGHT     use specified resolution\n";


using namespace std;

void terminate(int code)
{
    DeinitializeGL();
    SDL_Quit();
    exit(code);
}
    

int main(int argc, char *argv[]){
  SDL_Surface *Screen;
  SDL_Event event;
  Config config;
  // Information about the current video settings.
  const SDL_VideoInfo* info = NULL;

  // process std command Line Options
  for(int i=1; i<argc; i++)
  {
    string arg(argv[i]);
    if(arg.compare("--help")==0)
    {
        cout << VERSION << HELP;
        return 0;
    }
    else if(arg.compare("--version")==0)
    {
        cout << VERSION;
        return 0;
    }
  }

  lua_State *L = lua_open();
  if( L == NULL )
  {
  	cout << "Couldn't create lua_State" << endl;
	terminate(1);
  }
  cout << "Lua state created" << endl;
  luaL_openlibs(L);

  cout << "Read default ConfigFile" <<endl;
  init_lua(L, config.configFilename);
  
  cout << "Reading command Line Options" <<endl;
  for(int i=1; i<argc; i++)
  {
    string arg(argv[i]);

    if(arg.compare("--fullscreen")==0)
    {
        config.fullscreen=true;
    }
    else if(arg.compare("--nofullscreen")==0)
    {
        config.fullscreen=false;
    }
    else if(arg.compare("--config")==0)
    {
        i++;
        if(i>=argc)
        {
            cerr << "no Parameter for --config" << endl;
            return 1;
        }
        ifstream configFile ( argv[i] , ifstream::in );
        // is it possible to open file for reading?
        if(configFile.fail())
        {
            cerr << "failed to open config file " << argv[i] <<endl;
            return 1;
        }
        config.configFilename=argv[i];
        configFile.close();
        
    }
    else if(arg.compare("--terrain")==0)
    {
        i++;
        if(i>argc)
        {
            cerr << "invalid Parameter for --terrain" << endl;
            return 1;
        }
        ifstream terrainFile ( argv[i], ifstream::in );
        // is it possible to open file for reading?
        if(terrainFile.fail())
        {
            cerr << "invalid Parameter for --terrain" << endl;
            return 1;
        }
        config.TerrainFilename=argv[i];
        terrainFile.close();
    }
    else if(arg.find("--res")!=string::npos)
    {
        i++;
        if(i>=argc)
        {
            cerr << "Parameter for --resolution needed"<< endl;
            cerr << "usage "  << "--resolution WIDTHxHEIGHT" <<endl;
            return 1;
        }
        string param(argv[i]);
        int width, height;
        if(sscanf(argv[i], "%ix%i", &width, &height)<2)
        {
            cerr << "invalid Parameter for --resolution " << argv[i] <<endl;
            cerr << "usage " << "--resolution WIDTHxHEIGHT" <<endl;
            return 1;
        }
        config.width=width;
        config.height=height;
    }
    else if(arg.compare("--videoinfo")==0)
    {  
        //cout << "Entering videoinfo" << endl;
        if(SDL_Init(SDL_INIT_VIDEO)<0)
        {
            cerr << "Couldn't initialize SDL: \n" << SDL_GetError() << endl;
            terminate(1);
        }
        cout << "SDL Video Initialized"<< endl;
        SDL_Rect **modes;
        Uint32 flags=0;
        flags |= SDL_OPENGLBLIT | SDL_HWSURFACE | SDL_RESIZABLE;
        if(config.fullscreen)
            flags |= SDL_FULLSCREEN;
        /* Get available fullscreen/hardware modes */
        cout << "Call SDL_ListModes(NULL, " << flags << ")" << endl;
        modes=SDL_ListModes(NULL, flags);
        cout << "checking..." << endl;
        
        /* Check if there are any modes available */
        if(modes == (SDL_Rect **)0){
          cout <<"No modes available!" << endl;
          terminate(-1);
        }
        /* Check if or resolution is restricted */
        if(modes == (SDL_Rect **)-1){
          cout << "All resolutions available." << endl;
        }
        else{
          /* Print valid modes */
          cout << "Available Modes:" << endl;
          int cnt;
          for(cnt=0;modes[cnt];++cnt)
            cout << "  " << modes[cnt]->w << "x" << modes[cnt]->h << endl;
        }
        return 0;

    }
    else
    {
        cerr << "unknown Option \"" << argv[i] << "\" " << HELP;
        return 1; 
    }

  }
  
  cout << "Read specified config file" <<endl;
  if( !init_lua(L, config.configFilename) )
  {
  	cout << "Warning: reading config file " << config.configFilename << " failed" << endl;
  }

  cout << "Applying configuration" <<endl;
  if(lua_LoadConfig(L, &config))
  {
        cout << "Error while initialising Lua" << endl;
        terminate(1);
  }
  
  if(SDL_Init(SDL_INIT_VIDEO)<0)
  {
    cerr << "Couldn't initialize SDL: \n" << SDL_GetError() << endl;
    terminate(1);
  }
  cout << "SDL Video Initialized"<< endl;
  Uint32 flags=0;
  flags |= SDL_OPENGLBLIT | SDL_HWSURFACE | SDL_RESIZABLE;
  if(config.fullscreen)
    flags |= SDL_FULLSCREEN;

  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );						    // In order to use SDL_OPENGLBLIT we have to
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );							// set GL attributes first
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );						// colors and doublebuffering

  cout << "Setting up SDL Video Mode" << endl;
  if (SDL_SetVideoMode(config.width, config.height, 0, flags)==NULL)
  {
    cerr << "Error while setting video Mode to " << config.width;
    cerr << "x" << config.height << endl;
    terminate(1);
  }
  cout << "Set Window Title"  << endl;
  SDL_WM_SetCaption("Tut6Terrain_SDL", NULL);
  
  if(!InitializeGL())
  {
    cerr << "Error while Initialize OpenGL" << endl;
    terminate(1);
  }
  cout << "SDL_ShowCurser(SDL_DISABLE)" << endl;
  SDL_ShowCursor(SDL_DISABLE);

  cout << "Load LoadingScreen" << endl;
  SDL_Surface *SplashScreen=SDL_LoadBMP("Data/LoadingScreen.bmp");
  if(SplashScreen==NULL)
  {
    cout << "Error while Loading Splashscreen" << endl;
    terminate(1);
  }

  cout << "SDL_GetVideoSurface()" << endl;
  Screen=SDL_GetVideoSurface();
  if(Screen==NULL)
  {
    cout << "Error while Getting VideoSurface" << endl;
    terminate(1);
  }
  
  cout << "SDL_BlitSurface()" << endl;
  SDL_BlitSurface(SplashScreen, NULL, Screen, NULL);
  cout << "SDL_UpdateRect()" << endl;
  SDL_UpdateRect(Screen, 0, 0, config.width, config.height); // did crash
  cout << "SDL_GL_SwapBuffers()" << endl;
  SDL_GL_SwapBuffers();
  
  
  cout <<"--- Creating World ---" << endl;
  World *myWorld = new World(L);
  myWorld->Create(config.TerrainFilename);
  cout << "--- World created! ---" << endl;
  cout << "-----------------------------------------------------------------";
  cout << endl;
  SDL_FreeSurface(SplashScreen);
  
  ReshapeGL(config.width, config.height, myWorld->GetDepth());
  srand(SDL_GetTicks());
  Uint32 OldTime=SDL_GetTicks();
  cout << "Entering Main Loop" << endl;
  for(int done = 0; !done;){
    Uint32 Time=SDL_GetTicks();

    Uint8 *keyState;
    keyState=SDL_GetKeyState(NULL);
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            done = 1;
            break;    
        case SDL_VIDEORESIZE:
            ReshapeGL (event.resize.w, event.resize.h, myWorld->GetDepth() );
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            // do we directly react?
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                done = 1;
            }
            else // pass it to Terrain
            {
                myWorld->Update(&(event.key));
            }
            break;
        case SDL_MOUSEMOTION:
            myWorld->Update(&event.motion);
            break;

        };
    }
    

    myWorld->Update(Time-OldTime, keyState);
    OldTime=Time;
    myWorld->Draw();
    SDL_GL_SwapBuffers();
  }
  delete myWorld;
  return(0);
}
