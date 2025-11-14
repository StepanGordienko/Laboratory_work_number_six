#include <iostream>
#include <cstdlib>

using namespace std;


int** createExtendedMatrix(int A, int B, int C, int D, int& extendedRows, int& extendedCols) {
    extendedRows = 2 + A;
    extendedCols = 2 + B;

    int** extendedMatrix = (int**)malloc(extendedRows * sizeof(int*));
    for (int i = 0; i < extendedRows; i++) {
        extendedMatrix[i] = (int*)malloc(extendedCols * sizeof(int));
    }

    for (int i = 0; i < extendedRows; i++) {
        for (int j = 0; j < extendedCols; j++) {
            extendedMatrix[i][j] = i * C + j * D;
        }
    }

    return extendedMatrix;
}


int* findZeroCells(int** matrix, int rows, int cols, int& count) {
    count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                count++;
            }
        }
    }

    if (count == 0) {
        return nullptr;
    }


    int* result = (int*)malloc(count * sizeof(int));
    int index = 0;


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                result[index++] = i;
                break;
            }
        }
    }

    return result;
}


int** removeRows(int** matrix, int rows, int cols, int* rowsToRemove, int removeCount, int& newRows) {
    if (removeCount == 0 || rowsToRemove == nullptr) {
        newRows = rows;
        return matrix;
    }

    newRows = rows - removeCount;

    if (newRows <= 0) {
        return nullptr;
    }


    int** newMatrix = (int**)malloc(newRows * sizeof(int*));
    for (int i = 0; i < newRows; i++) {
        newMatrix[i] = (int*)malloc(cols * sizeof(int));
    }

    int newIndex = 0;
    for (int i = 0; i < rows; i++) {
        bool shouldRemove = false;
        for (int j = 0; j < removeCount; j++) {
            if (i == rowsToRemove[j]) {
                shouldRemove = true;
                break;
            }
        }

        if (!shouldRemove) {
            for (int j = 0; j < cols; j++) {
                newMatrix[newIndex][j] = matrix[i][j];
            }
            newIndex++;
        }
    }

    return newMatrix;
}


void printMatrix(int** matrix, int rows, int cols) {
    if (matrix == nullptr) return;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}


void freeMatrix(int** matrix, int rows) {
    if (matrix == nullptr) return;

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    setlocale(LC_ALL, "Ru");

    int A, B, C, D;

    do {
        cout << "Введите значение переменной A = ";
        cin >> A;
        if (A < 0) cout << "Переменная не может быть отрицательной!" << endl;
    } while (A < 0);

    do {
        cout << "Введите значение переменной B = ";
        cin >> B;
        if (B < 0) cout << "Переменная не может быть отрицательной!" << endl;
    } while (B < 0);

    do {
        cout << "Введите значение переменной C = ";
        cin >> C;
        if (C < 0) cout << "Переменная не может быть отрицательной!" << endl;
    } while (C < 0);

    do {
        cout << "Введите значение переменной D = ";
        cin >> D;
        if (D < 0) cout << "Переменная не может быть отрицательной!" << endl;
    } while (D < 0);


    int** initialMatrix = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        initialMatrix[i] = (int*)malloc(2 * sizeof(int));
    }


    initialMatrix[0][0] = A;
    initialMatrix[0][1] = B;
    initialMatrix[1][0] = C;
    initialMatrix[1][1] = D;

    printMatrix(initialMatrix, 2, 2);



    int extendedRows, extendedCols;
    int** extendedMatrix = createExtendedMatrix(A, B, C, D, extendedRows, extendedCols);

    if (extendedMatrix == nullptr) {
        freeMatrix(initialMatrix, 2);
        return 1;
    }

    printMatrix(extendedMatrix, extendedRows, extendedCols);


    int zeroCellsCount = 0;
    int* zeroRows = findZeroCells(extendedMatrix, extendedRows, extendedCols, zeroCellsCount);


    if (zeroCellsCount > 0 && zeroRows != nullptr) {
        cout << "Индексы строк с нулевыми ячейками: ";
        for (int i = 0; i < zeroCellsCount; i++) {
            cout << zeroRows[i] << " ";
        }
        cout << endl;
    }


    int finalRows = 0;
    int** finalMatrix = removeRows(extendedMatrix, extendedRows, extendedCols,
        zeroRows, zeroCellsCount, finalRows);



    if (finalMatrix != nullptr && finalRows > 0) {
        printMatrix(finalMatrix, finalRows, extendedCols);
    }
    else {
        cout << "Матрица пуста!" << endl;
    }


    freeMatrix(initialMatrix, 2);
    freeMatrix(extendedMatrix, extendedRows);

    if (finalMatrix != nullptr && finalMatrix != extendedMatrix) {
        freeMatrix(finalMatrix, finalRows);
    }

    if (zeroRows != nullptr) {
        free(zeroRows);
    }

    int a, b;


    cout << "Введите значение переменной a: ";
    cin >> a;
    cout << "Введите значение переменной b: ";
    cin >> b;

    int* ptrA = &a;
    int* ptrB = &b;

    *ptrA = *ptrA * 2;

    int temp = *ptrA;
    *ptrA = *ptrB;
    *ptrB = temp;


    int* AVar1 = new int(*ptrA);
    int* BVar2 = new int(*ptrB);

    cout << "new A = " << *AVar1 << ", new B = " << *BVar2 << endl;


    delete AVar1;
    delete BVar2;

    return 0;
}