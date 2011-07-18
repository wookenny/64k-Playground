#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <iostream>
 
#include "Image.h"
#include "ImageStack.h"
#include "ApplicationWindow.h"

#define MSEC_FRAMES 17/* 60 FPS(~17 milliseconds between frames) is enough, '0' will disable frame limiter */

unsigned const int imageWidth = 512, imageHeight = 512;

void gl_init(){
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	GLubyte image[imageWidth][imageHeight][3];
	Image img;

	/** Here comes my image creation process **/
	Image_ptr base_ptr = Image_ptr(new Image(
						Image::createCheckersBoard(imageWidth,imageHeight,Color::RED,Color::YELLOW,64,64)
						));
	Image_ptr layer1 = Image_ptr(new Image(
						Image::createCheckersBoard(imageWidth,imageHeight,Color::BLACK,Color::WHITE,128,128)
						));
	Image_ptr layer2 = Image_ptr(new Image(
						Image::createCheckersBoard(2*imageWidth,2*imageHeight,Color::BLACK,Color::WHITE,8,8)
						));
	layer2->rotate(Image::PI/8);	
	std::vector<std::vector<float> > mask1 = Image::createSolidColorMask(imageWidth,imageHeight,.5);

	ImageStack stack( base_ptr );
	stack.push(layer1, mask1);
	stack.push(layer2,Image::createSolidColorMask(2*imageWidth,2*imageHeight,.1));

	//add to stack
	img = stack.getCondensedImage();
	/** Here it ends and i copy iot to an array **/



	for(unsigned int i = 0; i<imageWidth;++i)
		for(unsigned int j = 0; j<imageHeight;++j){
			image[i][j][0] = img.at(i,j).getRed();
			image[i][j][1] = img.at(i,j).getGreen();
			image[i][j][2] = img.at(i,j).getBlue(); 		
		}
	
	// loadImage();	
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, 
	imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 
	&image[0][0][0]);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT);


}


bool pollEvents()
{
  SDL_Event event;
 
  while( SDL_PollEvent(&event) ) 
  {
    switch(event.type)
    {
      case SDL_QUIT:
        return false; 
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
 
    std::cout << "Die SDL konnte nicht initalisiert werden (" << SDL_GetError() << ")" << std::endl; 
    return 1;
 
  }
 

	ApplicationWindow *game_window =
	new ApplicationWindow( 800, 600, 32 );
	game_window->setCaption( "64k Intro Test-01" );
 
	game_window->create();
	 
	  // Die Endlosschleife
	unsigned int counter = 0;
	unsigned int tlast = 0, tcurrent, st;
	st = SDL_GetTicks();


   gl_init();

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
    
    
    // Eine orthogonale Projektionsmatrix zum Stack
    // dazu multiplizieren.
    glOrtho( 0, 800, 600, 0, -1, 1 );
    
    //gluPerspective(60, 800./600, 0, 4);
    //gluLookAt(px,py,pz, lx,ly,lz, ux,uy,uz);
    //gluLookAt(1,1,1, 0,0,0, 0,1,0);



   	
    //----------------------
    // Texturen malen
    //----------------------

	glMatrixMode( GL_MODELVIEW ); 
	glLoadIdentity();

	//shift to center of the quad and rotate
	glTranslated(200,300,0);	
	glRotated(counter/1.,0,0,1);
	glTranslated(-200,-300,0);
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin( GL_QUADS );
      		glTexCoord2f(0.0f, 0.0f); glVertex3f(100,200,0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(100,400,0);
   		glTexCoord2f(1.0f, 1.0f); glVertex3f(300,400,0);  
		glTexCoord2f(1.0f, 0.0f); glVertex3f(300,200,0);
	glEnd(); 

	//draw an unrotated quad
	glLoadIdentity();
 	glBegin( GL_QUADS );
      		glTexCoord2f(0.0f, 0.0f); glVertex3f(100+400,200,0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(100+400,400,0);
   		glTexCoord2f(1.0f, 1.0f); glVertex3f(300+400,400,0);  
		glTexCoord2f(1.0f, 0.0f); glVertex3f(300+400,200,0);
	glEnd();

    SDL_GL_SwapBuffers(); // Bildbuffer vertauschen (als Letztes)



    tlast = tcurrent;
  }
 
  SDL_Quit();
 
  return 0;
}

