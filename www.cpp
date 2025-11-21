#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int ROWS = 2;
const int COLS = 2;

void printMatrix(int** matrix, int rows, int cols) {
    cout << "\nМатрица " << rows << "x" << cols << ":\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << setw(6) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int** createExtendedMatrix(int** matrix, int& rows, int& cols) {

    int A = matrix[0][0];
    int B = matrix[0][1];
    int C = matrix[1][0];
    int D = matrix[1][1];

    int newRows = ROWS + A;
    int newCols = COLS + B;

    matrix = (int**)realloc(matrix, newRows * sizeof(int*));

    for (int i = 0; i < newRows; ++i) {
        if (i < ROWS) {
            matrix[i] = (int*)realloc(matrix[i], newCols * sizeof(int));
        }
        else {
            matrix[i] = (int*)malloc(newCols * sizeof(int));
        }
    }

    for (int i = 0; i < newRows; ++i) {
        for (int j = 0; j < newCols; ++j) {
            matrix[i][j] = i * C + j * D;
        }
    }

    rows = newRows;
    cols = newCols;
    return matrix;
}

int* findZeroRows(int** matrix, int rows, int cols, int& count) {
    count = 0;


    for (int i = 0; i < rows; i++) {
        bool hasZero = false;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                hasZero = true;
                break;
            }
        }
        if (hasZero) {
            count++;
        }
    }


    int* zeroRows = (int*)malloc(count * sizeof(int));

    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                zeroRows[index] = i;
                index++;
                break;
            }
        }
    }

    return zeroRows;
}

int** removeRows(int** matrix, int& rows, int cols, int* rowsToRemove, int removeCount) {
    if (removeCount == 0 || rowsToRemove == nullptr) {
        return matrix;
    }

    int newRows = rows - removeCount;

    if (newRows <= 0) {

        for (int i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
        rows = 0;
        return nullptr;
    }

    int** temp = (int**)malloc(newRows * sizeof(int*));
    int tempIndex = 0;


    for (int i = 0; i < rows; i++) {
        bool remove = false;
        for (int j = 0; j < removeCount; j++) {
            if (i == rowsToRemove[j]) {
                remove = true;
                break;
            }
        }

        if (!remove) {
            temp[tempIndex++] = matrix[i];
        }
        else {
            free(matrix[i]);
        }
    }

    matrix = (int**)realloc(matrix, newRows * sizeof(int*));

    for (int i = 0; i < newRows; i++) {
        matrix[i] = temp[i];
    }

    free(temp);
    rows = newRows;
    return matrix;
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


    int** matrix = (int**)malloc(ROWS * sizeof(int*));
    for (int i = 0; i < ROWS; ++i) {
        matrix[i] = (int*)malloc(COLS * sizeof(int));
    }
    /*
    cout << "Введите элементы матрицы " << ROWS << "x" << COLS << ":" << endl;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << "Элемент [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
            if (matrix[i][j] < 0) {
                cout << "Ошибка! Число не может быть отрицательным. Повторите ввод." << endl;
                j -= 1;
            }
        }
    }
    */
    cout << "Введите A , B , C , D" << endl;
    cin >> A >> B >> C >> D;
    if (A || B < 0) {
        return 1
    }

    int rows = ROWS, cols = COLS;
    matrix = createExtendedMatrix(matrix, rows, cols);

    int zeroRowsCount;
    int* zeroRows = findZeroRows(matrix, rows, cols, zeroRowsCount);

    cout << "\nНайдено строк с нулевыми элементами: " << zeroRowsCount << endl;
    if (zeroRowsCount > 0) {
        cout << "Индексы строк с нулями: ";
        for (int i = 0; i < zeroRowsCount; i++) {
            cout << zeroRows[i] << " ";
        }
        cout << endl;
    }

    matrix = removeRows(matrix, rows, cols, zeroRows, zeroRowsCount);

    if (matrix != nullptr && rows > 0) {
        cout << "\nМатрица:" << endl;
        printMatrix(matrix, rows, cols);
    }
    else {
        cout << "\nВсе строки были удалены!" << endl;
    }

    if (zeroRows != nullptr) {
        free(zeroRows);
    }
    if (matrix != nullptr) {
        freeMatrix(matrix, rows);
    }

    return 0;
}