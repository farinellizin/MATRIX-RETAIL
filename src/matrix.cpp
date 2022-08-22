#include "matrix.hpp"

void getCoordenates(int *initial_i, int *initial_j, int *final_i, int *final_j) {
    cout << "\t- Please inform the initial I coordenate: ";
    cin >> *initial_i;

    cout << "\t- Please inform the initial J coordenate: ";
    cin >> *initial_j;

    cout << "\t- Please inform the final I coordenate: ";
    cin >> *final_i;

    cout << "\t- Please inform the final J coordenate: ";
    cin >> *final_j;
}

Data** fillMatrix(string docName, int initial_i, int initial_j, int final_i, int final_j) {
    Data** mainMatrix = 0;
    mainMatrix = new Data*[final_i - initial_i + 1];
    
    int cont = 0, num_elements = (final_i - initial_i + 1) * (final_j - initial_j + 1);
    int aux[num_elements];
    int j_coord = 0;
    string line;
    ifstream myfile;
    myfile.open(docName);
    
    int a = 0;

    if (myfile.is_open()) {
        for (int i = 0; i < initial_i - 1; i++) {
            getline(myfile, line);
        }

        while(!myfile.eof()) {
            while(getline(myfile, line, ' ') && cont < num_elements) {
                j_coord++;

                if (j_coord >= initial_j && j_coord <= final_j) {
                    aux[a] = stoi(line);
                    a++;
                    cont++;
                }

                if (j_coord == final_j) {
                    j_coord = 0;
                }       
            }
        }
    }

    a = 0;

    for (int i = 0; i < (final_i - initial_i + 1); i++) {
        mainMatrix[i] = new Data[(final_j - initial_j + 1)];
        for (int j = 0; j < (final_j - initial_j + 1); j++) {
            mainMatrix[i][j].value = aux[a];
            a++;
        }
    }

    return mainMatrix;
}

Data** getTransposedMatrix(Data **mainMatrix, int lines, int columns) {
    Data** transposedMatrix = 0;
    transposedMatrix = new Data*[columns];

    for (int i = 0; i < columns; i++) {
        transposedMatrix[i] = new Data[lines];
        for (int j = 0; j < lines; j++) {
            transposedMatrix[i][j].value = mainMatrix[j][i].value;
        }
    }

    return transposedMatrix;
}

Data** multiplyMatrices(Data **mainMatrix, Data **transposedMatrix, int size, int columnsTransposed) {
    Data** multipliedMatrix = 0;
    multipliedMatrix = new Data*[size];
    int sum;

    // for (int i = 0; i < 20; i++) {
    //     for (int j = 0; j < 1; j++) {
    //         cout << transposedMatrix[i][j].value << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < size; i++) {
        multipliedMatrix[i] = new Data[size];
        for (int j = 0; j < size; j++) {
            sum = 0;
            for (int k = 0; k < columnsTransposed; k++) {
                sum += (mainMatrix[i][k].value * transposedMatrix[k][j].value);
                // cout << mainMatrix[i][k].value << " * " << transposedMatrix[k][j].value << "\tcont: " << sum << "\t\t\t";
            }
 
            multipliedMatrix[i][j].value = sum;
            // cout <<  "i: " << i << "j: " << j << endl;
        }
    }

    cout << "size: " << size << endl;
    cout << "columnsTransposed: " << columnsTransposed << endl;

    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 1; j++) {
            cout << "result: " << multipliedMatrix[i][j].value << " ";
        }
        cout << endl;
    }
    

    return multipliedMatrix;
}

 void printMatrix(Data **mat, int lines, int columns) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            cout << mat[i][j].value << " ";
        }
        cout << endl;
    }
 }