/*
 *  Final Project: The Taj Mahal
 *  Submitted by - Atharva R. Peshkar
 *
 *  References
 *  1) Course examples
 *  2) My homework submission
 *  3) Documentation
 *  4) Stack Overflow
 * 
 *
 *  Key bindings:
 *  p          Toggles ortogonal/perspective projection
 *  +/-        Change field of view of perspective
 *  x          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */

#include "CSCIx229.h"

int axes=1;       //  Display axes
int mode=1;       //  Projection mode
int th=0;         //  Azimuth of view angle
int ph=45;         //  Elevation of view angle
int fov=102;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=5;     //  Size of world
unsigned int texture[3]; // Texture names
int minaret_disk, minaret_tent, tomb_spire, tomb_tent;          //  Object display list

typedef struct {float x,y,z;} vtx;
#define n 500
vtx is[n];

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (mode)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }

   //  Enable textures
   // glEnable(GL_TEXTURE_2D);
   // glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
   // glBindTexture(GL_TEXTURE_2D,texture[0]);

   // Base of the Taj Mahal
   scale A = {4.5,0.3,4.5};
   rotate B = {0,0,0,0};
   translate C = {0,0,0};
   base(A,B,C);

   // // Base for the Minarets
   // // Front Right Minaret Base
   scale P = {0.32,0.32,0.32};
   rotate Q = {-25,0,0,1};
   glPushMatrix();
   glTranslatef(4.46,0,0);
   glTranslatef(0,0,4.46);
   glTranslatef(0,-0.29,0);
   octagonal_prism(P,Q);
   glPopMatrix();

   // Front Left Minaret Base
   glPushMatrix();
   glTranslatef(-4.46,0,0);
   glTranslatef(0,0,4.46);
   glTranslatef(0,-0.29,0);
   octagonal_prism(P,Q);
   glPopMatrix();

   // Back Left Minaret Base
   glPushMatrix();
   glTranslatef(-4.46,0,0);
   glTranslatef(0,0,-4.46);
   glTranslatef(0,-0.29,0);
   octagonal_prism(P,Q);
   glPopMatrix();

   // Back Right Minaret Base
   glPushMatrix();
   glTranslatef(4.46,0,0);
   glTranslatef(0,0,-4.46);
   glTranslatef(0,-0.29,0);
   octagonal_prism(P,Q);
   glPopMatrix();

   // Minarets
   // Front right minaret
   rotate S = {-3.5,0,1,0};
   rotate T = {3.8,0,1,0};
   glPushMatrix();
   glTranslatef(4.48,0,0);
   glTranslatef(0,0,4.48);
   glTranslatef(0,0.2,0);
   beveled_cylinder(P,S);
   glPopMatrix();

   // Front left minaret
   glPushMatrix();
   glTranslatef(-4.48,0,0);
   glTranslatef(0,0,4.48);
   glTranslatef(0,0.2,0);
   beveled_cylinder(P,T);
   glPopMatrix();

   // Back left minaret
   glPushMatrix();
   glTranslatef(-4.48,0,0);
   glTranslatef(0,0,-4.48);
   glTranslatef(0,0.2,0);
   beveled_cylinder(P,T);
   glPopMatrix();

   // Back right minaret
   glPushMatrix();
   glTranslatef(4.48,0,0);
   glTranslatef(0,0,-4.48);
   glTranslatef(0,0.2,0);
   beveled_cylinder(P,S);
   glPopMatrix();

   // glDisable(GL_TEXTURE_2D);


   // Tomb
   scale X = {3,2.8,2.8};
   translate Y = {0,0.18,0};
   beveled_cube(X,Y);

   //Gates of the tomb
   scale F = {1,1.7,0.06};
   rotate G = {0,0,0,0};
   translate H = {0,0,0};

   // Front Gate
   glPushMatrix();
   glColor3f(0.87,0.34,0.67);
   glTranslatef(0,0,0);
   glTranslatef(0,0,2.76);
   glTranslatef(0,2.1,0);
   gate(F,G,H);
   glPopMatrix();

   // Back Gate
   glPushMatrix();
   glTranslatef(0,0,0);
   glTranslatef(0,0,-2.76);
   glTranslatef(0,2.1,0);
   gate(F,G,H);
   glPopMatrix();

   // Right Gate
   glPushMatrix();
   glTranslatef(0,0,0);
   glTranslatef(2.96,0,0);
   glTranslatef(0,2.1,0);
   glRotatef(90,0,1,0);
   gate(F,G,H);
   glPopMatrix();

   // // Left Gate
   glPushMatrix();
   glTranslatef(0,0,0);
   glTranslatef(-2.96,0,0);
   glTranslatef(0,2.1,0);
   glRotatef(90,0,1,0);
   gate(F,G,H);
   glPopMatrix();

   // Main dome
   // glEnable(GL_TEXTURE_2D);
   // glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
   // glBindTexture(GL_TEXTURE_2D,texture[0]);

   scale K = {0.7,0.7,0.7};
   
   glPushMatrix();
   glTranslatef(0,3.32,0);
   main_dome(K);
   glPopMatrix();

   // Draw all the loaded objects
   // Tomb lotus spire
   glColor3f(0.78,0.45,0.89);
   glPushMatrix();
   glScaled(1.6,1.6,1.6);
   glTranslatef(0,0,0);
   glTranslatef(0,0,0);
   glTranslatef(0,3.6,0);
   glCallList(tomb_spire);
   glPopMatrix();

   // Front right minaret Disks
   glPushMatrix();
   glScaled(0.38,0.38,0.38);
   glTranslatef(11.6,0,0);
   glTranslatef(0,0,11.75);
   glTranslatef(0,3.6,0);
   glCallList(minaret_disk);
   glPopMatrix();

   glPushMatrix();
   glScaled(0.34,0.34,0.34);
   glTranslatef(12.8,0,0);
   glTranslatef(0,0,13.2);
   glTranslatef(0,7,0);
   glCallList(minaret_disk);
   glPopMatrix();

   // Back left minaret Disks
   glPushMatrix();
   glScaled(0.38,0.38,0.38);
   glTranslatef(-11.6,0,0);
   glTranslatef(0,0,-11.75);
   glTranslatef(0,3.6,0);
   glCallList(minaret_disk);
   glPopMatrix();

   glPushMatrix();
   glScaled(0.34,0.34,0.34);
   glTranslatef(-12.8,0,0);
   glTranslatef(0,0,-13.2);
   glTranslatef(0,7,0);
   glCallList(minaret_disk);
   glPopMatrix();

   // Back right minaret Disks
   glPushMatrix();
   glScaled(0.38,0.38,0.38);
   glTranslatef(11.6,0,0);
   glTranslatef(0,0,-11.75);
   glTranslatef(0,3.6,0);
   glCallList(minaret_disk);
   glPopMatrix();

   glPushMatrix();
   glScaled(0.34,0.34,0.34);
   glTranslatef(12.8,0,0);
   glTranslatef(0,0,-13.2);
   glTranslatef(0,7,0);
   glCallList(minaret_disk);
   glPopMatrix();

   // Front left minaret Disks
   glPushMatrix();
   glScaled(0.38,0.38,0.38);
   glTranslatef(-11.6,0,0);
   glTranslatef(0,0,11.75);
   glTranslatef(0,3.6,0);
   glCallList(minaret_disk);
   glPopMatrix();

   glPushMatrix();
   glScaled(0.34,0.34,0.34);
   glTranslatef(-12.8,0,0);
   glTranslatef(0,0,13.2);
   glTranslatef(0,7,0);
   glCallList(minaret_disk);
   glPopMatrix();

   // Front right minaret tent
   glPushMatrix();
   glScaled(0.32,0.32,0.32);
   glTranslatef(13.38,0,0);
   glTranslatef(0,0,14.1);
   glTranslatef(0,13.18,0);
   glCallList(minaret_tent);
   glPopMatrix();

   // Back left minaret tent
   glPushMatrix();
   glScaled(0.32,0.32,0.32);
   glTranslatef(-13.38,0,0);
   glTranslatef(0,0,-14.1);
   glTranslatef(0,13.18,0);
   glCallList(minaret_tent);
   glPopMatrix();

   // Back right minaret tent
   glPushMatrix();
   glScaled(0.32,0.32,0.32);
   glTranslatef(13.38,0,0);
   glTranslatef(0,0,-14.1);
   glTranslatef(0,13.18,0);
   glCallList(minaret_tent);
   glPopMatrix();

   // Front left minaret tent
   glPushMatrix();
   glScaled(0.32,0.32,0.32);
   glTranslatef(-13.38,0,0);
   glTranslatef(0,0,14.1);
   glTranslatef(0,13.18,0);
   glCallList(minaret_tent);
   glPopMatrix();

   // Tomb tents

   //Front right tomb tent
   glColor3f(0.76,0.89,0.19);
   glPushMatrix();
   glScaled(0.28,0.28,0.28);
   glTranslatef(5.6,0,0);
   glTranslatef(0,0,6);
   glTranslatef(0,15.1,0);
   glCallList(tomb_tent);
   glPopMatrix();

   //Back left tomb tent
   glColor3f(0.76,0.89,0.19);
   glPushMatrix();
   glScaled(0.28,0.28,0.28);
   glTranslatef(-5.6,0,0);
   glTranslatef(0,0,-6);
   glTranslatef(0,15.1,0);
   glCallList(tomb_tent);
   glPopMatrix();

   //Back right tomb tent
   glColor3f(0.76,0.89,0.19);
   glPushMatrix();
   glScaled(0.28,0.28,0.28);
   glTranslatef(5.6,0,0);
   glTranslatef(0,0,-6);
   glTranslatef(0,15.1,0);
   glCallList(tomb_tent);
   glPopMatrix();

   //Front left tomb tent
   glColor3f(0.76,0.89,0.19);
   glPushMatrix();
   glScaled(0.28,0.28,0.28);
   glTranslatef(-5.6,0,0);
   glTranslatef(0,0,6);
   glTranslatef(0,15.1,0);
   glCallList(tomb_tent);
   glPopMatrix();

   // glDisable(GL_TEXTURE_2D);

   glColor3f(1,1,1);
   if (axes)
   {
      const double len=5.0;  //  Length of axes
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }

   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s",
     th,ph,dim,fov,mode?"Perspective":"Orthogonal");

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(mode?fov:0,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
   {
      th = 0;
      ph = 45;
      fov = 102;
   }
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Switch projection mode
   else if (ch == 'p' || ch == 'P')
      mode = 1-mode;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  Reproject
   Project(mode?fov:0,asp,dim);
   // //  Animate if requested
   // glutIdleFunc(move?idle:NULL);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Set projection
   Project(mode?fov:0,asp,dim);
}

// Screen refresh
double time=100;
// Refreshing the display.
void timer(int val)
{
   glutPostRedisplay();
   glutTimerFunc(time, timer,0);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(800,800);
   glutCreateWindow("The Taj Mahal - Atharva R. Peshkar");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);

   //  Load textures
   texture[0] = LoadTexBMP("marble_tiles.bmp");
   texture[1] = LoadTexBMP("bronze_basecolor.bmp");

   // Load Blender objects
   minaret_disk = LoadOBJ("./minaret-disk-bl.obj");
   minaret_tent = LoadOBJ("./minaret_tent_bl.obj");
   tomb_spire = LoadOBJ("./tomb-simp-bl.obj");
   tomb_tent = LoadOBJ("./tomb-tent.obj");

   glutTimerFunc(0,timer,0);
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
