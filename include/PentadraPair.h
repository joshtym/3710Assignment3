#ifndef PENTADRAPAIR_H
#define PENTADRAPAIR_H

#include <GL/glut.h>

class PentadraPair
{
	public:
		// Constructor: Default
		PentadraPair();
		
		// Destructor
		~PentadraPair();
		
		// Assigns new origin values of the PentadraPair object
		void assignOriginValues(double, double, double);
		
		// Rotates and draws the object accordingly
		void drawAndRotate(double, GLfloat, GLfloat, GLfloat);
		
	private:
		// Helper private function that does the drawing of the PentadraPair
		void drawPentadraPair();
		
		// Helper private function that helps with rotating the points
		void rotatePoints(double, GLfloat, GLfloat, GLfloat);
		
		// Coordinates of the original PentadraPair from ass1. By translating these
		// when we make duplicates, we'll be able to spread them out amongst the
		// world
		double xValues[18] = {0, 0, 0.5, 0.75, 0.5, 0.25, 0, 0, 0.25, 0.5, 0, 0.25, 0.5, 0.75, 0.5, 0.5, 0, 0.75};
		double yValues[18] = {0, 0, 0, 0, 0.5, 0.25, 0, 0, 0.25, 0, 0, 0.25, 0.5, 0, 0, 0.5, 0, 0};
		double zValues[18] = {0, -1, -1, -0.75, -0.5, -1, -1, 0, -1, -1, -1, -1, -0.5, -0.75, -1, -0.5, 0, -0.75};
		
		// List of random colours: Red, Green, Blue, Yellow
		double coloursArray[12] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0};
		
		// Origin Value of Pentadra Pair. This defaults to 0.
		double xOriginValue;
		double yOriginValue;
		double zOriginValue;
};

#endif
