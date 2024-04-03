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
* Last Revision : 03.04.2024                                                                             *
* Comment       : чзх                                                                                    *
*********************************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "RUSSIAN");

    int forA = 0; // Счетчик строк в файле для А
    int countLinesA; // Кол-во строк в матрице А
    int countCollsA; // Кол-во столбцов в матрице А

    void getSumm(int** matrix, int& minn, int& maxx, int lines, int colls);
    void printMatrix(int** matrix, int minn, int maxx, int lines, int colls);


    //---------------------------------
    // БЛОК ЧТЕНИЯ С КОНСОЛИ
    //---------------------------------

    int numMinnA = 0;
    int numMaxxA = 0;
    
    // ВВОД МАТРИЦЫ
    cout << "Введите кол-во строк и столбцов матрицы: " << endl;
    cin >> countLinesA >> countCollsA;

    // ВЫДЕЛЯЕМ ПАМЯТЬ
    int** matrixA = new int* [countLinesA];
    for (int i = 0; i < countLinesA; ++i) {
        matrixA[i] = new int[countCollsA];
    }

    cout << "Введите матрицу: " << endl;
    for (int i = 0; i < countLinesA; ++i) {
        for (int j = 0; j < countCollsA; ++j) {
            cin >> *(*(matrixA + i) + j);
        }
    }
    cout << endl;

    // ПОДСЧЕТ СУММЫ В КАЖДОЙ СТРОЧКЕ
    getSumm(matrixA, numMinnA, numMaxxA, countLinesA, countCollsA);

    // ВЫВОД МАТРИЦ СО СМЕНОЙ СТРОК
    cout << "Матрица со сменой строк:" << endl;
    printMatrix(matrixA, numMinnA, numMaxxA, countLinesA, countCollsA);

    //---------------------------------
    // БЛОК ЧТЕНИЯ ИЗ ФАЙЛА
    //---------------------------------

    int forB = 0; // Счетчик строк в файле для B
    int countLinesB; // Кол-во строк в матрице B
    int countCollsB; // Кол-во столбцов в матрице B
    const char* filenameA = "matrA.txt"; // Файл с матрицей А
    const char* filenameB = "matrB.txt"; // Файл с матрицей B
    char lineB[256]; // Строки в файле B
    char lineA[256]; // Строки в файле А

    void readMatrixFromFile(int** matrix, int lines, int colls, const char* filename);

    ifstream file;

    // ПЕЧАТЬ ИСХОДНЫХ ДАННЫХ МАТРИЦЫ А
    file.open(filenameA);

    if (!file.is_open())
    {
        cout << "Не удалось открыть файл!" << endl;
        return 0;
    }

    cout << "Исходная матрица A:" << endl;

    while (!file.eof()) {

        if (forA == 0) {
            file >> countLinesA >> countCollsA;
        }

        else {
            file.getline(lineA, sizeof(lineA), '/n');
            cout << lineA << endl;
        }

        // Пустой файл
        if ((file.eof()) && (file.fail()) && (forA == 0))
        {
            cout << "Матрица А не введена. Файл пуст!" << endl;
            file.close();
            return 0;
        }

        ++forA;
    }

    cout << endl;

    if ((file.eof()) && (forA == 1))
    {
        cout << "Матрица А не введена!" << endl;
        return 0;
    }

    // ВЫДЕЛЯЕМ ПАМЯТЬ
    int** matrixA = new int* [countLinesA];
    for (int i = 0; i < countLinesA; ++i) {
        matrixA[i] = new int[countCollsA];
    }

    cout << "Размерность матрицы А: " << countLinesA << " " << countCollsA << endl;

    file.close();

    cout << endl;

    // ПЕЧАТЬ ИСХОДНЫХ ДАННЫХ МАТРИЦЫ B
    file.open(filenameB);

    if (!file.is_open())
    {
        cout << "Не удалось открыть файл!" << endl;
        return 0;
    }

    cout << "Исходная матрица B:" << endl;

    while (!file.eof()) {

        if (forB == 0) {
            file >> countLinesB >> countCollsB;
        }

        else {
            file.getline(lineB, sizeof(lineB), '/n');
            cout << lineB << endl;
        }

        // Пустой файл
        if ((file.eof()) && (file.fail()) && (forB == 0))
        {
            cout << "Матрица B не введена. Файл пуст!" << endl;
            file.close();
            return 0;
        }
        ++forB;
    }
    cout << endl;

    if ((file.eof()) && (forB == 1))
    {
        cout << "Матрица B не введена!" << endl;
        return 0;
    }

    // ВЫДЕЛЯЕМ ПАМЯТЬ
    int** matrixB = new int* [countLinesB];
    for (int i = 0; i < countLinesB; ++i) {
        matrixB[i] = new int[countCollsB];
    }

    cout << "Размерность матрицы B: " << countLinesB << " " << countCollsB << endl;
    cout << endl;

    file.close();

    // ЧТЕНИЕ МАТРИЦ

    readMatrixFromFile(matrixA, countLinesA, countCollsA, filenameA);
    readMatrixFromFile(matrixB, countLinesB, countCollsB, filenameB);

    // ПОДСЧЕТ СУММЫ В КАЖДОЙ СТРОКЕ

    int numMinnA = 0;
    int numMinnB = 0;
    int numMaxxA = 0;
    int numMaxxB = 0;
    getSumm(matrixA, numMinnA, numMaxxA, countLinesA, countCollsA);
    getSumm(matrixB, numMinnB, numMaxxB, countLinesB, countCollsB);

    // ВЫВОД МАТРИЦ СО СМЕНОЙ СТРОК

    cout << "Матрица А со сменой строк:" << endl;
    printMatrix(matrixA, numMinnA, numMaxxA, countLinesA, countCollsA);
    cout << endl;
    cout << "Матрица B со сменой строк:" << endl;
    printMatrix(matrixB, numMinnB, numMaxxB, countLinesB, countCollsB);
}

//------------------------------
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
//------------------------------

// СЧИТЫВАНИЕ МАТРИЦЫ
void readMatrixFromFile(int** matrix, int lines, int colls, const char* filename) {
    int sizeLines;
    int sizeColls;
    ifstream file(filename);
    file >> sizeLines;
    file >> sizeColls;
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < colls; ++j) {
            file >> *(*(matrix + i) + j);
        }
    }

    file.close();
}

// НАХОЖДЕНИЕ СТРОК С МИНИМАЛЬНОЙ И МАКСИМАЛЬНОЙ СУММОЙ ЭЛЕМЕНТОВ
void getSumm(int** matrix, int& minn, int& maxx, int lines, int colls) {
    int maxxSumm = -1000000000;
    int minnSumm = 100000000;

    for (int i = 0; i < lines; ++i) {
        int summ = 0;
        for (int j = 0; j < colls; ++j) {
            summ += (*(*(matrix + i) + j));
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

// ПЕЧАТЬ МАТРИЦЫ СО СМЕНОЙ СТРОК
void printMatrix(int** matrix, int minn, int maxx, int lines, int colls) {

    for (int i = 0; i < lines; ++i) {
        if (i == maxx) {
            for (int j = 0; j < colls; ++j) {
                cout << (*(*(matrix + minn) + j)) << " ";
            }
            cout << endl;
        }

        if (i == minn) {
            for (int j = 0; j < colls; ++j) {
                cout << (*(*(matrix + maxx) + j)) << " ";
            }
            cout << endl;
        }

        if (i != minn && i != maxx) {
            for (int j = 0; j < colls; ++j) {
                cout << (*(*(matrix + i) + j)) << " ";
            }
            cout << endl;
        }
    }
}
