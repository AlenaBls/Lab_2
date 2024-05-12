/*********************************************************************************************************
*                               Курс ПРОГРАММИРОВАНИЕ                                                    *
**********************************************************************************************************
* Project type  : Win64 Console Application                                                              *
* Project name  : Lab_2                                                                                  *
* File name     : Lab_2.cpp                                                                              *
* Language      : CPP                                                                                    *
* Programmers   : Большакова Алёна Денисовна, Кожушная Вероника Олеговна                                 *
* Modified By   :                                                                                        *
* Created       : 02.04.2024                                                                             *
* Last Revision : 02.05.2024                                                                             *
* Comment       : чзх                                                                                    *
*********************************************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <Windows.h>

using namespace std;

const int MAX_SIZE = 100;

int massiv[10] = { '0','1','2','3','4','5','6','7','8','9' };

// Функция проверки матрицы (для файла)
int checkMatrixF(int matrix[MAX_SIZE][MAX_SIZE], const char* filename, int& lines, int& colls);

// Функция вывода ошибок
int printError(int res);

// Функция проверки матрицы (для консоли)
int checkMatrixC(const char* line, int colls);

// Функция печати матрицы
void printMatrix(int matrix[MAX_SIZE][MAX_SIZE], int lines, int colls);

// Функция подсчета суммы и номеров строк, в который она максимальна и минимальна
void getSumm(int matrix[MAX_SIZE][MAX_SIZE], int& minn, int& maxx, int lines, int colls, int& maxxSumm, int& minnSumm);

// Функция смены строк в матрице с минимальной и максимальной суммой
void switchLines(int matrix[MAX_SIZE][MAX_SIZE], int matrixD[MAX_SIZE][MAX_SIZE], int& minn, int& maxx, int lines, int colls);

// Функция проверки числа
int findNum(char num);

// Функция ввода матрицы с консоли
int enterMatrix(int matrix[MAX_SIZE][MAX_SIZE], int& lines, int& colls);

int main()
{
    setlocale(LC_ALL, "RUSSIAN");

    int countLinesA = 0; // Кол-во строк в матрице А
    int countCollsA = 0; // Кол-во столбцов в матрице А

    //---------------------------------
    // БЛОК ЧТЕНИЯ С КОНСОЛИ
    //---------------------------------

//    int matrixA[MAX_SIZE][MAX_SIZE];
//    int matrixAD[MAX_SIZE][MAX_SIZE];
//    int numMinnA = 0;
//    int numMaxxA = 0;
//    int maxxSumm;
//    int minnSumm;
//
//    // ВВОД МАТРИЦЫ
//    if (enterMatrix(matrixA, countLinesA, countCollsA) == 0) {
//        return 0;
//    }
//
//    // ПОДСЧЕТ СУММЫ В КАЖДОЙ СТРОЧКЕ
//    getSumm(matrixA, numMinnA, numMaxxA, countLinesA, countCollsA, maxxSumm, minnSumm);
//
//    // СМЕНА СТРОК С МАКСИМАЛЬНОЙ И МИНИМАЛЬНОЙ СУММОЙ
//    switchLines(matrixA, matrixAD, numMinnA, numMaxxA, countLinesA, countCollsA);
//
//    // ВЫВОД МАТРИЦ СО СМЕНОЙ СТРОК
//    cout << "Измененная матрица A с размерностью " << countLinesA << " на " << countCollsA << ":" << endl;
//    printMatrix(matrixAD, countLinesA, countCollsA);
//    cout << "Максимальная сумма элементов строки - " << maxxSumm << endl;
//    cout << "Минимальная сумма элементов строки - " << minnSumm << endl;
//}
    //---------------------------------
    // БЛОК ЧТЕНИЯ ИЗ ФАЙЛА
    //---------------------------------

    int countLinesB; // Кол-во строк в матрице B
    int countCollsB; // Кол-во столбцов в матрице B
    const char* filenameA = "matrA.txt"; // Файл с матрицей А
    const char* filenameB = "matrB.txt"; // Файл с матрицей B
    int matrixA[MAX_SIZE][MAX_SIZE]; // Матрица А
    int matrixB[MAX_SIZE][MAX_SIZE]; // Матрица B

    // ДЕЙСТВИЯ ДЛЯ ФАЙЛА А
    cout << "МАТРИЦА А" << endl;

    int resultA = checkMatrixF(matrixA, filenameA, countLinesA, countCollsA);

    if (printError(resultA) == 0) {

        cout << "Исходная матрица А с размерностью " << countLinesA << " на " << countCollsA << ":" << endl;
        printMatrix(matrixA, countLinesA, countCollsA);

        // ВЫЧИСЛЕНИЕ СТОК С МАКСИМАЛЬНОЙ И МИНИМАЛЬНОЙ СУММОЙ ЭЛЕМЕНТОВ
        int maxxSummA; // Максимальная сумма элементов в строке
        int minnSummA; // Минимальная сумма элементов в строке
        int numMinnA = 0; // Номер строки с минимальной суммой 
        int numMaxxA = 0; // Номер строки с максимальной суммой
        getSumm(matrixA, numMinnA, numMaxxA, countLinesA, countCollsA, maxxSummA, minnSummA);

        // СМЕНА СТРОК С МАКСИМАЛЬНОЙ И МИНИМАЛЬНОЙ СУММОЙ ЭЛЕМЕНТОВ
        int matrixAD[MAX_SIZE][MAX_SIZE];
        switchLines(matrixA, matrixAD, numMinnA, numMaxxA, countLinesA, countCollsA);
        cout << "Измененная матрица A с размерностью " << countLinesA << " на " << countCollsA << ":" << endl;
        printMatrix(matrixAD, countLinesA, countCollsA);
        cout << "Максимальная сумма элементов строки - " << maxxSummA << endl;
        cout << "Минимальная сумма элементов строки - " << minnSummA << endl;
        cout << endl;
    }

    // ДЕЙСТВИЯ ДЛЯ ФАЙЛА B
    cout << "МАТРИЦА В" << endl;

    int resultB = checkMatrixF(matrixB, filenameB, countLinesB, countCollsB);

    if (printError(resultB) == 1) {
        return 0;
    }

    cout << "Исходная матрица В с размерностью " << countLinesB << " на " << countCollsB << ":" << endl;
    printMatrix(matrixB, countLinesB, countCollsB);

    // ВЫЧИСЛЕНИЕ СТОК С МАКСИМАЛЬНОЙ И МИНИМАЛЬНОЙ СУММОЙ ЭЛЕМЕНТОВ
    int maxxSummB; // Максимальная сумма элементов в строке
    int minnSummB; // Минимальная сумма элементов в строке
    int numMinnB = 0; // Номер строки с минимальной суммой 
    int numMaxxB = 0; // Номер строки с максимальной суммой
    getSumm(matrixB, numMinnB, numMaxxB, countLinesB, countCollsB, maxxSummB, minnSummB);

    // СМЕНА СТРОК С МАКСИМАЛЬНОЙ И МИНИМАЛЬНОЙ СУММОЙ ЭЛЕМЕНТОВ
    int matrixBD[MAX_SIZE][MAX_SIZE];
    switchLines(matrixB, matrixBD, numMinnB, numMaxxB, countLinesB, countCollsB);
    cout << "Измененная матрица B с размерностью " << countLinesB << " на " << countCollsB << ":" << endl;
    printMatrix(matrixBD, countLinesB, countCollsB);
    cout << "Максимальная сумма элементов строки - " << maxxSummB << endl;
    cout << "Минимальная сумма элементов строки - " << minnSummB << endl;
    cout << endl;
}

//------------------------------
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
//------------------------------

// ПРОВЕРКА МАТРИЦЫ ИЗ ФАЙЛА
int checkMatrixF(int matrix[MAX_SIZE][MAX_SIZE], const char* filename, int& lines, int& colls) {
    ifstream file;

    file.open(filename);

    int st = 0; // Счетчик строк в файле
    int stl = 0; // Счетчик столбцов в файле 
    char line[256];

    if (!file.is_open())
    {
        return 1; // Код ошибки при неверном имени файла
    }

    while (!file.eof()) {

        if (st == 0) {
            file >> lines >> colls;
            if ((lines > 0) && (colls > 0)) {
                ++st;
            }
            file.getline(line, sizeof(line));
        }

        else {
            for (int m = 0; m < 256; m++) {
                line[m] = 'n';
            }
            line[255] = '\0';

            file.getline(line, sizeof(line));
            ++st;

            if ((stl == 0) && (findNum(line[0]) == 1)) {
                ++stl;
            }

            for (int i = 1; i < 256; ++i) {
                if ((findNum(line[i]) == 1) && (findNum(line[i - 1]) == 0)) {
                    ++stl;
                }
            }

            if (stl != colls) {
                file.close();
                return 4; // Код ошибки при неверном кол-ве столбцов
            }

            else {
                stl = 0;
            }
        }

        if ((file.eof()) && (file.fail()) && (st == 0))
        {
            file.close();
            return 2; // Код ошибки при пустом файле
        }
    }

    if ((file.eof()) && (st == 1))
    {
        file.close();
        return 3; // Код ошибки для невведенной матрицы
    }

    if (st - 1 != lines) {
        file.close();
        return 5; // Код ошибки для неверного кол-ва строк 
    }
    file.close();

    int sizeLines;
    int sizeColls;

    file.open(filename);
    file >> sizeLines;
    file >> sizeColls;
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < colls; ++j) {
            file >> matrix[i][j];
        }
    }

    return 6;
    file.close();
}

// ПРОВЕРКА МАТРИЦЫ С КОНСОЛИ
int checkMatrixC(const char* line, int colls) {
    int stl = 0; // Счетчик элементов строки

    if ((stl == 0) && (findNum(line[0]) == 1)) {
        ++stl;
    }

    for (int i = 1; i < 256; ++i) {
        if ((findNum(line[i]) == 1) && (findNum(line[i - 1]) == 0)) {
            ++stl;
        }
    }

    if (stl != colls) {
        return 0; // Код ошибки при неверном кол-ве столбцов
    }
    else {
        return 1;
    }
}

// НАХОЖДЕНИЕ СТРОК С МИНИМАЛЬНОЙ И МАКСИМАЛЬНОЙ СУММОЙ ЭЛЕМЕНТОВ
void getSumm(int matrix[MAX_SIZE][MAX_SIZE], int& minn, int& maxx, int lines, int colls, int& maxxSumm, int& minnSumm) {
    minnSumm = 0;
    for (int i = 0; i < colls; ++i) {
        minnSumm += matrix[0][i];
        maxxSumm += matrix[0][i];
    }

    for (int i = 1; i < lines; ++i) {
        int summ = 0;
        for (int j = 0; j < colls; ++j) {
            summ += matrix[i][j];
        }
        if (summ < minnSumm) {
            minnSumm = summ;
            minn = i;
        }
        if (summ > maxxSumm) {
            maxxSumm = summ;
            maxx = i;
        }
    }
}

// ФУНКЦИЯ ПРОВЕРКИ НА ЧИСЛО
int findNum(char num) {
    for (int i = 0; i < 10; ++i) {
        if (massiv[i] == num) {
            return 1;
        }
    }
    return 0;
}

// ФУНКЦИЯ СМЕНЫ СТРОК
void switchLines(int matrix[MAX_SIZE][MAX_SIZE], int matrixD[MAX_SIZE][MAX_SIZE], int& minn, int& maxx, int lines, int colls) {
    for (int i = 0; i < lines; ++i) {
        if (i == maxx) {
            for (int j = 0; j < colls; ++j) {
                matrixD[i][j] = matrix[minn][j];
            }
        }

        if (i == minn) {
            for (int j = 0; j < colls; ++j) {
                matrixD[i][j] = matrix[maxx][j];
            }
        }

        if ((i != minn) && (i != maxx)) {
            for (int j = 0; j < colls; ++j) {
                matrixD[i][j] = matrix[i][j];
            }
        }
    }
}

int printError(int res) {
    switch (res) {
    case 1:
        cout << "Не удалось открыть файл!" << endl;
        return 1;
    case 2:
        cout << "Матрицa не введена. Файл пуст!" << endl;
        return 1;
    case 3:
        cout << "Матрица не введена!" << endl;
        return 1;
    case 4:
        cout << "Неверное кол-во колонок!" << endl;
        return 1;
    case 5:
        cout << "Неверное кол-во строк!" << endl; 
        return 1;
    case 6:
        cout << "Файл прошел проверки" << endl;
        return 0;
    }
}

void printMatrix(int matrix[MAX_SIZE][MAX_SIZE], int lines, int colls) {
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < colls; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int enterMatrix(int matrix[MAX_SIZE][MAX_SIZE], int& lines, int& colls) {
    char line[256];

    cout << "Введите кол-во строк и столбцов матрицы: " << endl;
    cin >> lines >> colls; 
    cin.getline(line, sizeof(line));

    cout << "Введите матрицу: " << endl;
    for (int i = 0; i < lines; i++) {

        for (int m = 0; m < 256; m++) {
            line[m] = 'n';
        }
        line[255] = '\0';

        cin.getline(line, sizeof(line));

        if (checkMatrixC(line, colls) == 0) {
            cout << "Введено неверное кол-во элементов строки!" << endl;
            return 0;
        }
        else {
            string l(line);
            istringstream a(l);
            for (int j = 0; j <= lines; j++) {
                a >> matrix[i][j];
            }
        }
    }
}