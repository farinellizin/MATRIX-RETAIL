#ifndef MATRIX_HPP
#define MATRIX_HPP
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
typedef struct Data Data;
typedef struct Matrix Matrix;

struct Data {
    int value;
};

struct Matrix {
    Data **Mat;
};

void getCoordenates(int *initial_i, int *initial_j, int *final_i, int *final_j);
Data** fillMatrix(string docName, int initial_i, int initial_j, int final_i, int final_j);
Data** getTransposedMatrix(Data **mainMatrix, int lines, int columns);
Data** multiplyMatrices(Data **mainMatrix, Data **trasnposedMatrix, int size, int columnsTransposed);
void printMatrix(Data **mat, int columns, int lines);

#endif