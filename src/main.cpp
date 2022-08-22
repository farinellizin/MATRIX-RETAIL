#include "matrix.hpp"
using namespace std;

int main() {
    int initial_i, initial_j, final_i, final_j;
    getCoordenates(&initial_i, &initial_j, &final_i, &final_j);
    int i = (final_i - initial_i + 1), j = (final_j - initial_j + 1);
    string docName = "matrix.txt";

    Data** mainMatrix = fillMatrix(docName, initial_i, initial_j, final_i, final_j);
    // printMatrix(mainMatrix, i, j);
    // cout << "Main Matrix complete";
    cout << endl << endl;
    
    Data** transposedMatrix = getTransposedMatrix(mainMatrix, i, j);
    // printMatrix(transposedMatrix, j, i);
    // cout << "Transposed Matrix complete";
    cout << endl << endl;

    Data** multipliedMatrix = multiplyMatrices(mainMatrix, transposedMatrix, i, j);
    cout << endl << endl << endl;
    printMatrix(multipliedMatrix, i, i);
    // cout << "Multiplication between matrices complete";
    cout << endl << endl;
}