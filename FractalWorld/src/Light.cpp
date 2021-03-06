#include "Light.hpp"
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

Light::Light() {
	aI = 0.6;
	dI = 0.9;
	sI = 0.8;
	On = true;
	Day = true;

	pos[0] = 160.0;
	pos[1] = 0.0;
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
	GLfloat amb[4];

	if(Day){
		glClearColor(0.53 * pos[1]/200, 0.81 * pos[1]/200, 0.98 * pos[1]/200, 1.0);

		amb[0] = ambDay[0] * pos[1]/100;
		amb[1] = ambDay[1] * pos[1]/100;
		amb[2] = ambDay[2] * pos[1]/100;

		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffDay);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specDay);

		glDisable(GL_LIGHTING);
		glColor3f(1.0,1.0,0.5);
		glTranslatef(pos[0],pos[1],pos[2]);
		glutSolidSphere(3, 20, 20);
		glTranslatef(-pos[0],-pos[1],-pos[2]);
		glEnable(GL_LIGHTING);
	} else {
		glClearColor(0.05 * pos[1]/200, 0.05 * pos[1]/200, 0.1 * pos[1]/200, 1.0);

		amb[0] = ambNight[0] * pos[1]/100;
		amb[1] = ambNight[1] * pos[1]/100;
		amb[2] = ambNight[2] * pos[1]/100;

		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffNight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specNight);

		glDisable(GL_LIGHTING);
		glColor3f(0.7,0.7,0.7);
		glTranslatef(pos[0],pos[1],pos[2]);
		glutSolidSphere(3, 20, 20);
		glTranslatef(-pos[0],-pos[1],-pos[2]);
		glEnable(GL_LIGHTING);
	}

}

void Light::rotate(GLfloat angle){
	GLfloat y2, x2;
	x2 = pos[0]*cos(angle) - pos[1]*sin(angle);
	y2 = pos[1]*cos(angle) + pos[0]*sin(angle);

	pos[0] = x2;
	pos[1] = y2;

	if(pos[0] < -159.99){
		resetPos();
		if(Day)
			Day = false;
		else
			Day = true;
	}
}

void Light::resetPos(){
	pos[0] = 160;
	pos[1] = 0;
}
