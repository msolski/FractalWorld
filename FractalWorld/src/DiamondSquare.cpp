/*
 * DiamondSquare.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: Paul_
 */

#include "DiamondSquare.hpp"


int *Terrain;
int modulo = rand()%1000;	//Bigger number, higher peaks and lower valleys
int randomneg = modulo/2;	//allows a range of [modulo/2, -modulo/2]
int ScaleHeight = modulo/10;//Scale of the Terrain, Higher value less height difference
int ScaleMapSize = 5;
int step_size = S-1;

void PrintArray(int *Terrain){
	int i,j;
	for (i = 0; i < S; i++){
		for(j = 0; j < S; j++){
			printf("| %3d ",Terrain[i*S+j]);
		}
		printf("\n");
	}
	printf("\n");
}

void ClearArray(int *Terrain){
	int i,j;
	for (i = 0; i < S; i++){
		for(j = 0; j < S; j++){
			Terrain[i*S+j] = 0;	//Sets the value to zero
		}
	}
}

//Passed the midpoint of a diamond
void SquareStep(int *Terrain,int x, int y, int step_size, int r){
	int top = Terrain[S*(x)+(y-S)];
	int left = Terrain[S*(x)+(y-1)];
	int right = Terrain[S*(x)+(y+1)];
	int bottom = Terrain[S*(x)+(y+S)];

	if (x==0){
		int average = (left+right+bottom)/3;
		Terrain[x*S + y] = average + r;

	} else if (y==0){
		int average = (top+right+bottom)/3;
		Terrain[x*S + y] = average + r;

	} else if (x==S-1){
		int average = (top+left+right)/3;
		Terrain[x*S + y] = average + r;

	} else if (y==S-1){
		int average = (top+left+bottom)/3;
		Terrain[x*S + y] = average + r;
	} else {
		int average = (top+left+right+bottom)/4;
		Terrain[x*S + y] = average + r;
	}


}

//Passed the top left of a square
void DiamondStep(int *Terrain,int x, int y, int step_size, int r){

	int topleft = Terrain[S*(x)+y];
	int topright = Terrain[S*(x+step_size)+y];
	int bottomleft = Terrain[S*(x)+(y+step_size)];
	int bottomright = Terrain[S*(x+step_size)+(y+step_size)];


	int average = (topleft+topright+bottomright+bottomleft)/4;
	Terrain[S*(x+step_size/2)+(y+step_size/2)] = average + r;
}

void DiamondSquare(int *Terrain){


	int a,b,c,d,r;
	srand(time(NULL));

	// Seeding section, seeds  the corner values with posotive and negative numbers
	a = rand() % modulo + randomneg;
	b = rand() % modulo + randomneg;
	c = rand() % modulo + randomneg;
	d = rand() % modulo + randomneg;


	//Sets the seed values to the terrain matrix
	Terrain[0] = a;		//Top left
	Terrain[0*S + S-1] = b;	//Top Right
	Terrain[(S-1)*S + 0] = c;	//Bottom Left
	Terrain[(S-1)*S+S-1] = d;	//Bottom Right



	int amtsquares = 1;		//Amount of squares

	//While Loop for iterating through the matrix
	while (step_size > 1){

		int i,j,x,y;			//Counters, Coordinates, Random number
		i=j=x=y=0;


		//Loop over Terrain, for every square in A perform the diamond step

		for (i=0; i < sqrt(amtsquares); i++){
			y = 0;
			for(j=0;j<sqrt(amtsquares);j++){
				r = rand() % modulo + randomneg;		//
				DiamondStep(Terrain,x,y,step_size,r);	//
				y+=step_size;
			}
			x+=step_size;
		}
										//Amt of diamonds increases by a multiple of 4 each time the above loop runs


		//Loop over Terrain, for every diamond, run the square step
		x = step_size/2;

		for (i=0; i<sqrt(amtsquares); i++){
			y = step_size/2;
			for (j=0; j<sqrt(amtsquares);j++) {

				//top
				int x1 = x - step_size/2;
				int y1 = y;
				int r1 = rand() % modulo + randomneg;
				SquareStep(Terrain,x1,y1,step_size,r1);

				//left
				int x2 = x;
				int y2 = y - step_size/2;
				int r2 = rand() % modulo + randomneg;
				SquareStep(Terrain,x2,y2,step_size,r2);

				//bottom
				int x3 = x + step_size/2;
				int y3 = y;
				int r3 = rand() % modulo + randomneg;
				SquareStep(Terrain,x3,y3,step_size,r3);

				//right
				int x4 = x;
				int y4 = y + step_size/2;
				int r4 = rand() % modulo + randomneg;
				SquareStep(Terrain,x4,y4,step_size,r4);
				y += step_size;
			}
			x += step_size;


		}
		amtsquares *= 4;

		step_size /= 2;
		modulo /=2;
		randomneg /= 2;
	}
}

//Populates an Array of Points using the array of Terrain
void MatrixOfPoints(Point *Points, int *Terrain){

	GLfloat tempfx,tempfy,tempfz;
	int tempx,tempy,tempz,i,j;

	for (i=0; i<S; i++){
		for(j=0;j<S;j++){

			tempx = i;				//Terrain integer x value
			tempy = j;				//Terrain integer y value
			tempz = Terrain[i*S+j];	//Terrain integer z value

			tempfx = (float)tempx*ScaleMapSize;	//Sets GLfloat x value
			tempfy = (float)tempy*ScaleMapSize;	//Sets GLfloat y value
			tempfz = (float)tempz/ScaleHeight;	//Sets GLfloat z value

			//Initializes the point at Points[x][y] to our values
			Points[S*i + j].set(tempfx,tempfz,tempfy);

		}
	}
}


void DrawPoints(Point *Points){
	int i,j;

	//Connects points to their next door neighbor
	for (i=0;i<S-1;i++){
		for (j=0;j<S-1;j++){
			Point p1 = Points[S*i + j];		//p1
			Point p2 = Points[S*i + j + 1];	//p1		p2
			Point p3 = Points[S*(i+1) + j];
			Point p4 = Points[S*(i+1) + j + 1];

			glBegin(GL_QUADS);
				//First Point
				pointColor(p1.y);
				glVertex3f(p1.x,p1.y,p1.z);

				//Second point
				pointColor(p2.y);
				glVertex3f(p2.x,p2.y,p2.z);

				//Fourth point
				pointColor(p4.y);
				glVertex3f(p4.x,p4.y,p4.z);

				//Third point
				pointColor(p3.y);
				glVertex3f(p3.x,p3.y,p3.z);
			glEnd();

		}
	}
}

void pointColor(GLfloat y){

	GLfloat r, g, b;

	r = y/15 + 0.2;
	g = y/18 + 0.2;
	b = y/25 + 0.25;

	glColor3f(r, g, b);

}

void DrawPointsWire(Point *Points){
	int i,j;

	//Connects points to their next door neighbor
	for (i=0;i<S-1;i++){
		for (j=0;j<S-1;j++){
			Point p1 = Points[S*i + j];		//p1
			Point p2 = Points[S*i + j + 1];	//p1		p2
			Point p3 = Points[S*(i+1) + j];
			Point p4 = Points[S*(i+1) + j + 1];

			glColor3f(0.8, 0.8, 0.8);
			glBegin(GL_LINE_LOOP);
			glVertex3f(p1.x,p1.y,p1.z);
			glVertex3f(p2.x,p2.y,p2.z);
			glVertex3f(p4.x,p4.y,p4.z);
			glVertex3f(p3.x,p3.y,p3.z);
			glEnd();

		}
	}
}
