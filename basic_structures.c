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