#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include <SDL/SDL.h>
#include <GL/gl.h>

#include <lua.hpp>
#include <tclap/CmdLine.h>

#include "config.h"
#include "main.h"
#include "LuaFuncs.h"

#include "Terrain.hpp"
#include "OpenGL.h"

#include "HMapReader.hpp"
#include "World.hpp"

using namespace std;

void terminate(int code)
{
	DeinitializeGL();
	SDL_Quit();
	exit(code);
}

Uint32 initSDL(Config conf)
{
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{
		cerr << "Couldn't initialize SDL: \n" << SDL_GetError() << endl;
		terminate(1);
	}
	cout << "SDL Video Initialized"<< endl;
	Uint32 flags = SDL_OPENGL | SDL_HWSURFACE;
	if(conf.fullscreen)
		flags |= SDL_FULLSCREEN;
	else
		flags |= SDL_RESIZABLE;
	return flags;
}

int main(int argc, char *argv[])
{
	SDL_Event event;
	Config config;

	TCLAP::CmdLine cmd("OpenGL demo with terrain from bitmap files", ' ', VERSION );
	TCLAP::SwitchArg fullscreenArg("f", "fullscreen", "Start in fullscreen mode", false );
	TCLAP::SwitchArg noFullscreenArg("n", "nofullscreen", "Do not start in fullscreen mode", false );
	TCLAP::ValueArg<string> configArg("c", "config", "Use specified configuration file instead of the default one", false, config.configFilename, "FILE");
	TCLAP::ValueArg<string> terrainArg("t", "terrain", "Use specified terrain file instead of the one specified in configuration file", false, "", "FILE");
	TCLAP::ValueArg<string> resolutionArg("r", "resolution", "Use specified resolution", false, "", "WIDTHxHEIGHT");
	TCLAP::SwitchArg videoinfoArg("v", "videoinfo", "Get videoinfo from hardware", false);
	cmd.add(fullscreenArg);
	cmd.add(configArg);
	cmd.add(terrainArg);
	cmd.add(resolutionArg);
	cmd.add(videoinfoArg);
	try
	{
		cmd.parse(argc, argv);
	}
	catch (TCLAP::ArgException & e)
	{
		cerr << "Invalid option: " << e.argId() << "." << endl << e.error() << endl;
		return 1;
	}
	
	// validate if config files are readable
	ifstream configFile ( configArg.getValue().c_str(), ifstream::in );
	if(configFile.fail())
	{
		cerr << "failed to open config file " << configArg.getValue() <<endl;
		return 1;
	}
	configFile.close();

	if( terrainArg.getValue() != "" ) {
		ifstream terrainFile ( terrainArg.getValue().c_str(), ifstream::in );
		if(terrainFile.fail())
		{
			cerr << "failed to open terrain file " << terrainArg.getValue() << endl;
			return 1;
		}
		terrainFile.close();
	}

	// read default config
	lua_State *L = luaL_newstate();
	if( L == NULL )
	{
		cout << "Couldn't create lua_State" << endl;
		terminate(1);
	}
	cout << "Lua state created" << endl;
	luaL_openlibs(L);

	cout << "Read default ConfigFile" <<endl;
	init_lua(L, config.configFilename);
	cout << "Applying configuration" <<endl;
	if(lua_LoadConfig(L, &config))
	{
		cout << "Error while initialising Lua" << endl;
		terminate(1);
	}
	
	config.configFilename=configArg.getValue().c_str();
	// apply specified config file
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
	if(terrainArg.getValue() != "" ) {
		config.TerrainFilename=terrainArg.getValue().c_str();
	}

	// apply flags
	cout << "Applying command Line Options" <<endl;
	if(fullscreenArg.getValue()) {
		config.fullscreen = true;
	}
	if(noFullscreenArg.getValue()) {
		config.fullscreen = false;
	}

	if(videoinfoArg.getValue()) {
		Uint32 flags = initSDL(config);
		/* Get available fullscreen/hardware modes */
		cout << "Call SDL_ListModes(NULL, " << flags << ")" << endl;
		SDL_Rect **modes=SDL_ListModes(NULL, flags);
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

	if(resolutionArg.getValue() != "") {
		int width, height;
		if(sscanf(resolutionArg.getValue().c_str(), "%ix%i", &width, &height)<2)
		{
			cerr << "invalid Parameter for --resolution " << resolutionArg.getValue()<<endl;
			cerr << "usage " << "--resolution WIDTHxHEIGHT" <<endl;
			return 1;
		}
		config.width=width;
		config.height=height;
	}

	Uint32 flags = initSDL(config);

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );     // In order to use SDL_OPENGLBLIT we have to
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );   // set GL attributes first
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // colors and doublebuffering

	cout << "Setting up SDL Video Mode" << endl;
	if (SDL_SetVideoMode(config.width, config.height, 0, flags)==NULL)
	{
		cerr << "Error while setting video Mode to " << config.width;
		cerr << "x" << config.height << endl;
		terminate(1);
	}
	cout << "Set Window Title"  << endl;
	SDL_WM_SetCaption("gl_terrain", NULL);

	if(!InitializeGL())
	{
		cerr << "Error while Initialize OpenGL" << endl;
		terminate(1);
	}
	cout << "SDL_ShowCurser(SDL_DISABLE)" << endl;
	SDL_ShowCursor(SDL_DISABLE);

	cout << "Load LoadingScreen" << endl;
	unsigned texture;
	texture = LoadTexture("Data/LoadingScreen.bmp");
	if(!texture) {
		cout << "Error while Loading Splashscreen" << endl;
		terminate(1);
	}
	GLfloat vertices[4][2] = {
		{-1.0, -1.0}, // Bottom Left
		{+1.0, -1.0}, // Bottom Right
		{+1.0, +1.0}, // Top Right
		{-1.0, +1.0}, // Top Left
	};
	GLint texcoords[4][2] = {
		{0,1}, // Top Left
		{1,1}, // Top Right
		{1,0}, // Bottom Right
		{0,0}, // Bottom Left
	};
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glTranslatef (0,0,-1);	// Translate to Cam Pos
	glEnable(GL_TEXTURE_2D);// Texture Mapping aktivieren
	glBindTexture(GL_TEXTURE_2D, texture);    

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glVertexPointer( 2, GL_FLOAT, 0, vertices );
	glTexCoordPointer( 2, GL_INT, 0, texcoords );
	glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	
	glDisable(GL_TEXTURE_2D);
	
	GLenum error = glGetError();
	if(error != GL_NO_ERROR ) {
		cerr << "OpenGL error occoured\n";
	}

	SDL_GL_SwapBuffers();

	glDeleteTextures( 1, &texture);
	
	cout <<"--- Creating World ---" << endl;
	World *myWorld = new World(L);
	if( !myWorld->Create(config.TerrainFilename) ) {
		cout << "Creating World failed!" << endl;
		terminate(2);
	}
	cout << "--- World created! ---" << endl;
	cout << "-----------------------------------------------------------------";
	cout << endl;

	ReshapeGL(config.width, config.height, myWorld->GetDepth());
	srand(SDL_GetTicks());
	Uint32 OldTime=SDL_GetTicks();
	Uint32 frames = 0;
	Uint32 frameTimer = OldTime;
	cout << "Entering Main Loop" << endl;
	for(int done = 0; !done;)
	{
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
				cout << "SDL_VIDEORESIZE" << endl;
				config.width = event.resize.w;
				config.height = event.resize.h;
				if (SDL_SetVideoMode(config.width, config.height, 0, flags))
					ReshapeGL (config.width, config.height, myWorld->GetDepth() );
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
			default:
				break;
			};
		}
		Uint32 diff = Time-OldTime;
		
		myWorld->Update(diff, keyState);
		OldTime=Time;
		myWorld->Draw();
		SDL_GL_SwapBuffers();
		frames++;
		if(Time-frameTimer > 5000) {
			cout << "FPS: " << (float)frames*1000/(float)(Time-frameTimer) << endl;
			frameTimer = Time;
			frames = 0;
		}
	}
	delete myWorld;
	return(0);
}
