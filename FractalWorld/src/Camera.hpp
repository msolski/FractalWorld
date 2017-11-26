
#ifndef CCAMERA_H
#define CCAMERA_H

#include <GL/glut.h>
#include "Point.hpp"
#include "Vector.hpp"

class Camera {
 public:
	Point eye; 			//camera position
	Point ref; 			//look at point
	Vector viewup; 		//view up vector
	GLfloat aspect, nearDist, farDist, viewAngle, W, H;
	Vector viewNorm;   // ref-eye/|ref-eye|

	//Vector u, v, n; 		//view coordinate system

	Camera();
	void set(Point Eye, Point look, Vector up);
	void set(float ex, float ey, float ez, float lx, float ly, float lz, float upx, float upy, float upz);

	void setViewNorm();

	void printCamera(void);
	void setDefaultCamera();

	void rotate(GLfloat angle);
	void translate(GLfloat dist);
	void setViewVolume(float viewAngle, float aspect, float Near, float Far);
	void setAspect(float aspect);
	void turnAround();

	void setProjectionMatrix();

};
#endif


