//--------------------------------------------------------------------------------------------------
// file: tomprogs_opengl_tutorial_02.cpp
// description: Contains the whole code used in the OpenGL Tutorial 02 at www.tomprogs.at
//--------------------------------------------------------------------------------------------------
// Copyright (c) 2008 - 2010, Thomas Geymayer
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted
// provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice, this list of 
//      conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright notice, this list of
//      conditions and the following disclaimer in the documentation and/or other materials
//      provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
// FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
// WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//--------------------------------------------------------------------------------------------------

#include "SDL.h"
#include "SDL_opengl.h"

#include <iostream>
 
#include "application_window.h" // Hier ist die neue Klasse drinnen

//using std::cout;    // Wir verwenden std::cout und
//using std::endl;    // std::endl für die Konsolenausgaben

#define MSEC_FRAMES 17/* 60 FPS(~17 milliseconds between frames) is enough, '0' will disable frame limiter */


// Die neue Polling-Funktion
bool pollEvents()
{
  SDL_Event event;
 
  while( SDL_PollEvent(&event) ) // Nächste Nachricht holen
  {
    switch(event.type)
    {
      case SDL_QUIT:
        return false; // Programm sollte beendet werden
      default:
        break;
    }
  }
 
  return true;
}

int main(int argc, char **argv)
{
  if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) // Initialisieren des SDL Video Subsystems
  {
 
    //cout << "Die SDL konnte nicht initalisiert werden (" << SDL_GetError() << ")" << endl; 
    return 1;
 
  }
 
  // Ein Fenster mit 800*600 Pixeln bei 32 Bit Farbtiefe anlegen
  ApplicationWindow *game_window =
    new ApplicationWindow( 800, 600, 32 );
 
  // Den Fenstertitel setzen
  game_window->setCaption( "64k Intro Test-01" );
 
  // Und schließlich das Fenster erzeugen lassen
  game_window->create();
 
  // Die Endlosschleife
  unsigned int counter = 0;
  Uint32 tlast = 0,
         tcurrent, st;
  st = SDL_GetTicks();

  // load a texture
  GLuint texture;			// This is a handle to our texture object
SDL_Surface *surface;	// This surface will tell us the details of the image
GLenum texture_format;
GLint  nOfColors;
 
  surface = SDL_CreateRGBSurface(SDL_SWSURFACE,512,512,32,0,0,0,0);

 if ( surface ) { 
	// Check that the image's width is a power of 2
	if ( (surface->w & (surface->w - 1)) != 0 ) {
		printf("warning: image.bmp's width is not a power of 2\n");
	}
 
	// Also check if the height is a power of 2
	if ( (surface->h & (surface->h - 1)) != 0 ) {
		printf("warning: image.bmp's height is not a power of 2\n");
	}
 
        // get the number of channels in the SDL surface
        nOfColors = surface->format->BytesPerPixel;
        if (nOfColors == 4)     // contains an alpha channel
        {
                if (surface->format->Rmask == 0x000000ff)
                        texture_format = GL_RGBA;
                else
                        texture_format = GL_BGRA;
        } else if (nOfColors == 3)     // no alpha channel
        {
                if (surface->format->Rmask == 0x000000ff)
                        texture_format = GL_RGB;
                else
                        texture_format = GL_BGR;
        } else {
                printf("warning: the image is not truecolor..  this will probably break\n");
                // this error should not go unhandled
        }
 
	// Have OpenGL generate a texture object handle for us
	glGenTextures( 1, &texture );
 
	// Bind the texture object
	glBindTexture( GL_TEXTURE_2D, texture );
 
	// Set the texture's stretching properties
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
 
	// Edit the texture object's image data using the information SDL_Surface gives us
	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
                      texture_format, GL_UNSIGNED_BYTE, surface->pixels );
} 
else {
	printf("SDL could not load image.bmp: %s\n", SDL_GetError());
	SDL_Quit();
	return 1;
}    
 
// Free the SDL_Surface only if it was successfully created
if ( surface ) { 
	SDL_FreeSurface( surface );
}
 

  while(true)
  {
	//------------------------- 
    // Nachrichten verarbeiten:
    //-------------------------
    if( !pollEvents() ) break;
		
	tcurrent = SDL_GetTicks();
    if(tcurrent < tlast + MSEC_FRAMES)
    	usleep(1000*(tlast + MSEC_FRAMES - tcurrent));

    
    counter++;
	counter = counter%360;    
   
   
    //----------------------------------
    // Den aktuellen Bildbuffer löschen:
    //----------------------------------
   
    glClearColor( 0.0, 0.0, 0.1, 0.0 ); // Farbe zum Löschen setzen
    glClear( GL_COLOR_BUFFER_BIT );     // Aktuellen Bildbuffer löschen
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   


    //--------------------------
    // Die Projektion festlegen:
    //--------------------------
   
    glMatrixMode( GL_PROJECTION ); // Stack für Projektionsmatrix als
                                   // aktiven Matrixstack setzen
    glLoadIdentity();              // Identitätsmatrix auf den Stack laden
   glRotated(counter/1.,0,0,1);
    // Eine orthogonale Projektionsmatrix zum Stack
    // dazu multiplizieren.
    glOrtho( 0, 800, 600, 0, -1, 1 );
   	
    //----------------------
    // Das Dreieck zeichnen:
    //----------------------
    
    glBindTexture( GL_TEXTURE_2D, texture );
    glBegin( GL_TRIANGLES ); // Wir wollen ein Dreieck zeichnen
      

      //glColor3f(1,0,0);      // Ab jetzt werden alle gezeichneten Punkte rot
	  glTexCoord2f(1.0f, 0.0f);
      glVertex3f(400,100,0); // Der erste Eckpunkt ist mittig und 100 Pixel
                             // vom oberen Rand entfernt
   
      //glColor3f(0,1,0);      // Ab jetzt werden alle gezeichneten Punkte grün
      glTexCoord2f(0.0f, 1.0f);
	  glVertex3f(750,500,0); // Der zweite Eckpunkt ist 50 Pixel vom rechten
                             // und 100 Pixel vom unteren Rand entfernt
   
      //glColor3f(0,0,1);      // Ab jetzt werden alle gezeichneten Punkte blau
      glTexCoord2f(1.0f, 1.0f);
	  glVertex3f(50,500,0);  // Der dritte Eckpunkt ist 50 Pixel vom linken
                             // und 100 Pixel vom unteren Rand entfernt
   
    glEnd(); // Wir sind fertig mit dem Zeichnen
   
    SDL_GL_SwapBuffers(); // Bildbuffer vertauschen (als Letztes)



    tlast = tcurrent;
  }
 
  SDL_Quit();
 
  return 0;
}

