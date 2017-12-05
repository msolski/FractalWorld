#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include "DiamondSquare.hpp"
#include "Camera.hpp"
#include "Light.hpp"
using namespace std;

/* ===========================
 * 			CONTROLS
 * ===========================
 * Up - make the camera look upwards
 * Down - make the camera look downwards
 * Right - rotate the camera to the right
 * Left - rotate the camera to the left
 * Space - Move the camera forwards
 * 'V' - Move the camera backwards
 * 'B' - Turn the camera 180 degrees around
 * 'W' - Switch between wire frame or solid polygon view mode
 * 'S' - Switch to smooth shading
 * 'F' - Switch to flat shading
 */

// Global Variables
GLint winWidth = 800, winHeight = 800;
bool wireFrame;

// World Objects
Camera myCamera;
Light myLight;

//Array of Points
Point *Points = (Point *)malloc(S*S*sizeof(Point));

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
	wireFrame = false;
	glEnable(GL_COLOR_MATERIAL);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	myCamera.setProjectionMatrix();

	//Should(TM) draw the matrix
	if(!wireFrame)
		DrawPoints(Points);
	else
		DrawPointsWire(Points);

	//Draw world
	myLight.draw();

	glFlush();
	glutSwapBuffers();
}

void cameraRotate(int key, int x, int y){
	switch(key){
	case GLUT_KEY_UP:
		myCamera.ref.set(myCamera.ref.x, myCamera.ref.y+1.5, myCamera.ref.z);
		break;
	case GLUT_KEY_DOWN:
		myCamera.ref.set(myCamera.ref.x, myCamera.ref.y-1.5, myCamera.ref.z);
		break;
	case GLUT_KEY_LEFT:
		myCamera.rotate(-0.05);
		break;
	case GLUT_KEY_RIGHT:
		myCamera.rotate(0.05);
		break;
	}

	glutPostRedisplay();
}

void nightDay(){
	myLight.rotate(0.0001);
	glutPostRedisplay();
}

void cameraMove(unsigned char key, int x, int y){
	switch(key){
	case ' ':
		myCamera.translate(0.5);
		break;
	case 'v':
	case 'V':
		myCamera.translate(-0.5);
		break;
	case 'b':
	case 'B':
		myCamera.turnAround();
		break;
	case 'w':
	case 'W':
		if(wireFrame) wireFrame = false;
		else wireFrame = true;
		break;
	case 's':
	case 'S':
		glShadeModel(GL_SMOOTH);
		break;
	case 'f':
	case 'F':
		glShadeModel(GL_FLAT);
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	setbuf(stdout, NULL);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Fractal World - Paul Hohbaum and Michael Solski");

	//Creates a Terrain Matrix of size S (in DiamondSquare.hpp)
	//Terrain Array
	int *Terrain = (int *)malloc(S*S*sizeof(int));

	ClearArray(Terrain);
	DiamondSquare(Terrain);

	//Creates a Matrix of points from the Terrain Matrix
	MatrixOfPoints(Points,Terrain);

	init();
	DrawPoints(Points);
	glutDisplayFunc(display);
	glutKeyboardFunc(cameraMove);
	glutSpecialFunc(cameraRotate);
	glutIdleFunc(nightDay);
	glutMainLoop();
	return 0;

}
