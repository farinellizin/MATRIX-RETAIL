#include "matrix.hpp"
using namespace std;

int main() {
    int initial_i, initial_j, final_i, final_j;
    ifstream myfile;
    myfile.open("matrix.txt");
    string line;
    int cont = 0;
    int num_elements = (final_i - initial_i + 1) * (final_j - initial_j + 1);
    int matrix[final_i - initial_i + 1][final_j - initial_j + 1];
    int j_coord = 0;
    int I = 0, J = 0;

    cout << "\t- Please inform the initial I coordenate: ";
    cin >> initial_i;

    cout << "\t- Please inform the initial J coordenate: ";
    cin >> initial_j;

    cout << "\t- Please inform the final I coordenate: ";
    cin >> final_i;

    cout << "\t- Please inform the final J coordenate: ";
    cin >> final_j;

    if (myfile.is_open()) {
        for(int i = 0; i < initial_i - 1; i++) {
            getline(myfile, line);
        }

        while(!myfile.eof()) {
            while (getline(myfile, line, ' ') && cont < num_elements) {
                j_coord++;

                if (j_coord >= initial_j && j_coord <= final_j) {
                    matrix[I][J] = stoi(line);
                    J++;
                
                    if (J == (final_j - initial_j + 1)) {
                        J = 0;
                        I++;
                    }

                    cont++;
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