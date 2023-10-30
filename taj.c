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
double asp=1;     //  Aspect ratio
double dim=5;     //  Size of world
double rep=1;  //  Repetition

typedef struct {float x,y,z;} vtx;
#define n 500
vtx is[n];

// static void pentagon(vtx A,vtx B,vtx C,vtx D,vtx E)
// {
//    //  Planar vector 0
//    float dx0 = A.x-C.x;
//    float dy0 = A.y-C.y;
//    float dz0 = A.z-C.z;

//     float dx1 = A.x-D.x;
//     float dy1 = A.y-D.y;
//     float dz1 = A.z-D.z;
//    //  Normal
//    float Nx = dy0*dz1 - dy1*dz0;
//    float Ny = dz0*dx1 - dz1*dx0;
//    float Nz = dx0*dy1 - dx1*dy0;
    
//    //  Draw pentagon
//    glNormal3f(Nx,Ny,Nz);
//    glBegin(GL_POLYGON);
//    glTexCoord2f(0.5, 1.0); glVertex3f(A.x,A.y,A.z);
//    glTexCoord2f(0.8, 1.0); glVertex3f(B.x,B.y,B.z);
//    glTexCoord2f(1.0, 0.0); glVertex3f(C.x,C.y,C.z);
//    glTexCoord2f(0.0, 0.0); glVertex3f(D.x,D.y,D.z);
//    glTexCoord2f(0.2, 1.0); glVertex3f(E.x,E.y,E.z);
//    glEnd();
// }

// /*
//  *  Draw dodecahedron
//  *     at (x,y,z)
//  *     size  s
//  *     rotated th about the x axis
//  */
// static void dodecahedron(float x,float y,float z,float s,float th)
// {
//    GLfloat ambient[] = { 0.05, 0.05, 0.05, 1.0 };
//    GLfloat diffuse[] = { 0.8, 0.8, 0.8, 0.5 };
//    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat emission[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat shininess = 100.0;

//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
//    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

//    //  Draw dodecahedron
//    glPushMatrix();
//    glTranslatef(x,y,z);
//    glScalef(s,s,s);
//    glRotatef(th,0,1,0);
//    glRotatef(55,1,0,0);
//    // //  Enable textures
//    // glEnable(GL_TEXTURE_2D);
//    // glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
//    // glBindTexture(GL_TEXTURE_2D,texture[0]);
//    for (int i=0;i<Do_N;i++)
//    {
//       pentagon(xyz_dodec[idx_dodec[i].A],xyz_dodec[idx_dodec[i].B],xyz_dodec[idx_dodec[i].C],
//                xyz_dodec[idx_dodec[i].D],xyz_dodec[idx_dodec[i].E]);
//    }
     
//    glPopMatrix();
// }

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

   // Base of the Taj Mahal
   scale A = {9,0.6,9};
   rotate B = {0,0,0,0};
   translate C = {0,0,0};
   base(A,B,C);

   // Base for the Minarets
   // Front Right Minaret Base
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


   // glPushMatrix();
   // glTranslatef(0,0,0);
   // glTranslatef(0,0,0);
   // glTranslatef(0,0,0);
   // disk(P,S);
   // glPopMatrix();

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
     th,ph,dim,fov,mode?"Perpective":"Orthogonal");

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
   glutCreateWindow("Taj - Atharva R. Peshkar");
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

   glutTimerFunc(0,timer,0);
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
