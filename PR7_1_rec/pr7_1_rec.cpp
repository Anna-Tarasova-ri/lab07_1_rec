// Lab_7_1_rec.cpp
// Лабораторна робота 7.1.
// Пошук заданих елементів та впорядкування рядків / стовпчиків матриці.
// Рекурсивний спосіб.
// Варіант 27

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

// Заповнення поточного рядка випадковими числами
void CreateRow(int** T, const int rowNo, const int colCount, const int Low,
    const int High, int colNo)
{
    T[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < colCount - 1)
        CreateRow(T, rowNo, colCount, Low, High, colNo + 1);
}

// Заповнення всіх рядків матриці
void CreateRows(int** T, const int rowCount, const int colCount, const int Low,
    const int High, int rowNo)
{
    CreateRow(T, rowNo, colCount, Low, High, 0);
    if (rowNo < rowCount - 1)
        CreateRows(T, rowCount, colCount, Low, High, rowNo + 1);
}

// Виведення поточного рядка
void PrintRow(int** T, const int rowNo, const int colCount, int colNo)
{
    cout << setw(4) << T[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(T, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

// Виведення всіх рядків матриці
void PrintRows(int** T, const int rowCount, const int colCount, int rowNo)
{
    if (rowNo == 0)
        cout << endl;
    PrintRow(T, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(T, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

// Обмін двох рядків місцями (по елементах)
void Change(int** T, const int row1, const int row2, const int colCount,
    int colNo)
{
    int tmp = T[row1][colNo];
    T[row1][colNo] = T[row2][colNo];
    T[row2][colNo] = tmp;
    if (colNo < colCount - 1)
        Change(T, row1, row2, colCount, colNo + 1);
}

// Один прохід «бульбашки» (внутрішній цикл)
// Ключі впорядкування: ↑ ↓ ↑
void SortPass(int** T, const int rowCount, const int colCount, const int i0,
    int i1)
{
    if (i1 < rowCount - i0 - 1)
    {
        if ((T[i1][0] > T[i1 + 1][0])
            ||
            (T[i1][0] == T[i1 + 1][0] &&
                T[i1][1] < T[i1 + 1][1])
            ||
            (T[i1][0] == T[i1 + 1][0] &&
                T[i1][1] == T[i1 + 1][1] &&
                T[i1][2] > T[i1 + 1][2]))
            Change(T, i1, i1 + 1, colCount, 0);

        SortPass(T, rowCount, colCount, i0, i1 + 1);
    }
}

// Впорядкування рядків (зовнішній цикл)
void Sort(int** T, const int rowCount, const int colCount, int i0)
{
    if (i0 < rowCount - 1)
    {
        SortPass(T, rowCount, colCount, i0, 0);
        Sort(T, rowCount, colCount, i0 + 1);
    }
}

// Критерій: всі, крім додатних кратних 5
void CalcRow(int** T, const int rowNo, const int colCount, int& S, int& k,
    int colNo)
{
    if (!(T[rowNo][colNo] > 0 && T[rowNo][colNo] % 5 == 0))
    {
        S += T[rowNo][colNo];
        k++;
        T[rowNo][colNo] = 0;
    }
    if (colNo < colCount - 1)
        CalcRow(T, rowNo, colCount, S, k, colNo + 1);
}

void CalcRows(int** T, const int rowCount, const int colCount, int& S, int& k,
    int rowNo)
{
    CalcRow(T, rowNo, colCount, S, k, 0);
    if (rowNo < rowCount - 1)
        CalcRows(T, rowCount, colCount, S, k, rowNo + 1);
}


int main()
{
    srand((unsigned)time(NULL));

    int Low = -42;
    int High = 51;

    int rowCount = 7;
    int colCount = 6;

    int** T = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        T[i] = new int[colCount];

    CreateRows(T, rowCount, colCount, Low, High, 0);
    PrintRows(T, rowCount, colCount, 0);
    Sort(T, rowCount, colCount, 0);
    PrintRows(T, rowCount, colCount, 0);

    int S = 0;
    int k = 0;
    CalcRows(T, rowCount, colCount, S, k, 0);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    PrintRows(T, rowCount, colCount, 0);

    for (int i = 0; i < rowCount; i++)
        delete[] T[i];
    delete[] T;

    return 0;
}