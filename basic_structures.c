#include "CSCIx229.h"

void cube()
{
   glPushMatrix();
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
   glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
   glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
   glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
   glEnd();
   //  Back
   glBegin(GL_QUADS);
   glNormal3f( 0, 0,-1);
   glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
   glEnd();
   //  Right
   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
   glEnd();
   //  Left
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();
   //  Top
   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();
   //  Bottom
   glBegin(GL_QUADS);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
   glEnd();
   //  Undo transformations and textures
   glPopMatrix();
}


// Base of the Taj Mahal
void base(scale S, rotate R, translate T)
{

   glColor3f(1, 0, 0);
   glPushMatrix();
   glScaled(S.x,S.y,S.z); 
   glRotatef(R.a,R.x,R.y,R.z);
   glTranslatef(T.x,T.y,T.z);
   cube();
   glPopMatrix();

   glColor3f(1, 0, 0);
   glPushMatrix();
   glScaled(S.x/3,S.y,S.z/9);
   glTranslatef(T.x,T.y,T.z+9.7);
   cube();
   glPopMatrix();
} 

void octagonal_prism(scale S, rotate R)
{
   glPushMatrix();

   glScaled(S.x,S.y,S.z);
   glRotatef(-90,1.0f, 0.0f, 0.0f);
   glRotatef(R.a,R.x,R.y,R.z);

   // Draw a solid cylinder
   GLUquadricObj* quadratic = gluNewQuadric();
   gluQuadricNormals(quadratic, GLU_SMOOTH);
   gluQuadricTexture(quadratic,GLU_TRUE);
   gluQuadricOrientation(quadratic, GLU_OUTSIDE); // Set the orientation to outside

   // Draw a cylinder
   glColor3f(0.0, 0.6, 1.0); // Set cylinder color

   gluCylinder(quadratic, 1.0, 1.0, 2.0, 8,8); // (base radius, top radius, height, slices, stacks)

   glColor3f(0,1,0); // Set cylinder color
   // Draw the top and bottom discs to close the cylinder
   glPushMatrix();
   glTranslatef(0.0, 0.0, 2.0); // Move to the other end
   gluDisk(quadratic, 0.0, 1.0, 8,8); // Inner and outer radius for top disc
   glPopMatrix();
   glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
   gluDisk(quadratic, 0.0, 1.0, 8,8); // Inner and outer radius for bottom disc
   gluDeleteQuadric(quadratic);
   glPopMatrix();
}

void beveled_cylinder(scale S, rotate R)
{
   float base_radius = 0.8;
   float top_radius = 0.5;
   float height = 11;
   int slices = 80;
   int stacks = 80;
   glPushMatrix();

   glScaled(S.x,S.y,S.z);
   glRotatef(-90,1.0f, 0.0f, 0.0f);
   glRotatef(R.a,R.x,R.y,R.z);

   // Draw a solid cylinder
   GLUquadricObj* quadratic = gluNewQuadric();
   gluQuadricNormals(quadratic, GLU_SMOOTH);
   gluQuadricTexture(quadratic,GLU_TRUE);
   gluQuadricOrientation(quadratic, GLU_OUTSIDE); // Set the orientation to outside

   // Draw a cylinder
   glColor3f(0.0, 0.6, 1.0); // Set cylinder color

   gluCylinder(quadratic, base_radius, top_radius, height, slices, stacks); // (base radius, top radius, height, slices, stacks)

   glColor3f(0,1,0); // Set cylinder color
   // Draw the top and bottom discs to close the cylinder
   glPushMatrix();
   gluDisk(quadratic, 0.0, base_radius, slices,stacks); // Inner and outer radius for top disc
   glTranslatef(0.0, 0.0, 10); // Move to the other end
   glPopMatrix();
   glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
   gluDisk(quadratic, 0.0, top_radius,slices, stacks); // Inner and outer radius for bottom disc
   gluDeleteQuadric(quadratic);
   glPopMatrix();
}

// The body of the main tomb
void beveled_cube(scale S, translate T)
{
   //  Vertex index list
   const int N=48;
   const unsigned char index[] =
   {
      0,8,9,1,
      1,9,10,2,
      2,10,11,3,
      3,11,12,4,
      4,12,13,5,
      5,13,14,6,
      6,14,15,7,
      7,15,8,0,
      0,1,2,3,4,5,6,7,
      8,9,10,11,12,13,14,15
   };
   //  Vertex coordinates
   const float xyz[] =
   {
      -0.6,1,-1,
      0.6,1,-1,
      1,1,-0.6,
      1,1,0.6,
      0.6,1,1,
      -0.6,1,1,
      -1,1,0.6,
      -1,1,-0.6,
      -0.6,0,-1,
      0.6,0,-1,
      1,0,-0.6,
      1,0,0.6,
      0.6,0,1,
      -0.6,0,1,
      -1,0,0.6,
      -1,0,-0.6
   };

   //  Define vertexes
   glVertexPointer(3,GL_FLOAT,0,xyz);
   glEnableClientState(GL_VERTEX_ARRAY);
   //  Draw the tomb
   glPushMatrix();
   glScalef(S.x,S.y,S.z);
   glTranslatef(T.x,T.y,T.z);

   glColor3f(0.4, 0.1, 0.56); // Set color


   glDrawElements(GL_POLYGON,N,GL_UNSIGNED_BYTE,index);
   glPopMatrix();
   //  Disable vertex array
   glDisableClientState(GL_VERTEX_ARRAY);
}

// Gates of the Taj
void gate(scale S, rotate R, translate T)
{
   glColor3f(0.69,0.23,0.45);
   glPushMatrix();
   glScaled(S.x,S.y,S.z); 
   glRotatef(R.a,R.x,R.y,R.z);
   glTranslatef(T.x,T.y,T.z);
   cube();
   glPopMatrix();
} 

void main_dome(scale S)
{
   float height = 1.4;
   float radius = 1.5;
   float sphere_rad = 1.65;
   glPushMatrix();

   glScaled(S.x,S.y,S.z);
   glRotatef(-90,1.0f, 0.0f, 0.0f);
   // Draw a solid cylinder
   GLUquadricObj* quadratic = gluNewQuadric();
   gluQuadricNormals(quadratic, GLU_SMOOTH);
   gluQuadricTexture(quadratic,GLU_TRUE);
   gluQuadricOrientation(quadratic, GLU_OUTSIDE); // Set the orientation to outside

   glColor3f(0.0, 0.6, 1.0); // Set cylinder color
   gluCylinder(quadratic, radius,radius, height, 80,80); // (base radius, top radius, height, slices, stacks)

   glColor3f(0,1,0); // Set cylinder color
   // Draw the top and bottom discs to close the cylinder
   glPushMatrix();
   gluDisk(quadratic, 0.0, radius, 80,80); // Inner and outer radius for top disc
   glPopMatrix();

   glTranslatef(0.0, 0.0, height+0.5); // Move to the other end

   gluSphere(quadratic,sphere_rad,80,10);

   glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
   gluDisk(quadratic, 0.0, radius, 80,80); // Inner and outer radius for bottom disc

   gluDeleteQuadric(quadratic);
   glPopMatrix();
} 
