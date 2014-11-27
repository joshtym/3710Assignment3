#include "GLDonut.h"

//********************************************************************
// Default Constructor
// Post-Condition -- Initializes the origin values of the Pentadra to
//                   be what they currently are. 0, 0, 0.
//********************************************************************
GLDonut::GLDonut()
{
	// Initial origin values to 0
	xOriginValue = 0;
	yOriginValue = 0;
	zOriginValue = 0;	
}

//********************************************************************
// Destructor 
// Post-Condition -- Plays no purpose in this assignment
//********************************************************************
GLDonut::~GLDonut()
{
}

//********************************************************************
// Origin Value Assigner
// Post-Condition -- Defines the origin values of the Pentadra Pair 
//					 that we are drawing. In the initial coordinates
//					 given, the origin is 0, 0, 0. We use this new
//					 origin value to draw the same PentadraPair, and
//					 then translate it to where we want it in the world
//********************************************************************
void GLDonut::assignOriginValues(double xAlteration, double yAlteration, double zAlteration)
{
	xOriginValue = xAlteration;
	yOriginValue = yAlteration;
	zOriginValue = zAlteration;
}

//********************************************************************
// Draw and Rotate Public Function
// Post-Condition -- Uses the RotatePoints and drawPentadraPair
//					 to rotate and draw the Pentadra accordingly
//********************************************************************
void GLDonut::drawAndRotate(double theta, GLfloat xAxis, GLfloat yAxis, GLfloat zAxis)
{
	glPushMatrix();
		rotatePoints(theta, xAxis, yAxis, zAxis);
		drawPentadraPair();
	glPopMatrix();
}

//********************************************************************
// PentadraPair Drawer
// Post-Condition -- Using a small algorithm, this function iterates
//					 through all the points and draws them
//********************************************************************
void GLDonut::drawPentadraPair()
{
	// Draw the shape at the appropiate position
	glTranslatef(xOriginValue, yOriginValue, zOriginValue);
	
	glutSolidTorus (0.275, 0.85, 8, 15);
}

//********************************************************************
// Object rotater
// Post-Condition -- Dependant on the theta, this function moves the
//					 to the true world origin, rotates about the appropiate
//					 axis, and then moves the object back to its original
//					 location
//********************************************************************
void GLDonut::rotatePoints(double theta, GLfloat xAxis, GLfloat yAxis, GLfloat zAxis)
{
	// Translate to origin and rotate about axis, then translate back
	glTranslatef(xOriginValue, yOriginValue, zOriginValue);
	glRotatef(theta, xAxis, yAxis, zAxis);
	glTranslatef(xOriginValue * -1, yOriginValue * -1, zOriginValue * -1);
}
