#ifndef LIGHT_HPP_
#define LIGHT_HPP_
#include <GL/glut.h>
#include "Point.hpp"

class Light {
	public:
		GLfloat pos[3];
		GLfloat aI, dI, sI;
		GLboolean On;
		GLboolean Day;

		GLfloat colourDay[3];
		GLfloat ambDay[4];
		GLfloat diffDay[4];
		GLfloat specDay[4];

		GLfloat colourNight[3];
		GLfloat ambNight[4];
		GLfloat diffNight[4];
		GLfloat specNight[4];

		Light();
		void draw();

};

#endif /* LIGHT_HPP_ */
