#include "Light.hpp"
#include <stdio.h>
#include <GL/glut.h>

Light::Light() {
	aI = 0.3;
	dI = 0.9;
	sI = 0.8;
	On = true;
	Day = false;

	pos[0] = 0.0;
	pos[1] = 10.0;
	pos[2] = 0.0;

	colourDay[0] = 1.0;
	colourDay[1] = 0.95;
	colourDay[2] = 0.9;
	ambDay[0] = aI * colourDay[0];
	ambDay[1] = aI * colourDay[1];
	ambDay[2] = aI * colourDay[2];
	ambDay[3] = 1.0;
	diffDay[0] = dI * colourDay[0];
	diffDay[1] = dI * colourDay[1];
	diffDay[2] = dI * colourDay[2];
	diffDay[3] = 1.0;
	specDay[0] = sI * colourDay[0];
	specDay[1] = sI * colourDay[1];
	specDay[2] = sI * colourDay[2];
	specDay[3] = 1.0;

	colourNight[0] = 0.5;
	colourNight[1] = 0.55;
	colourNight[2] = 0.6;
	ambNight[0] = aI * colourNight[0];
	ambNight[1] = aI * colourNight[1];
	ambNight[2] = aI * colourNight[2];
	ambNight[3] = 1.0;
	diffNight[0] = dI * colourNight[0];
	diffNight[1] = dI * colourNight[1];
	diffNight[2] = dI * colourNight[2];
	diffNight[3] = 1.0;
	specNight[0] = sI * colourNight[0];
	specNight[1] = sI * colourNight[1];
	specNight[2] = sI * colourNight[2];
	specNight[3] = 1.0;
}

void Light::draw(){
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	if(Day){
		glClearColor(0.53, 0.81, 0.98, 1.0);

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambDay);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffDay);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specDay);

		glDisable(GL_LIGHTING);
		glColor3f(1.0,1.0,0.5);
		glTranslatef(pos[0],pos[1],pos[2]);
		glutSolidSphere(0.1, 10, 10);
		glTranslatef(-pos[0],-pos[1],-pos[2]);
		glEnable(GL_LIGHTING);
	} else {
		glClearColor(0.05, 0.05, 0.1, 1.0);

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambNight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffNight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specNight);

		glDisable(GL_LIGHTING);
		glColor3f(0.7,0.7,0.7);
		glTranslatef(pos[0],pos[1],pos[2]);
		glutSolidSphere(0.1, 10, 10);
		glTranslatef(-pos[0],-pos[1],-pos[2]);
		glEnable(GL_LIGHTING);
	}

}
