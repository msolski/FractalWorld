/*
 * DiamondSquare.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: Paul_
 */

#include "DiamondSquare.hpp"

int Terrain[S][S];
int modulo = 50;
int randomneg = -25;
int step_size = S-1;

void PrintArray(int[S][S]){
	int i,j;
	for (i = 0; i < S; i++){
		for(j = 0; j < S; j++){
			printf("| %3d ",Terrain[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//Passed the midpoint of a diamond
void SquareStep(int Terrain[S][S],int x, int y, int step_size, int r){

	int top = Terrain[x][y-S];
	int left = Terrain[x][y-1];
	int right = Terrain[x][y+1];
	int bottom = Terrain[x][y+S];

	/*
	printf("\n");
	printf("   %d\n",top);
	printf("%d     %d\n",left,right);
	printf("   %d  \n",bottom);
	 */

	if (x==0){
		int average = (left+right+bottom)/3;
		Terrain[x][y] = average + r;
		//printf("%d\n",r);

	} else if (y==0){
		int average = (top+right+bottom)/3;
		Terrain[x][y] = average + r;
		//printf("%d\n",r);

	} else if (y==S){
		int average = (top+left+bottom)/3;
		Terrain[x][y] = average + r;
		//printf("%d\n",r);

	} else if (x==S){
		int average = (top+left+right)/3;
		Terrain[x][y] = average + r;
		//printf("%d\n",r);
	} else {
		int average = (top+left+right+bottom)/4;
		Terrain[x][y] = average + r;
		//printf("%d\n",r);
	}


}

//Passed the top left of a square
void DiamondStep(int Terrain[S][S],int x, int y, int step_size, int r){

	int topleft = Terrain[x][y];
	int topright = Terrain[x+step_size][y];
	int bottomleft = Terrain[x][y+step_size];
	int bottomright = Terrain[x+step_size][y+step_size];


	int average = (topleft+topright+bottomright+bottomleft)/4;
	Terrain[x+step_size/2][y+step_size/2] = average + r;
}

void DiamondSquare(int Terrain[S][S]){


	int a,b,c,d,r;


	// Seeding section, seeds  the corner values with posotive and negative numbers
	a = rand() % modulo + randomneg;
	b = rand() % modulo + randomneg;
	c = rand() % modulo + randomneg;
	d = rand() % modulo + randomneg;

	//Sets the seed values to the terrain matrix
	Terrain[0][0] = a;		//Top left
	Terrain[0][S-1] = b;	//Top Right
	Terrain[S-1][0] = c;	//Bottom Left
	Terrain[S-1][S-1] = d;	//Bottom Right

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
				//printf("\n");
				//printf("x = %d, y = %d\n",x,y);
				//PrintArray(Terrain);

				//top
				int x1 = x - step_size/2;
				int y1 = y;
				int r1 = rand() % modulo + randomneg;
				//printf("/////////////////////////////////////////////////\n");
				//printf("%d %d\n", x1,y1);
				SquareStep(Terrain,x1,y1,step_size,r1);
				//PrintArray(Terrain);

				//left
				int x2 = x;
				int y2 = y - step_size/2;
				int r2 = rand() % modulo + randomneg;
				//printf("/////////////////////////////////////////////////\n");
				//printf("%d %d\n", x2,y2);
				SquareStep(Terrain,x2,y2,step_size,r2);
				//PrintArray(Terrain);

				//right
				int x3 = x + step_size/2;
				int y3 = y;
				int r3 = rand() % modulo + randomneg;
				//printf("/////////////////////////////////////////////////\n");
				//printf("%d %d\n", x3,y3);
				SquareStep(Terrain,x3,y3,step_size,r3);
				//PrintArray(Terrain);

				//bottom
				int x4 = x;
				int y4 = y + step_size/2;
				int r4 = rand() % modulo + randomneg;
				//printf("/////////////////////////////////////////////////\n");
				//printf("%d %d\n", x4,y4);
				SquareStep(Terrain,x4,y4,step_size,r4);
				//PrintArray(Terrain);
				y += step_size;
			}
			x += step_size;


		}
		printf("\n");
		amtsquares *= 4;

		step_size /= 2;
		modulo /=2;
		randomneg /= 2;
	}
}
