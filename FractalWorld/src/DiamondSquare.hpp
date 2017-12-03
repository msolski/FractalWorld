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

int const S = 65;

//Prototype functions

void PrintArray(int[S][S]);
void SquareStep(int Terrain[S][S],int x, int y, int step_size, int r);
void DiamondStep(int Terrain[S][S], int x, int y, int step_size, int r);
void DiamondSquare(int Terrain[S][S]);



#endif /* DIAMONDSQUARE_HPP_ */
