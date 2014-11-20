#include "PentadraPair.h"

//********************************************************************
// Default Constructor
// Post-Condition -- Initializes the origin values of the Pentadra to
//                   be what they currently are. 0, 0, 0.
//********************************************************************
PentadraPair::PentadraPair()
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
PentadraPair::~PentadraPair()
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
void PentadraPair::assignOriginValues(double xAlteration, double yAlteration, double zAlteration)
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
void PentadraPair::drawAndRotate(double theta, GLfloat xAxis, GLfloat yAxis, GLfloat zAxis)
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
void PentadraPair::drawPentadraPair()
{
	// Draw the shape at the appropiate position
	glTranslatef(xOriginValue, yOriginValue, zOriginValue);
	
	// Algorithm to iterate through all the points and draw all the points
	int iterateAmount = 0;
	int currentArrayNumber = 0;
	int otherArrayNumber = 1;
	
	for (int i = 0; i < 10; ++i)
	{
		// Faces 2, 4, 7, and 9 only have 3 points each whilst the others
		// have 4 (Note that this starts on Face 0)
		if (i == 2 || i == 4 || i == 5 || i == 7)
			iterateAmount = 3;
		else
			iterateAmount = 4;
			
		
		glBegin(GL_POLYGON);
			for (int j = 0; j < iterateAmount; j++)
			{
				glColor3f(coloursArray[3 * j], coloursArray[3 * j + 1], coloursArray[3 * j + 2]);
				
				// Note that because we only change the z values to draw the other half of the
				// PentadraPair, we can just re-iterate through the same 18 points and
				// just multiply the z coordinate by -1.
				if (currentArrayNumber >= 18)
				{
					glVertex3f(xValues[currentArrayNumber - otherArrayNumber], yValues[currentArrayNumber - otherArrayNumber], 
							  (zValues[currentArrayNumber - otherArrayNumber]) * -1);
							  
					otherArrayNumber = otherArrayNumber+2;
				}
				else
					glVertex3f(xValues[currentArrayNumber], yValues[currentArrayNumber], 
							   zValues[currentArrayNumber]);
					
				currentArrayNumber++;
			}
		glEnd();
	}
}

//********************************************************************
// Object rotater
// Post-Condition -- Dependant on the theta, this function moves the
//					 to the true world origin, rotates about the appropiate
//					 axis, and then moves the object back to its original
//					 location
//********************************************************************
void PentadraPair::rotatePoints(double theta, GLfloat xAxis, GLfloat yAxis, GLfloat zAxis)
{
	// Translate to origin and rotate about axis, then translate back
	glTranslatef(xOriginValue, yOriginValue, zOriginValue);
	glRotatef(theta, xAxis, yAxis, zAxis);
	glTranslatef(xOriginValue * -1, yOriginValue * -1, zOriginValue * -1);
}
