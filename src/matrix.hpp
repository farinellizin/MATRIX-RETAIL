#ifndef MATRIX_HPP
#define MATRIX_HPP
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <unordered_map>
typedef struct Data Data;
typedef struct Matrix Matrix;

struct Data {
    int value;
};

struct Matrix {
    Data **Mat;
};

void getCoordenates(int *initial_i, int *initial_j, int *final_i, int *final_j);
bool verifyMemory(unordered_map<long long unsigned int, Data**> memory, long long unsigned int key);
Data** fillMatrix(string docName, int initial_i, int initial_j, int final_i, int final_j);
Data** getTransposedMatrix(Data **mainMatrix, int lines, int columns);
Data** multiplyMatrices(Data **mainMatrix, Data **trasnposedMatrix, int size, int columnsTransposed);
long long unsigned int generateKey(int initial_i, int initial_j, int final_i, int final_j);
void printMatrix(Data **mat, int columns, int lines);

#endif