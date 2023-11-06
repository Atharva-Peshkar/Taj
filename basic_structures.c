#include "CSCIx229.h"

// Base of the Taj Mahal
float base(scale S, rotate R, translate T)
{
   glColor3f(1, 0, 0);
   glPushMatrix();
   glScaled(S.x,S.y,S.z); 
   glRotatef(R.a,R.x,R.y,R.z);
   glTranslatef(T.x,T.y,T.z);
   glutSolidCube(1);
   glPopMatrix();

   glColor3f(1, 0, 0);
   glPushMatrix();
   glScaled(S.x/3,S.y,S.z/3);
   glTranslatef(T.x,T.y,T.z+1.2);
   glutSolidCube(1);
   glPopMatrix();
} 

float octagonal_prism(scale S, rotate R)
{
   glPushMatrix();
   // Draw a solid cylinder
   GLUquadricObj* quadratic = gluNewQuadric();
   gluQuadricNormals(quadratic, GLU_SMOOTH);
   gluQuadricOrientation(quadratic, GLU_OUTSIDE); // Set the orientation to outside

   glScaled(S.x,S.y,S.z);
   glRotatef(-90,1.0f, 0.0f, 0.0f);
   glRotatef(R.a,R.x,R.y,R.z);
   // glTranslatef(T.x,-T.z,T.y);
   // Draw a cylinder
   glColor3f(0.0, 0.6, 1.0); // Set cylinder color

   gluCylinder(quadratic, 1.0, 1.0, 2.0, 8,8); // (base radius, top radius, height, slices, stacks)

   glColor3f(0,1,0); // Set cylinder color
   // Draw the top and bottom discs to close the cylinder
   gluQuadricOrientation(quadratic, GLU_INSIDE); // Set the orientation to inside
   gluDisk(quadratic, 0.0, 1.0, 8,8); // Inner and outer radius for top disc
   glTranslatef(0.0, 0.0, 2.0); // Move to the other end
   gluDisk(quadratic, 0.0, 1.0, 8,8); // Inner and outer radius for bottom disc
   gluDeleteQuadric(quadratic);
   glPopMatrix();
}

float beveled_cylinder(scale S, rotate R)
{
   glPushMatrix();
   // Draw a solid cylinder
   GLUquadricObj* quadratic = gluNewQuadric();
   gluQuadricNormals(quadratic, GLU_SMOOTH);
   gluQuadricOrientation(quadratic, GLU_OUTSIDE); // Set the orientation to outside

   glScaled(S.x,S.y,S.z);
   glRotatef(-90,1.0f, 0.0f, 0.0f);
   glRotatef(R.a,R.x,R.y,R.z);
   // glTranslatef(T.x,-T.z,T.y);
   // Draw a cylinder
   glColor3f(0.0, 0.6, 1.0); // Set cylinder color

   gluCylinder(quadratic, 0.7, 0.4, 10, 80,80); // (base radius, top radius, height, slices, stacks)

   glColor3f(0,1,0); // Set cylinder color
   // Draw the top and bottom discs to close the cylinder
   gluQuadricOrientation(quadratic, GLU_INSIDE); // Set the orientation to inside
   gluDisk(quadratic, 0.0, 0.7, 80,80); // Inner and outer radius for top disc
   glTranslatef(0.0, 0.0, 10); // Move to the other end
   gluDisk(quadratic, 0.0, 0.4, 80,80); // Inner and outer radius for bottom disc
   gluDeleteQuadric(quadratic);
   glPopMatrix();
}

float disk(scale S, rotate R)
{
     glPushMatrix();
   // Draw a solid cylinder
   GLUquadricObj* quadratic = gluNewQuadric();
   gluQuadricNormals(quadratic, GLU_SMOOTH);
   gluQuadricOrientation(quadratic, GLU_OUTSIDE); // Set the orientation to outside

   glScaled(S.x,S.y,S.z);
   glRotatef(-90,1.0f, 0.0f, 0.0f);
   glRotatef(R.a,R.x,R.y,R.z);
   // glTranslatef(T.x,-T.z,T.y);
   // Draw a cylinder
   glColor3f(0.0, 0.6, 1.0); // Set cylinder color

   gluCylinder(quadratic, 0.6, 0.6, 0.2, 80,80); // (base radius, top radius, height, slices, stacks)

   glColor3f(0,1,0); // Set cylinder color
   // Draw the top and bottom discs to close the cylinder
   gluQuadricOrientation(quadratic, GLU_INSIDE); // Set the orientation to inside
   gluDisk(quadratic, 0.0, 0.6, 80,80); // Inner and outer radius for top disc
   glTranslatef(0.0, 0.0, 0.2); // Move to the other end
   gluDisk(quadratic, 0.0, 0.6, 80,80); // Inner and outer radius for bottom disc
   gluDeleteQuadric(quadratic);
   glPopMatrix();
}

// The body of the main tomb
float beveled_cube(scale S, translate T)
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
float gate(scale S, rotate R, translate T)
{
   glColor3f(0.69,0.23,0.45);
   glPushMatrix();
   glScaled(S.x,S.y,S.z); 
   glRotatef(R.a,R.x,R.y,R.z);
   glTranslatef(T.x,T.y,T.z);
   glutSolidCube(1);
   glPopMatrix();
} 

