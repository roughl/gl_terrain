// OpengGL.c
#include "OpenGL.h"

#include <cmath>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>												// Header File For The GLu32 Library

unsigned LoadAlphaTexture(const char *filename)
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x000000ff;
#else
    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0xff000000;
#endif

    printf("AlphaTextur %s laden...\n", filename);
    SDL_Surface *bitmap, *alpha;  // surface pointer auf das bitmap und die textur
    unsigned texture;            // texture ID

    bitmap = SDL_LoadBMP(filename);   // bitmap einlesen
    if (!bitmap) {
        fprintf(stderr, "%s: konnte nicht geladen werden\n", filename);
        exit(1);
    }
    // RGB Surface zur konvertierung in Textur erstellen
    alpha = SDL_CreateRGBSurface(SDL_SWSURFACE, bitmap->w, bitmap->h, 32,
            rmask, gmask, bmask, amask);

    SDL_BlitSurface(bitmap, 0, alpha, 0); // surface umwandeln

/*    SDL_Surface *surface = SDL_CreateRGBSurface(SDL_SWSURFACE, alpha.width, alpha.height, 32,
                                   rmask, gmask, bmask, amask); */
    SDL_FreeSurface(bitmap); // zwischenspeicher des Bitmaps löschen
    
      Pixel *alp = (Pixel *)(void *)alpha->pixels;
      for (int y = 0; y < alpha->h; y++) {
          for (int x = 0; x < alpha->w; x++) {
            (alp+y*64+x)->a = (alp+y*64+x)->r; // set alpha from r
            (alp+y*64+x)->r = 255; // White Texture
            (alp+y*64+x)->g = 255;
            (alp+y*64+x)->b = 255;
          }
      }

        glGenTextures(1, &texture); // Textur erstellen
        glBindTexture(GL_TEXTURE_2D, texture); // als 2D Textur definieren
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// Filter konfigurieren
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glPixelStorei(GL_UNPACK_ROW_LENGTH, alpha->pitch / alpha->format->BytesPerPixel);
         
        glTexImage2D(GL_TEXTURE_2D, 0,GL_ALPHA, alpha->w, alpha->h, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, alpha->pixels);// angaben zur grösse, farbbereich und wo die pixeldaten sind
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    
        SDL_FreeSurface(alpha); // zwischenspeicher des Bitmaps löschen
        return texture;
}


unsigned LoadTexture(const char *filename)
{
    printf("Textur %s laden...\n", filename);
    SDL_Surface *bitmap, *conv;  // surface pointer auf das bitmap und die textur
    unsigned texture;            // texture ID

    bitmap = SDL_LoadBMP(filename);   // bitmap einlesen
    if (!bitmap) {
        fprintf(stderr, "%s: konnte nicht geladen werden\n", filename);
        exit(1);
    }
    // RGB Surface zur konvertierung in Textur erstellen
    conv = SDL_CreateRGBSurface(SDL_SWSURFACE, bitmap->w, bitmap->h, 32,
#if SDL_BYTEORDER == SDL_BIG_ENDIAN  // wie ist die Byteorder?
            0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
#else
                        0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
#endif

    SDL_BlitSurface(bitmap, 0, conv, 0);
    
    glGenTextures(1, &texture); // Textur erstellen
    glBindTexture(GL_TEXTURE_2D, texture); // als 2D Textur definieren
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// Filter konfigurieren
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glPixelStorei(GL_UNPACK_ROW_LENGTH, conv->pitch / conv->format->BytesPerPixel);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, conv->w, conv->h, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, conv->pixels);// angaben zur grösse, farbbereich und wo die pixeldaten sind
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

    SDL_FreeSurface(bitmap); // zwischenspeicher des Bitmaps löschen
    SDL_FreeSurface(conv);

    return texture;
}



void ReshapeGL (int width, int height, float depth)									// Reshape The Window When It's Moved Or Resized
{
	glViewport (0, 0, (GLsizei)(width), (GLsizei)(height));				// Reset The Current Viewport
	glMatrixMode (GL_PROJECTION);										// Select The Projection Matrix
	glLoadIdentity ();													// Reset The Projection Matrix
	gluPerspective (90.0f, (GLfloat)(width)/(GLfloat)(height),			// Calculate The Aspect Ratio Of The Window
					1.0f, depth);
    glFogf(GL_FOG_START, 2.0f);				    // Fog Start Depth
    glFogf(GL_FOG_END, depth);				        // Fog End Depth		
	glMatrixMode (GL_MODELVIEW);										// Select The Modelview Matrix
	glLoadIdentity ();													// Reset The Modelview Matrix
/*	
	float LightPos[4]={64.0f,12.0f,64.0f,0.0f};
    float Ambient[4]={0.75f,0.75f,0.75f,1.0f};
    GL_SetLight(LightPos, Ambient);
*/    
}
    

		



void GL_SetLight(float *Position, float *Ambient, float *Difuse, float *Specular)
{
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);
    glLightfv(GL_LIGHT0,GL_AMBIENT,Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,Difuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);

}

bool InitializeGL ( )					// Any GL Init Code & User Initialiazation Goes Here
{

	// Start Of User Initialization

	glClearColor (0.5f, 0.5f, 0.5f, 0.0f);						 // Dark Background
	glClearDepth (2.0f);										 // Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);									 // The Type Of Depth Testing (Less Or Equal)
	glEnable (GL_DEPTH_TEST);								 	 // Enable Depth Testing
	glShadeModel (GL_SMOOTH);									 // Select Shading GL_FLAT or GL_SMOOTH
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			 // Set Perspective Calculations To Most Accurate
  //  glCullFace(GL_BACK);
    glFrontFace(GL_CCW); 
    glEnable(GL_CULL_FACE);
    
    GLfloat fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f};		// Fog Color

    glFogi(GL_FOG_MODE, GL_EXP);		            // Fog Mode
    glFogfv(GL_FOG_COLOR, fogColor);		        // Set Fog Color
    glFogf(GL_FOG_DENSITY, 0.05f);				    // How Dense Will The Fog Be
    glHint(GL_FOG_HINT, GL_DONT_CARE);			    // Fog Hint Value
    glEnable(GL_FOG);					            // Enables GL_FOG
    glLoadIdentity ();											// Reset The Modelview Matrix
    //glTranslatef(64.0f, 30.0f, 64.0f);
/*    float pos[4], amb[4], dif[4], spec[4];
    pos[0]=0.0f;pos[1]=-1.0f;pos[2]=10.0f;pos[3]=0.0f;
    amb[0]=0.01f;amb[1]=0.01f;amb[2]=0.01f;amb[3]=1.0f;
    dif[0]=0.5f; dif[1]=0.5f; dif[2]=0.5f; dif[3]=0.5f;
    spec[0]=1.0f;spec[1]=1.0f;spec[2]=1.0f;spec[3]=1.0f;
    GL_SetLight(pos, amb, dif, spec);

*/
	return true;												// Return TRUE (Initialization Successful)
}

void DeinitializeGL (void)										// Any User DeInitialization Goes Here
{
}
