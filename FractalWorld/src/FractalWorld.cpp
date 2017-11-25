#include <GL/glut.h>
#include <iostream>
#include "DiamondSquare.hpp"
#include "Camera.hpp"
using namespace std;

//Hello -Paul
//Sup -Michael

// Global Variables
GLint winWidth = 800, winHeight = 800;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Fractal World - Paul Hohbaum and Michael Solski");

	//glewInit(); // for using GSLS

	/*
	init();
	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	*/
	glutMainLoop();
	return 0;

}
