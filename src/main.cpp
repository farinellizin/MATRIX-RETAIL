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
    bool verify = false;

    int line_cont = (final_i - initial_i + 1), cont = 0;

    // int matrix[final_i - initial_i][final_j - initial_j];

    int matrix[10][10];

    int j_coord = 0;

    int I = 0, J = 0;

    if (myfile.is_open()) {
        for(int i = 0; i < initial_i - 1; i++) {
            getline(myfile, line);
        }

        while(!myfile.eof() && verify == false) {
            while (getline(myfile, line, ' ')) {
                j_coord++;

                if (j_coord >= initial_j && j_coord <= final_j) {
                    matrix[I][J] = stoi(line);
                    J++;
                    

                    if (J == 6) {
                        J = 0;
                        I++;
                    }
                }

                if (j_coord == final_j) {
                    j_coord = 0;
                }
            }
            
            cont++;

            if(cont == line_cont) {
                verify = true;
            }
        }
    }
}