/*
 * DiamondSquare.hpp
 *
 *  Created on: Nov 23, 2017
 *      Author: Paul_
 */

#ifndef DIAMONDSQUARE_HPP_
#define DIAMONDSQUARE_HPP_

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Point.hpp"

//Must be of the form 2^(n) + 1
//Max is 65 :(
int const S = 5;

//Prototype functions

void PrintArray(int *Terrain);	//Prints a 2D array (for debugging)
void ClearArray(int *Terrain);	//Sets all points in the array to zero
void SquareStep(int *Terrain,int x, int y, int step_size, int r); 		//Used in Diamond Square
void DiamondStep(int *Terrain, int x, int y, int step_size, int r);	//Used in Diamond Square
void DiamondSquare(int *Terrain);	//The Diamond Square algorithm for Terrain Generation

//Takes an empty array of points and maps the Terrain values to them;
void MatrixOfPoints(Point *Points,int *Terrain);

//Takes an array of points and draws them to the screen (in theory)
void DrawPoints(Point *Points);


#endif /* DIAMONDSQUARE_HPP_ */
