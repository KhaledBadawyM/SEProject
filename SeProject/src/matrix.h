/*
 * matrix.h
 *
 *  Created on: Oct 23, 2017
 *      Author: m_eltobgy
 */

#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_
#ifdef _WIN32
#include <string.h>
#else
#include <strings.h>
#endif
#include <iostream>
#include <stdio.h>
#include <cstring>
//#include "conio.h"
#include <bits/stdc++.h>
#include <cstdio>
#include <cmath>
using namespace std;
class matrix {
	int rows, columns;
	float **matr; //to use it in copying matrix
public:
	matrix();
	//void copy_matrix (matrix &m);
	virtual ~matrix();
	int Getrows(string s);
	int Getcolumns(string s);
	float** create_matrix(int rows, int columns);
	void destroy_matrix(float** matrix, int rows);
	float** fill_matrix(string s, float** A, int rows, int columns);
	float** createEmptyMatrix(int rows, int columns);
	float** sum_matrix(float** A, float** B, int rows, int columns);
	float** sub_matrix(float** A, float** B, int rows, int columns);
	float** multiply_matrix(float** A, float** B, int rows, int columns,int n1);
	float** division_By_One(float** A ,int rows ,int columns);                 //Farag
    float** partial_pivoting (float ** C ,int rows ,int i);
	float** divide_matrix (float **A , float** B , int rows ,int columns , int n1); //added by salah :D
	float** Transpose_matrix(float** A, int rows, int columns);
	float** zeros_matrix(int rows, int columns);
	float** ones_matrix(int rows, int columns);
	float** eye_matrix(int rows, int columns);                       // matrix.h
	float** rand_matrix(int rows, int columns);
	float** Exponential(float** A ,int rows ,int columns);
	float** Log_Base10(float** A ,int rows ,int columns,int &negative_flag);
	float** Log_Base2(float** A ,int rows ,int columns,int &negative_flag);
	float** Natural_Log(float** A ,int rows ,int columns,int &negative_flag);
	float** Tan_M(float** A ,int rows ,int columns);
    float** Cos_M(float** A ,int rows ,int columns);
    float** Sin_M(float** A ,int rows ,int columns);
    float** Power_the_matrix(float** A,float** B,int rows,int cloumns);
	float** SquareRoot(float** A,int m1,int n1, int & negative_flag);
	void print_matrix(float** A, int rows, int columns);
};

#endif /* SRC_MATRIX_H_ */
