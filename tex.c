                                                 
/*
Perlin noise
	               PROCEDURAL TEXTURES using OPENGL

In this article, I don't speak about the Procedural Textures teori,
you can found very good information in this page and here (spain)

I write this page because a don't found a simple example to make
a Procedural Texture,now I have compiled information to develop
a OPENGL Procedural Texture to making futures landscape.

Now the code is simple ,is the better moment to explaint it
We are using Linux,OpenGl and C++.


http://www.sorgonet.com/linux/noise_textures/

Usin a big number on "Width  " variable avoid a imagen repetition ,if your like
and "seed" variable make a other imagex
Your can use "scale"  variable  to scale a imagen box
zoom  

*/

	///WWW.SorgoNet.COM PerlinNoise map .27-01-03
//To compile $ gcc tex.c -lglut -lGLU -lGL

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>


#define    ImageWidth 524
#define    ImageHeight 524
//GLubyte MatrixImage[ImageHeight][ImageWidth][3];



float InterPolation(float a, float b, float c)
{   
    return a+(b-a)*c*c*(3-2*c);               
                                           
}


float InterLinear(float a, float b, float c)
{    
      return a*(1-c)+b*c;                                         
}

float Noise( int x)
{
    x = (x<<13)^x;
    return (((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 2147483648.0);
   }

 float PerlinNoise(float x,float y,int width,int octaves,int seed,double periode){
          
           double a,b,value,freq,tam_pas,zone_x,zone_y;
           int s,box,num,step_x,step_y;
           int amplitude=120;
           int noisedata;
      
       freq=1/(float)(periode);

           for ( s=0;s<octaves;s++){
        num=(int)(width*freq);
                step_x=(int)(x*freq);
                step_y=(int)(y*freq);
                zone_x=x*freq-step_x;
                zone_y=y*freq-step_y;
                box=step_x+step_y*num;
        noisedata=(box+seed);
                a=InterPolation(Noise(noisedata),Noise(noisedata+1),zone_x);
                b=InterPolation(Noise(noisedata+num),Noise(noisedata+1+num),zone_x);
                value=InterPolation(a,b,zone_y)*amplitude;

              }
          return value;
              }



void colour (float valor, float *RGB){
      int r=InterLinear(valor,0,0 );
      int g=InterLinear(0,valor);
      int b=InterLinear(0,0,valor);

      RGB[0]=r;
      RGB[1]=g;
      RGB[2]=b;
}
                  
void makeImage(GLubyte ***MatrixImage)
{
 
 int x,y;
 float color;
 int seed;
 int width;
 float  disp1,disp2,disp3,disp4,disp5,disp6,scale;

for(y=0;y< ImageWidth; y++){
        for(x=0;x<ImageHeight; x++){
      scale=1;
      width=12413;
      seed=63;
   
    disp1= PerlinNoise(x*scale,y*scale,width,1,seed,100);
    disp2= PerlinNoise(x*scale,y*scale,width,1,seed,25);
    disp3= PerlinNoise(x*scale,y*scale,width,1,seed,12.5);
    disp4= PerlinNoise(x*scale,y*scale,width,1,seed,6.25);
    disp5= PerlinNoise(x*scale,y*scale,width,1,seed,3.125);
    disp6= PerlinNoise(x*scale,y*scale,width,1,seed,1.56);
        

    float RGB[3];     
     colour((int)disp1+(int)(disp2*.25)+(int)(disp3*.125)+(int)(disp4*.0625)+(int)(disp5*.03125)+(int)(disp6*.0156), &RGB[0]);
 
      MatrixImage[x][y][0] = RGB[0];
      MatrixImage[x][y][1] = RGB[1];
      MatrixImage[x][y][2] = RGB[2];  
    }}


 
}       

void init(GLubyte ***MatrixImage)
{   
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   makeImage(MatrixImage);
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void display(void)
{
   /* how to insert my matrix?*/
   glClear(GL_COLOR_BUFFER_BIT);
   glRasterPos2i(0, 0);
   glDrawPixels(ImageWidth, ImageHeight, GL_RGB,
                GL_UNSIGNED_BYTE, MatrixImage);
   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   GLint height = (GLint) h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}


void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
    
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(524, 524);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   GLubyte MatrixImage[ImageHeight][ImageWidth][3];
   init(MatrixImage);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}


