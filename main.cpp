// Name: Calder Kamman
// KUID: 3123207
// LAB Session: Thursday 9 a.m.
// LAB Assignment: 7
// Description: This program reads values from a file into a matrix, Adds two matrices with  operator overloading, Multiply two matrices using operator overloading, getting the sum of matrix diagonal elements, and swapping matrix rows.
// Collaborators: None

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Matrix {
private:
    vector<vector<int>> data;
    int size;

public:
    Matrix(int n) : size(n) {
        data.resize(size, vector<int>(size, 0)); 
    }

    bool loadMatrixFromFile(const string &filename) {  
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open file: " << filename << endl;
            return false;
        }

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file >> data[i][j];
            }
        }

        file.close();
        return true;
    }

    void displayMatrix() const {
        for (const auto &row : data) {
            for (int value : row) {
                cout << value << " ";
            }
            cout << endl;
        }
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < size; k++) {
                    result.data[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    int sumDiagonals() const {  
        int mainDiagonalSum = 0;
        int secondaryDiagonalSum = 0;
        for (int i = 0; i < size; i++) {
            mainDiagonalSum += data[i][i];
            secondaryDiagonalSum += data[i][size - i - 1];
        }
        return mainDiagonalSum + secondaryDiagonalSum;  
    }

    void swapRows(int row1, int row2) {
        if (row1 >= 0 && row1 < size && row2 >= 0 && row2 < size) {
            swap(data[row1], data[row2]);
        } else {
            cout << "Invalid row indices." << endl;
        }
    }
};

int main() {
    int matrixSize = 4;

    Matrix matrixA(matrixSize);
    Matrix matrixB(matrixSize);

    string filenameA, filenameB;
    cout << "Enter the filename for Matrix A: ";
    cin >> filenameA;
    cout << "Enter the filename for Matrix B: ";
    cin >> filenameB;

    if (!matrixA.loadMatrixFromFile(filenameA) || !matrixB.loadMatrixFromFile(filenameB)) {
        return 1;
    }

    cout << "Matrix A:" << endl;
    matrixA.displayMatrix();

    cout << "\nMatrix B:" << endl;
    matrixB.displayMatrix();

    Matrix sumMatrix = matrixA + matrixB;
    cout << "\nMatrix A + Matrix B:" << endl;
    sumMatrix.displayMatrix();

    Matrix productMatrix = matrixA * matrixB;
    cout << "\nMatrix A * Matrix B:" << endl;
    productMatrix.displayMatrix();

    int diagonalSum = matrixA.sumDiagonals();
    cout << "\nSum of diagonals of Matrix A: " << diagonalSum << endl;

    cout << "\nMatrix A after swapping row 1 and row 3:" << endl;
    matrixA.swapRows(0, 2);
    matrixA.displayMatrix();

    return 0;
}

