#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include "DiamondSquare.hpp"
#include "Camera.hpp"
#include "Light.hpp"
using namespace std;

//Hello -Paul
//Sup -Michael

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
 */

// Global Variables
GLint winWidth = 800, winHeight = 800;
GLdouble time;

// World Objects
Camera myCamera;
Light myLight;

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	time = 0;
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	myCamera.setProjectionMatrix();

	//Draw world
	myLight.draw();

	// THESE SPHERES ARE FOR DEBUGGING CAMERA AND LIGHTING AND STUFF
	glutSolidSphere(1.0, 20, 20);
	glTranslatef(0, 0, 10);
	glutSolidSphere(0.9, 20, 20);
	glTranslatef(0, 0, 10);

	glFlush();
	glutSwapBuffers();
}

void cameraRotate(int key, int x, int y){
	switch(key){
	case GLUT_KEY_UP:
		myCamera.ref.set(myCamera.ref.x, myCamera.ref.y+0.5, myCamera.ref.z);
		break;
	case GLUT_KEY_DOWN:
		myCamera.ref.set(myCamera.ref.x, myCamera.ref.y-0.5, myCamera.ref.z);
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
	myLight.rotate(0.00001);
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

	//glewInit(); // for using GSLS

	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(cameraMove);
	glutSpecialFunc(cameraRotate);
	glutIdleFunc(nightDay);
	/*
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	*/
	glutMainLoop();
	return 0;

}
