/*********************************************************************************************************
*                               Курс ПРОГРАММИРОВАНИЕ                                                    *
**********************************************************************************************************
* Project type  : Win64 Console Application                                                              *
* Project name  : Lab_2D                                                                                  *
* File name     : Lab_2D.cpp                                                                              *
* Language      : CPP                                                                                    *
* Programmers   : Большакова Алёна Денисовна, Кожушная Вероника Олеговна                                 *
* Modified By   :                                                                                        *
* Created       : 02.04.2024                                                                             *
* Last Revision : 03.04.2024                                                                             *
* Comment       : чзх                                                                                    *
*********************************************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <Windows.h>

using namespace std;

int massiv[10] = { '0','1','2','3','4','5','6','7','8','9' };

// Функция проверки матрицы (для файла)
int checkMatrixF(const char* filename, int& lines, int& colls);

// Функция вывода ошибок
int printError(const char* filename, int& lines, int& colls);

// Функция проверки матрицы (для консоли)
int checkMatrixC(const char* line, int colls);

// Функция печати матрицы
void printMatrix(int** matrix, int lines, int colls);

// Функция подсчета суммы и номеров строк, в который она максимальна и минимальна
void getSumm(int** matrix, int& minn, int& maxx, int lines, int colls, int& maxxSumm, int& minnSumm);

// Функция смены строк в матрице с минимальной и максимальной суммой
void switchLines(int** matrix, int** matrixD, int& minn, int& maxx, int lines, int colls);

// Функция проверки числа
int findNum(char num);

// Функция ввода матрицы с консоли
int enterMatrix(int** matrix, int& lines, int& colls);

// Функция заполнения матрицы
void fillMatrix(int** matrix, const char* filename, int lines, int colls);

int main()
{
    setlocale(LC_ALL, "RUSSIAN");

    int countLinesA = 0; // Кол-во строк в матрице А
    int countCollsA = 0; // Кол-во столбцов в матрице А

    //---------------------------------
    // БЛОК ЧТЕНИЯ С КОНСОЛИ
    //---------------------------------

    int numMinnA = 0;
    int numMaxxA = 0;
    int maxxSumm;
    int minnSumm;

    cout << "Введите кол-во строк и столбцов матрицы: " << endl;
    cin >> countLinesA >> countCollsA;

    // ВЫДЕЛЯЕМ ПАМЯТЬ
    int** matrixA = new int* [countLinesA];
    for (int i = 0; i < countLinesA; ++i) {
        matrixA[i] = new int[countCollsA];
    }

    // ВВОД МАТРИЦЫ
    if (enterMatrix(matrixA, countLinesA, countCollsA) == 0) {
        return 0;
    }

    // ПОДСЧЕТ СУММЫ В КАЖДОЙ СТРОЧКЕ
    getSumm(matrixA, numMinnA, numMaxxA, countLinesA, countCollsA, maxxSumm, minnSumm);

    // ВЫДЕЛЯЕМ ПАМЯТЬ
    int** matrixAD = new int* [countLinesA];
    for (int i = 0; i < countLinesA; ++i) {
        matrixAD[i] = new int[countCollsA];
    }

    // СМЕНА СТРОК С МАКСИМАЛЬНОЙ И МИНИМАЛЬНОЙ СУММОЙ
    switchLines(matrixA, matrixAD, numMinnA, numMaxxA, countLinesA, countCollsA);

    // ВЫВОД МАТРИЦ СО СМЕНОЙ СТРОК
    cout << "Измененная матрица A с размерностью " << countLinesA << " на " << countCollsA << ":" << endl;
    printMatrix(matrixAD, countLinesA, countCollsA);
    cout << "Максимальная сумма элементов строки - " << maxxSumm << endl;
    cout << "Минимальная сумма элементов строки - " << minnSumm << endl;
}
//---------------------------------
// БЛОК ЧТЕНИЯ ИЗ ФАЙЛА
//---------------------------------

    //int countLinesB; // Кол-во строк в матрице B
    //int countCollsB; // Кол-во столбцов в матрице B
    //const char* filenameA = "matrA.txt"; // Файл с матрицей А
    //const char* filenameB = "matrB.txt"; // Файл с матрицей B

    //// ДЕЙСТВИЯ ДЛЯ ФАЙЛА А
    //cout << "МАТРИЦА А" << endl;

    //if (printError(filenameA, countLinesA, countCollsA) == 1) {
    //    return 0;
    //}

    //// ВЫДЕЛЯЕМ ПАМЯТЬ
    //int** matrixA = new int* [countLinesA];
    //for (int i = 0; i < countLinesA; ++i) {
    //    matrixA[i] = new int[countCollsA];
    //}

    //fillMatrix(matrixA, filenameA, countLinesA, countCollsA);
    //
    //cout << "Исходная матрица А с размерностью " << countLinesA << " на " << countCollsA << ":" << endl;
    //printMatrix(matrixA, countLinesA, countCollsA);

    //// ВЫЧИСЛЕНИЕ СТОК С МАКСИМАЛЬНОЙ И МИНИМАЛЬНОЙ СУММОЙ ЭЛЕМЕНТОВ
    //int maxxSummA; // Максимальная сумма элементов в строке
    //int minnSummA; // Минимальная сумма элементов в строке
    //int numMinnA = 0; // Номер строки с минимальной суммой 
    //int numMaxxA = 0; // Номер строки с максимальной суммой
    //getSumm(matrixA, numMinnA, numMaxxA, countLinesA, countCollsA, maxxSummA, minnSummA);

    //// ВЫДЕЛЯЕМ ПАМЯТЬ
    //int** matrixAD = new int* [countLinesA];
    //for (int i = 0; i < countLinesA; ++i) {
    //    matrixAD[i] = new int[countCollsA];
    //}

    //// СМЕНА СТРОК С МАКСИМАЛЬНОЙ И МИНИМАЛЬНОЙ СУММОЙ ЭЛЕМЕНТОВ
    //switchLines(matrixA, matrixAD, numMinnA, numMaxxA, countLinesA, countCollsA);
    //cout << "Измененная матрица A с размерностью " << countLinesA << " на " << countCollsA << ":" << endl;
    //printMatrix(matrixAD, countLinesA, countCollsA);
    //cout << "Максимальная сумма элементов строки - " << maxxSummA << endl;
    //cout << "Минимальная сумма элементов строки - " << minnSummA << endl;
    //cout << endl;

    //// ДЕЙСТВИЯ ДЛЯ ФАЙЛА B
    //cout << "МАТРИЦА В" << endl;

    //if (printError(filenameB, countLinesB, countCollsB) == 1) {
    //    return 0;
    //}

    //// ВЫДЕЛЯЕМ ПАМЯТЬ
    //int** matrixB = new int* [countLinesB];
    //for (int i = 0; i < countLinesB; ++i) {
    //    matrixB[i] = new int[countCollsB];
    //}

    //fillMatrix(matrixB, filenameB, countLinesB, countCollsB);

    //cout << "Исходная матрица В с размерностью " << countLinesB << " на " << countCollsB << ":" << endl;
    //printMatrix(matrixB, countLinesB, countCollsB);

    //// ВЫЧИСЛЕНИЕ СТОК С МАКСИМАЛЬНОЙ И МИНИМАЛЬНОЙ СУММОЙ ЭЛЕМЕНТОВ
    //int maxxSummB; // Максимальная сумма элементов в строке
    //int minnSummB; // Минимальная сумма элементов в строке
    //int numMinnB = 0; // Номер строки с минимальной суммой 
    //int numMaxxB = 0; // Номер строки с максимальной суммой
    //getSumm(matrixB, numMinnB, numMaxxB, countLinesB, countCollsB, maxxSummB, minnSummB);

    //// ВЫДЕЛЯЕМ ПАМЯТЬ
    //int** matrixBD = new int* [countLinesA];
    //for (int i = 0; i < countLinesA; ++i) {
    //    matrixBD[i] = new int[countCollsA];
    //}

    //// СМЕНА СТРОК С МАКСИМАЛЬНОЙ И МИНИМАЛЬНОЙ СУММОЙ ЭЛЕМЕНТОВ
    //switchLines(matrixB, matrixBD, numMinnB, numMaxxB, countLinesB, countCollsB);
    //cout << "Измененная матрица B с размерностью " << countLinesB << " на " << countCollsB << ":" << endl;
    //printMatrix(matrixBD, countLinesB, countCollsB);
    //cout << "Максимальная сумма элементов строки - " << maxxSummB << endl;
    //cout << "Минимальная сумма элементов строки - " << minnSummB << endl;
    //cout << endl;
//------------------------------
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
//------------------------------

// ПРОВЕРКА МАТРИЦЫ ИЗ ФАЙЛА
int checkMatrixF(const char* filename, int& lines, int& colls) {
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
    return 6;
}

void fillMatrix(int** matrix, const char* filename, int lines, int colls) {
    ifstream file;

    file.open(filename);
    file >> lines >> colls;

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < colls; ++j) {
            file >> *(*(matrix + i) + j);
        }
    }
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
void getSumm(int** matrix, int& minn, int& maxx, int lines, int colls, int& maxxSumm, int& minnSumm) {
    minnSumm = 0;
    for (int i = 0; i < colls; ++i) {
        minnSumm += *(*(matrix) + i);
        maxxSumm += *(*(matrix) + i);
    }

    for (int i = 1; i < lines; ++i) {
        int summ = 0;
        for (int j = 0; j < colls; ++j) {
            summ += *(*(matrix + i) + j);
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
void switchLines(int** matrix, int** matrixD, int& minn, int& maxx, int lines, int colls) {
    for (int i = 0; i < lines; ++i) {
        if (i == maxx) {
            for (int j = 0; j < colls; ++j) {
                *(*(matrixD + i) + j) = *(*(matrix + minn) + j);
            }
        }

        if (i == minn) {
            for (int j = 0; j < colls; ++j) {
                *(*(matrixD + i) + j) = *(*(matrix + maxx) + j);
            }
        }

        if ((i != minn) && (i != maxx)) {
            for (int j = 0; j < colls; ++j) {
                *(*(matrixD + i) + j) = *(*(matrix + i) + j);
            }
        }
    }
}

int printError(const char* filename, int& lines, int& colls) {
    switch (checkMatrixF(filename, lines, colls)) {
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

void printMatrix(int** matrix, int lines, int colls) {
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < colls; ++j) {
            cout << *(*(matrix + i) + j) << " ";
        }
        cout << endl;
    }
}

int enterMatrix(int** matrix, int& lines, int& colls) {
    char line[256];

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
                a >> *(*(matrix + i) + j);
            }
        }
    }
}