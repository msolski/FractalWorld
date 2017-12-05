#include <stdio.h>
#include <math.h>
#include "Camera.hpp"
#include "Matrix.hpp"

bool DEBUG = false;

Camera::Camera(){
	eye.x = 150.0, eye.y = 20.0, eye.z = 175.0;
	ref.x = 113.0, ref.y = 5.0, ref.z = 112.0;
	viewup.x = 0.0,viewup.y = 1.0, viewup.z = 0.0;
	aspect = 1.0, viewAngle = 40.0, nearDist = 0.5, farDist = 500.0;
	setViewNorm();
}


void Camera::setDefaultCamera(void) { // make default camera
	eye.x = 5.0, eye.y = 5.0, eye.z = 10.0;
	ref.x = 0.0, ref.y = 0.0, ref.z = 0.0;
	viewup.x = 0.0,viewup.y = 1.0, viewup.z = 0.0;
	aspect = 1.0, viewAngle = 40.0, nearDist = 1.0, farDist = 40.0;
	setViewNorm();
}

void Camera::set(Point Eye, Point Look, Vector Up) {
	eye.set(Eye);
	ref.set(Look);
	viewup.set(Up);
	aspect = 1.0, viewAngle = 40.0, nearDist = 1.0, farDist = 40.0;
	setViewNorm();
}


void Camera::setViewNorm() {
	GLfloat x, y, z, sr;
	x = ref.x-eye.x;
	y = ref.y-eye.y;
	z = ref.z-eye.z;
	sr = sqrt(x*x + y*y + z*z);
	x = x/sr;
	y = y/sr;
	z = z/sr;
	viewNorm.set(x, y, z);
}

// This rotates the reference point around the camera, for the purposes
// of being able to look around, instead of focusing on a single object
void Camera::rotate(GLfloat angle){
	GLfloat x2, z2;
	x2 = cos(angle) * (ref.x-eye.x) - sin(angle) * (ref.z-eye.z) + eye.x;
	z2 = sin(angle) * (ref.z-eye.z) + cos(angle) * (ref.z-eye.z) + eye.z;

	ref.x = x2;
	ref.z = z2;
}

// This moves the camera towards the reference point
// and then moves the reference point so they are always the same distance apart
void Camera::translate(GLfloat dist){
	Vector *v = new Vector(ref.x-eye.x, ref.y-eye.y, ref.z-eye.z);

	/*
	printf("e: %.1f, %.1f %.1f\n", eye.x, eye.y, eye.z);
	printf("r: %.1f, %.1f %.1f\n", ref.x, ref.y, ref.z);
	printf("v: %.1f, %.1f %.1f\n\n", v->x, v->y, v->z);
	 */

	eye.x += dist * v->x/5;
	eye.y += dist * v->y/5;
	eye.z += dist * v->z/5;

	ref.x += dist * v->x/5;
	ref.y += dist * v->y/5;
	ref.z += dist * v->z/5;

	delete v;
}

void Camera::turnAround(){
	Vector *v = new Vector(-(ref.x-eye.x), -(ref.y-eye.y), -(ref.z-eye.z));

	ref.x += 2 * v->x;
	ref.y += 2 * v->y;
	ref.z += 2 * v->z;
}

void Camera::setProjectionMatrix() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, aspect, nearDist, farDist);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, ref.x, ref.y, ref.z, viewup.x,viewup.y,viewup.z);
}



