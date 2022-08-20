#include "matrix.hpp"
using namespace std;

int main() {
    int initial_i = 18, initial_j = 15, final_i = 20, final_j = 20;

    // cout << "\t- Please inform the initial I coordenate: ";
    // cin >> initial_i;

    // cout << "\t- Please inform the initial J coordenate: ";
    // cin >> initial_j;

    // cout << "\t- Please inform the final I coordenate: ";
    // cin >> final_i;

    // cout << "\t- Please inform the final J coordenate: ";
    // cin >> final_j;

    ifstream myfile;
    myfile.open("matrix.txt");

    string line;

    int line_cont = (final_i - initial_i + 1), cont = 0;

    int matrix[final_i - initial_i + 1][final_j - initial_j + 1];
    cout << "[ " << final_i - initial_i + 1 << " ][ " << final_j - initial_j + 1 << " ]\n\n"; 

    int j_coord = 0;

    int I = 0, J = 0;

    if (myfile.is_open()) {
        for(int i = 0; i < initial_i - 1; i++) {
            getline(myfile, line);
        }

        while(!myfile.eof()) {
            while (getline(myfile, line, ' ')) {
                j_coord++;

                if (j_coord >= initial_j && j_coord <= final_j) {
                    matrix[I][J] = stoi(line);
                    cout << "[" << I << "][" << J + 1 << "] = " << matrix[I][J] << endl;
                    cout << endl << endl << "Line Cont = " << line_cont << " cont = " << cont << endl << endl;

                    J++;
                
                    if (J == (final_j - initial_j + 1)) {
                        J = 0;
                        I++;
                        cont++;
                    }

                    if(cont == line_cont) {
                        break;
                    }
                }

                if (j_coord == final_j) {
                    j_coord = 0;
                }
            }
        }
    }

    for (int i = 0; i < (final_i - initial_i + 1); i++) {
        for (int j = 0; j < (final_j - initial_j + 1); j++) {
            cout << matrix[i][j] << " ";
        }

        cout << endl;
    }
}