#include <GL/glut.h>
#include <cmath>
#include "PentadraPair.h"

// Function Prototypes

// Handles initialization with OpenGL
void init();

// Display function that OpenGL calls
void display();

// Spinning animation
void action();

// Keyboard Input Handler
void keyboard(unsigned char key, int xPos, int yPos);

// Mouse Input Handler
void mouse(int button, int state, int xPos, int yPos);

// Function to handle resizing of the window
void reshape(int width, int height);

// Function to handle rotation when input is detected
void rotationHelperFunc();

// Function which changes which axis is being rotated about when
// key is pressed
void changeAxisRotation(double, double, double);

// Take in two vectors, compute their cross product, and return the vector of the cross product
double* computeCrossProduct (double[], double[]);

// Rotate a vector about an arbitray axis
void rotateAboutArbitraryAxis(double[], GLfloat, GLfloat, GLfloat, double);

// Deal with OpenGL's rendition of UP, DOWN, LEFT, RIGHT cursor keys
void processSpecialKeys(int, int, int);

// Global Variables
static GLfloat spin = 0.0;
static bool isRotating = true;
static double PI = 3.14159265358979;
static int screenWidth = 500;
static int screenHeight = 500;

// Axis details (which axis we are rotating about)
static GLfloat xAxisRotation = 1.0;
static GLfloat yAxisRotation = 0.0;
static GLfloat zAxisRotation = 0.0;

// Major vectors that we deal with in the assignment
static double VPN[3];
static double VUP[3];
static double VRP[3];

// Global object
static PentadraPair pentadra1;
static PentadraPair pentadra2;
static PentadraPair pentadra3;
static PentadraPair pentadra4;
static PentadraPair pentadra5;
static PentadraPair pentadra6;
static PentadraPair pentadra7;
static PentadraPair pentadra8;
static PentadraPair pentadra9;
static PentadraPair pentadra10;

int main(int argc, char **argv)
{
	/* Supplied -- Do not change! */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	
	init();
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(processSpecialKeys);
	glutIdleFunc(action);
	glutMainLoop();
	
	return 0;
}

// Function Definitions

//***************************************************************
// Function: init
// Purpose: Initialize the OpenGL window with the appropiate colour and
//          shade modelling
//***************************************************************
void init()
{
	// Clear the colour to black and set appropiate ShadeModeling
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	// Give the VRP, VPN, and VUP default values
	VRP[0] = 0;
	VRP[1] = 0;
	VRP[2] = 5;
	
	VPN[0] = 0;
	VPN[1] = 0;
	VPN[2] = -1;
	
	VUP[0] = 0;
	VUP[1] = 1;
	VUP[2] = 0;
	
	// Assign initial origin values to Pentadras
	pentadra1.assignOriginValues(cos(0), sin(0), -10);
	pentadra2.assignOriginValues(cos(PI/3), sin(PI/3), -7);
	pentadra3.assignOriginValues(cos(2*PI/3), sin(2*PI/3), -4);
	pentadra4.assignOriginValues(cos(PI), sin(PI), -1);
	pentadra5.assignOriginValues(cos(4*PI/3), sin(4*PI/3), 2);
	pentadra6.assignOriginValues(cos(5*PI/3), sin(5*PI/3), 5);
	pentadra7.assignOriginValues(cos(0), sin(0), 8);
	pentadra8.assignOriginValues(cos(PI/3), sin(PI/3), 11);
	pentadra9.assignOriginValues(cos(2*PI/3), sin(2*PI/3), 14);
	pentadra10.assignOriginValues(cos(PI), sin(PI), 17);
}

//***************************************************************
// Function: display
// Purpose: Handle all display. This includes drawing, rotation and 
//          handling of the OpenGL pipeline
//***************************************************************
void display()
{
	// Clear the colour buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glCullFace(GL_BACK);
	
	// Handle perspective of the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) screenWidth/(GLfloat) screenHeight,0.1, 25.0);
	
	// Deal with the appropiate 'camera' viewpoint
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(VRP[0], VRP[1], VRP[2], VRP[0] + VPN[0], VRP[1] + VPN[1], VRP[2] + VPN[2], VUP[0], VUP[1], VUP[2]);
	
	// Draw and rotate each item accordingly
	pentadra1.drawAndRotate(spin, xAxisRotation, yAxisRotation, zAxisRotation);
	pentadra2.drawAndRotate(spin, xAxisRotation, yAxisRotation, zAxisRotation);
	pentadra3.drawAndRotate(spin, xAxisRotation, yAxisRotation, zAxisRotation);
	pentadra4.drawAndRotate(spin, xAxisRotation, yAxisRotation, zAxisRotation);
	pentadra5.drawAndRotate(spin, xAxisRotation, yAxisRotation, zAxisRotation);
	pentadra6.drawAndRotate(spin, xAxisRotation, yAxisRotation, zAxisRotation);
	pentadra7.drawAndRotate(spin, xAxisRotation, yAxisRotation, zAxisRotation);
	pentadra8.drawAndRotate(spin, xAxisRotation, yAxisRotation, zAxisRotation);
	pentadra9.drawAndRotate(spin, xAxisRotation, yAxisRotation, zAxisRotation);
	pentadra10.drawAndRotate(spin, xAxisRotation, yAxisRotation, zAxisRotation);
	
	glutSwapBuffers();
	
	glFlush();
}

//***************************************************************
// Function: action
// Purpose: Updates angle for the rotation of the object
//***************************************************************
void action()
{
	if (isRotating)
	{
		spin = spin + 0.10;
	
		if (spin > 360.0)
			spin = spin - 360;
	}
	
	glutPostRedisplay();
}

//***************************************************************
// Function: keyboard
// Purpose: Handles all keyboard input. If input is the ESC key, close
//          the program. If input is either x, y, or z, use the helper
//          function to change which axis we are rotating about.
//          If the key is r, begin or stop rotation depending on
//          whether it is currently going
//***************************************************************
void keyboard(unsigned char key, int xPos, int yPos)
{
	switch(key)
	{
		// ESC Key
		case 27:
			glutDestroyWindow(1);
			break;
		// 'r' key
		case 82:
			rotationHelperFunc();
			break;
		// 'R' key
		case 114:
			rotationHelperFunc();
			break;
		// 'x' key
		case 88:
			changeAxisRotation(1.0, 0.0, 0.0);
			break;
		// 'X' key
		case 120:
			changeAxisRotation(1.0, 0.0, 0.0);
			break;
		// 'y' key
		case 89:
			changeAxisRotation(0.0, 1.0, 0.0);
			break;
		// 'Y' key
		case 121:
			changeAxisRotation(0.0, 1.0, 0.0);
			break;
		// 'z' key
		case 90:
			changeAxisRotation(0.0, 0.0, 1.0);
			break;
		// 'Z' key
		case 122:
			changeAxisRotation(0.0, 0.0, 1.0);
			break;
		// Space bar
		case 32:
			VRP[0] = VRP[0] + VPN[0];
			VRP[1] = VRP[1] + VPN[1];
			VRP[2] = VRP[2] + VPN[2];
			break;
		// 'B' key
		case 66:
			VRP[0] = VRP[0] - VPN[0];
			VRP[1] = VRP[1] - VPN[1];
			VRP[2] = VRP[2] - VPN[2];
			break;
		// 'b' key
		case 98:
			VRP[0] = VRP[0] - VPN[0];
			VRP[1] = VRP[1] - VPN[1];
			VRP[2] = VRP[2] - VPN[2];
			break;
		// 'N' key
		case 78:
			rotateAboutArbitraryAxis(VUP, VPN[0], VPN[1], VPN[2], PI/20);
			break;
		// 'n' key
		case 110:
			rotateAboutArbitraryAxis(VUP, VPN[0], VPN[1], VPN[2], PI/20);
			break;
		// 'M' key
		case 77:
			rotateAboutArbitraryAxis(VUP, VPN[0], VPN[1], VPN[2], PI/20 * -1);
			break;
		// 'm' key
		case 109:
			rotateAboutArbitraryAxis(VUP, VPN[0], VPN[1], VPN[2], PI/20 * -1);
			break;
		default:
			break;
	}
			
}

//***************************************************************
// Function: processSpecialKeys
// Purpose: Handles all keyboard input of special keys not available
//			within the standard keyboard function. These are the cursor
//			keys. If the key is up or down, we want to rotate VPN/VUP
//			about the cross of VPN and VUP. If the key is left or
//			right, we want to rotate VPN about VUP
//***************************************************************
void processSpecialKeys(int key, int xx, int yy)
{
	double crossVupVpn[3];
	crossVupVpn[0] = computeCrossProduct(VUP, VPN)[0];
	crossVupVpn[1] = computeCrossProduct(VUP, VPN)[1];
	crossVupVpn[2] = computeCrossProduct(VUP, VPN)[2];
	
	switch (key)
	{
		case GLUT_KEY_LEFT:
			rotateAboutArbitraryAxis(VPN, VUP[0], VUP[1], VUP[2], PI/20);
			break;
		case GLUT_KEY_RIGHT:
			rotateAboutArbitraryAxis(VPN, VUP[0], VUP[1], VUP[2], PI/20 * -1);
			break;
			break;
		case GLUT_KEY_UP:
			rotateAboutArbitraryAxis(VUP, crossVupVpn[0], crossVupVpn[1], crossVupVpn[2], PI/20 * -1);
			rotateAboutArbitraryAxis(VPN, crossVupVpn[0], crossVupVpn[1], crossVupVpn[2], PI/20 * -1);
			break;
		case GLUT_KEY_DOWN:
			rotateAboutArbitraryAxis(VUP, crossVupVpn[0], crossVupVpn[1], crossVupVpn[2], PI/20);
			rotateAboutArbitraryAxis(VPN, crossVupVpn[0], crossVupVpn[1], crossVupVpn[2], PI/20);
			break;
		default:
			break;
	}
}

//***************************************************************
// Function: Mouse
// Purpose: Handles all mouse input. Currently, this program does
//          not have any mouse functionality
//***************************************************************
void mouse(int button, int state, int xPos, int yPos)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		default:
			break;
	}
}

//***************************************************************
// Function: reshape
// Purpose: Handles resizing of the OpenGL window
//***************************************************************
void reshape(int width, int height)
{
	/* Supplied -- Do not change! */
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* set the viewing area -- use perspective projection
	 * an object at the origin that is about 1 or 2 units wide should
	 * be nicely visible
	*/
	glFrustum(-1.0, 1.0, -1.0, 1.0, 0.5, 15.0);
	//gluPerspective(60.0, (GLfloat) width/(GLfloat) height,0.1, 25.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/* Viewing Transformation
	 * sets the eye to be at (1.5, 1.5, 1.5) looking at the origin etc.
	*/
	//gluLookAt(1.5, 1.5, 1.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(VRP[0], VRP[1], VRP[2], VRP[0] + VPN[0], VRP[1] + VPN[1], VRP[2] + VPN[2], VUP[0], VUP[1], VUP[2]);
	//gluLookAt(VRP[0] + VPN[0], VRP[1] + VPN[1], VRP[2] + VPN[2], VRP[0], VRP[1], VRP[2], VUP[0], VUP[1], VUP[2]);
	
	screenWidth = width;
	screenHeight = height;
}


//***************************************************************
// Function: Rotation Helper
// Purpose: Essentially checks if the object is currently rotating
//          when the 'r' key is pressed. If so, stop rotation and set
//          isRotating to false, else, start rotation and set it to true
//***************************************************************
void rotationHelperFunc()
{
	if (isRotating)
		isRotating = false;
	else
		isRotating = true;
}

//***************************************************************
// Function: Axis Rotation Changer
// Purpose: Changes the axis values to the values which are passed in
//***************************************************************
void changeAxisRotation(double xAxis, double yAxis, double zAxis)
{
	xAxisRotation = xAxis;
	yAxisRotation = yAxis;
	zAxisRotation = zAxis;
}

//***************************************************************
// Function: Cross Product Computer
// Purpose: Takes in two vectors and returns the cross product of them
//***************************************************************
double* computeCrossProduct (double vector1[3], double vector2[3])
{
	double crossProductVector[3];
	
	crossProductVector[0] = vector1[1]*vector2[2] - vector1[2]*vector2[1];
	crossProductVector[1] = (vector1[2]*vector2[0] - vector1[0]*vector2[2]) * -1;
	crossProductVector[2] = vector1[0]*vector2[1] - vector1[1]*vector2[0];
	
	return crossProductVector;
}

//***************************************************************
// Function: Arbitrary Axis Rotator
// Purpose: Rotates vector A about vector with x, y, z values of
//			uX, uY, uZ by theta. Provided by the professor
//***************************************************************
void rotateAboutArbitraryAxis(double* A, GLfloat uX, GLfloat uY, GLfloat uZ, double theta) 
{
	double ct, st, lv0, lv1, lv2;
	
	ct = cos(theta);
	st = sin(theta);
	
	lv0 = A[0];
	lv1 = A[1];
	lv2 = A[2];
	
	A[0] = lv0 * (uX*uX + ct * (1.0 - uX*uX)) + lv1 * (uX*uY * (1.0 - ct) - uZ * st) + lv2 * (uZ * uX * (1.0 - ct) + uY * st);
	A[1] = lv0 * (uX*uY * (1.0 - ct) + uZ*st) + lv1 * (uY*uY +  ct * (1.0 - uY*uY)) +lv2 * (uY*uZ * (1.0 - ct) - uX*st);
	A[2] = lv0 * (uZ*uX * (1.0 - ct) - uY*st) + lv1 * (uY*uZ * (1.0 - ct) + uX*st) + lv2 * (uZ*uZ +  ct * (1.0 - uZ*uZ));
}
