#include "matrix.hpp"
using namespace std;

int menu() {
    int option;
    cout << "*********************************************************" << endl;
    cout << "*                                                       *" << endl;
    cout << "*                 Welcome to the menu!                  *" << endl;
    cout << "*                                                       *" << endl;
    cout << "*********************************************************" << endl;
    cout << "*                                                       *" << endl;
    cout << "*                1. Generate new matrix                 *" << endl;
    cout << "*                2. Quit                                *" << endl;
    cout << "*                                                       *" << endl;
    cout << "*********************************************************" << endl;
    cout << endl <<  "\t~ Select your option: ";
    cin >> option;

    return option;
}

int main() {
    unordered_map<long long unsigned int, Data**> memory;
    int initial_i, initial_j, final_i, final_j, i, j;
    string docName = "matrix.txt";
    Data** mainMatrix;
    Data** transposedMatrix;
    Data** multipliedMatrix;
    Data** memoryMatrix;
    long long unsigned int key;
    int option;

    do {
        option = menu();

        if (option == 1) {
            getCoordenates(&initial_i, &initial_j, &final_i, &final_j);
            key = generateKey(initial_i, initial_j, final_i, final_j);
                
            i = (final_i - initial_i + 1);
            j = (final_j - initial_j + 1);
            
            if(!verifyMemory(memory, key)) {
                cout << endl << endl << "\t\t~ This is this Matrix's key: " << key << endl << endl;

                cout << "\t\t\t\t~ This is the Main Matrix ~" << endl << endl;
                mainMatrix = fillMatrix(docName, initial_i, initial_j, final_i, final_j);
                printMatrix(mainMatrix, i, j);

                cout << endl << "\t\t\t~ This is the Transposed of the Main Matrix ~" << endl << endl;
                transposedMatrix = getTransposedMatrix(mainMatrix, i, j);
                printMatrix(transposedMatrix, j, i);

                cout << endl <<"\t\t~ This is the multiplication between the two matrices above ~" << endl << endl;
                multipliedMatrix = multiplyMatrices(mainMatrix, transposedMatrix, i, j);
                printMatrix(multipliedMatrix, i, i);

                memory.emplace(key, multipliedMatrix);
            } else {
                cout << endl << endl << "\t\t- This matrix has already been processed, here is the result: " << endl << endl;
                memoryMatrix = memory[key];
                printMatrix(memoryMatrix, i, i);
            }
        }

        cout << endl << endl;
    } while(option != 2);
}