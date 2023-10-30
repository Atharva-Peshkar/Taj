/*
 *  Homework 6: Lighting and Textures
 *  Submitted by - Atharva R. Peshkar
 *
 *  References
 *  1) Ex 13, 14, 15
 *  2) StackOverflow
 * 
 *
 *  Key bindings:
 *  l          Toggles lighting
 *  a/A        Decrease/increase ambient light
 *  d/D        Decrease/increase diffuse light
 *  s/S        Decrease/increase specular light
 *  e/E        Decrease/increase emitted light
 *  n/N        Decrease/increase shininess
 *  F1         Toggle smooth/flat shading
 *  F2         Toggle local viewer mode
 *  F3         Toggle light distance (1/5)
 *  F8         Change ball increment
 *  F9         Invert bottom normal
 *  m          Toggles light movement
 *  []         Lower/rise light
 *  p          Toggles ortogonal/perspective projection
 *  o          Cycles through objects
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
int move=1;       //  Move light
int th=-40;         //  Azimuth of view angle
int ph=40;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int obj=0;        //  Scene/opbject selection
double asp=1;     //  Aspect ratio
double dim=3;     //  Size of world
double rep=1;  //  Repetition

// Light values
int light     =   1;  // Lighting
int one       =   1;  // Unit value
int distance  =   5;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   100;  // Emission intensity (%)
int ambient   =  40;  // Ambient intensity (%)
int diffuse   =  50;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light
unsigned int texture[2]; // Texture names

typedef struct {float x,y,z;} vtx;
typedef struct {int A,B,C;} tri;
typedef struct {int A,B,C,D,E;} pent;
#define n 500
vtx is[n];

/*
 *  Dodecahedron data
 */
const int Do_N=12;
//  Pentagon index list
const pent idx_dodec[] =
   {
      {0,  1,  2,  3,  4}, {5,  6,  7,  8,  9}, {10, 11,  3,  2, 12}, 
      {13, 14,  8,  7, 15}, {3, 11, 16, 17,  4}, {2,  1, 18, 19, 12}, 
      {7,  6, 17, 16, 15}, {8, 14, 19, 18,  9}, {17,  6,  5,  0,  4}, 
      {16, 11, 10, 13, 15}, {18,  1,  0,  5,  9}, {19, 14, 13, 10, 12}
   };
//  Vertex coordinates
const vtx xyz_dodec[] =
   {
      {0.0,1.61803398875,0.61803398875},{-1.0,1.0,1.0},{-0.61803398875,0.0,1.61803398875},{0.61803398875,0.0,1.61803398875},
      {1.0,1.0,1.0},{0.0,1.61803398875, -0.61803398875},{1.0,1.0, -1.0},{0.61803398875,0.0, -1.61803398875},
      {-0.61803398875,0.0, -1.61803398875},{-1.0,1.0, -1.0},{0.0, -1.61803398875,0.61803398875},{1.0, -1.0,1.0},
      {-1.0, -1.0,1.0},{0.0, -1.61803398875, -0.61803398875},{-1.0, -1.0, -1.0},{1.0, -1.0, -1.0},
      {1.61803398875, -0.61803398875,0.0},{1.61803398875,0.61803398875,0.0},{-1.61803398875,0.61803398875,0.0},{-1.61803398875, -0.61803398875,0.0}
   };

/*
 *  Octahedron data
 */
const int Oct_N=8;
//  Vertex index list
const tri idx_octa[] =
{
   {0, 1, 2},{0, 5, 1},{0, 2, 4},{0, 4, 5},
   {3, 2, 1},{3, 1, 5},{3, 4, 2},{3, 5, 4}
};
//  Vertex coordinates
const vtx xyz_octa[] =
{
   {1.0,  0.0,  0.0}, {0.0,  1.0,  0.0},  {0.0,  0.0,  1.0},
   {-1.0,  0.0,  0.0},{0.0, -1.0,  0.0}, {0.0,  0.0, -1.0} 
};

/*
 * Draw triangle
 */
static void triangle(vtx A,vtx B,vtx C)
{
   //  Planar vector 0
   float dx0 = A.x-B.x;
   float dy0 = A.y-B.y;
   float dz0 = A.z-B.z;

    float dx1 = A.x-C.x;
    float dy1 = A.y-C.y;
    float dz1 = A.z-C.z;
   //  Normal
   float Nx = dy0*dz1 - dy1*dz0;
   float Ny = dz0*dx1 - dz1*dx0;
   float Nz = dx0*dy1 - dx1*dy0;
    
   //  Draw triangle
   glNormal3f(Nx,Ny,Nz);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0,0); glVertex3f(A.x,A.y,A.z);
   glTexCoord2f(rep  ,0.0); glVertex3f(B.x,B.y,B.z);
   glTexCoord2f(rep/2,rep); glVertex3f(C.x,C.y,C.z);
   glEnd();
}

static void pentagon(vtx A,vtx B,vtx C,vtx D,vtx E)
{
   //  Planar vector 0
   float dx0 = A.x-C.x;
   float dy0 = A.y-C.y;
   float dz0 = A.z-C.z;

    float dx1 = A.x-D.x;
    float dy1 = A.y-D.y;
    float dz1 = A.z-D.z;
   //  Normal
   float Nx = dy0*dz1 - dy1*dz0;
   float Ny = dz0*dx1 - dz1*dx0;
   float Nz = dx0*dy1 - dx1*dy0;
    
   //  Draw pentagon
   glNormal3f(Nx,Ny,Nz);
   glBegin(GL_POLYGON);
   glTexCoord2f(0.5, 1.0); glVertex3f(A.x,A.y,A.z);
   glTexCoord2f(0.8, 1.0); glVertex3f(B.x,B.y,B.z);
   glTexCoord2f(1.0, 0.0); glVertex3f(C.x,C.y,C.z);
   glTexCoord2f(0.0, 0.0); glVertex3f(D.x,D.y,D.z);
   glTexCoord2f(0.2, 1.0); glVertex3f(E.x,E.y,E.z);
   glEnd();
}

/*
 *  Draw dodecahedron
 *     at (x,y,z)
 *     size  s
 *     rotated th about the x axis
 */
static void dodecahedron(float x,float y,float z,float s,float th)
{
   GLfloat ambient[] = { 0.05, 0.05, 0.05, 1.0 };
   GLfloat diffuse[] = { 0.8, 0.8, 0.8, 0.5 };
   GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat emission[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat shininess = 100.0;

   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

   //  Draw dodecahedron
   glPushMatrix();
   glTranslatef(x,y,z);
   glScalef(s,s,s);
   glRotatef(th,0,1,0);
   glRotatef(55,1,0,0);
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   for (int i=0;i<Do_N;i++)
   {
      pentagon(xyz_dodec[idx_dodec[i].A],xyz_dodec[idx_dodec[i].B],xyz_dodec[idx_dodec[i].C],
               xyz_dodec[idx_dodec[i].D],xyz_dodec[idx_dodec[i].E]);
   }
     
   glPopMatrix();
}

/*
 *  Draw octahedron
 *     at (x,y,z)
 *     size  s
 *     rotated th about the x axis
 */
static void octahedron(float x,float y,float z,float s,float th)
{
   //  Octahedron
   float black[]  = {0.0,0.0,0.0,1.0};
   float purple[] = {1.0,1.0,1.0,1.0};
   float white[]  = {1.0,1.0,1.0,1.0};
   glColor4fv(purple);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,purple);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   //  Draw octahedron
   glPushMatrix();
   glTranslatef(x,y,z);
   glScalef(s,s,s);
   glRotatef(th,0,1,0);
   glRotatef(90,0,1,0);

   for (int i=0;i<Oct_N;i++)
   {
      triangle(xyz_octa[idx_octa[i].A],xyz_octa[idx_octa[i].B],xyz_octa[idx_octa[i].C]);
   }
   glPopMatrix();
}

/*
 *  Draw vertex in polar coordinates with normal
 */
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
static void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball with yellow specular
   float yellow[]   = {1.0,1.0,0.0,1.0};
   float Emission[] = {0.0,0.0,0.01*emission,1.0};
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (int ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

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

   //  Flat or smooth shading
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light position
      float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 0.1);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  Location of viewer for specular calculations
      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
      glDisable(GL_LIGHTING);

   //  Draw individual objects
   if (obj==1)
     dodecahedron(0,0,0 , 0.6 , 0);
   else if(obj==2)
   {
      octahedron(0,0,1.5,0.4,0);
      octahedron(1.5,0,0,0.4,0);
   }
   //  Basic scene
   else
   {
      dodecahedron(0,0,0 , 0.6 , 0);
      octahedron(0,0,1.5,0.4,0);
      octahedron(1.5,0,0,0.4,0);
   }

   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   if (axes)
   {
      const double len=2.0;  //  Length of axes
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
   Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s Light=%s",
     th,ph,dim,fov,mode?"Perpective":"Orthogonal",light?"On":"Off");
   if (light)
   {
      glWindowPos2i(5,45);
      Print("Model=%s LocalViewer=%s Distance=%d Elevation=%.1f",smooth?"Smooth":"Flat",local?"On":"Off",distance,ylight);
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(60*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
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
   //  Smooth color model
   else if (key == GLUT_KEY_F1)
      smooth = 1-smooth;
   //  Local Viewer
   else if (key == GLUT_KEY_F2)
      local = 1-local;
   else if (key == GLUT_KEY_F3)
      distance = (distance==1) ? 5 : 1;
   //  Toggle ball increment
   else if (key == GLUT_KEY_F8)
      inc = (inc==10)?3:10;
   //  Flip sign
   else if (key == GLUT_KEY_F9)
      one = -one;
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
      th = -40;
      ph = 40;
   }
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Switch projection mode
   else if (ch == 'p' || ch == 'P')
      mode = 1-mode;
   //  Toggle light movement
   else if (ch == 'm' || ch == 'M')
      move = 1-move;
   //  Move light
   else if (ch == '<')
      zh += 1;
   else if (ch == '>')
      zh -= 1;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //  Ambient level
   else if (ch=='a' && ambient>0)
      ambient -= 5;
   else if (ch=='A' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='d' && diffuse>0)
      diffuse -= 5;
   else if (ch=='D' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='s' && specular>0)
      specular -= 5;
   else if (ch=='S' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='e' && emission>0)
      emission -= 5;
   else if (ch=='E' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1)
      shininess -= 1;
   else if (ch=='N' && shininess<7)
      shininess += 1;
   //  Switch scene/object
   else if (ch == 'o')
      obj = (obj+1)%6;
   else if (ch == 'O')
      obj = (obj+5)%6;
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(mode?fov:0,asp,dim);
   //  Animate if requested
   glutIdleFunc(move?idle:NULL);
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
   glutCreateWindow("HW6 - Atharva R. Peshkar");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   texture[0] = LoadTexBMP("./diam.bmp");
   texture[1] = LoadTexBMP("./wood.bmp");
   // Refreshing the display
   glutTimerFunc(0,timer,0);
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
