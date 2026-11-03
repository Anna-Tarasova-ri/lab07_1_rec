// UnitTest_7_1_rec.cpp
// Unit-тест до лабораторної роботи № 7.1 (рекурсивний спосіб)
// Варіант 27

#include "pch.h"
#include "CppUnitTest.h"
#include "../PR7_1_rec/pr7_1_rec.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest71rec
{
    // створює матрицю rowCount x colCount зі значень data (по рядках)
    int** MakeMatrix(const int rowCount, const int colCount, const int* data)
    {
        int** T = new int* [rowCount];
        for (int i = 0; i < rowCount; i++)
        {
            T[i] = new int[colCount];
            for (int j = 0; j < colCount; j++)
                T[i][j] = data[i * colCount + j];
        }
        return T;
    }

    void FreeMatrix(int** T, const int rowCount)
    {
        for (int i = 0; i < rowCount; i++)
            delete[] T[i];
        delete[] T;
    }

    // порівнює матрицю T з очікуваними значеннями expected
    void AssertMatrix(int** T, const int rowCount, const int colCount,
        const int* expected)
    {
        for (int i = 0; i < rowCount; i++)
            for (int j = 0; j < colCount; j++)
                Assert::AreEqual(expected[i * colCount + j], T[i][j]);
    }

    TEST_CLASS(UnitTest71rec)
    {
    public:

        // Calc: змішані значення (додатні кратні 5, від'ємні кратні 5, нуль)
        TEST_METHOD(CalcTest)
        {
            const int rowCount = 3, colCount = 3;
            int data[] = { 5, -5, 10,
                            0,  7, 15,
                           -3, 20,  9 };
            int expected[] = { 5, 0, 10,
                               0, 0, 15,
                               0, 20, 0 };
            int** T = MakeMatrix(rowCount, colCount, data);

            int S = 0, k = 0;
            CalcRows(T, rowCount, colCount, S, k, 0);

            Assert::AreEqual(8, S);   // -5 + 0 + 7 - 3 + 9
            Assert::AreEqual(5, k);
            AssertMatrix(T, rowCount, colCount, expected);

            FreeMatrix(T, rowCount);
        }

        // Calc: усі елементи – додатні кратні 5, жоден не підходить
        TEST_METHOD(CalcAllPositiveMultiplesOf5Test)
        {
            const int rowCount = 3, colCount = 3;
            int data[] = { 5, 10, 15,
                           20, 25, 30,
                           35, 40, 45 };
            int** T = MakeMatrix(rowCount, colCount, data);

            int S = 0, k = 0;
            CalcRows(T, rowCount, colCount, S, k, 0);

            Assert::AreEqual(0, S);
            Assert::AreEqual(0, k);
            AssertMatrix(T, rowCount, colCount, data);   // матриця не змінилась

            FreeMatrix(T, rowCount);
        }

        // Calc: жодного додатного кратного 5, підходять усі елементи
        TEST_METHOD(CalcNoPositiveMultiplesOf5Test)
        {
            const int rowCount = 3, colCount = 3;
            int data[] = { 1,   2,  3,
                          -5, -10,  0,
                           7,  -1, 14 };
            int expected[] = { 0, 0, 0,
                               0, 0, 0,
                               0, 0, 0 };
            int** T = MakeMatrix(rowCount, colCount, data);

            int S = 0, k = 0;
            CalcRows(T, rowCount, colCount, S, k, 0);

            Assert::AreEqual(11, S);
            Assert::AreEqual(9, k);
            AssertMatrix(T, rowCount, colCount, expected);

            FreeMatrix(T, rowCount);
        }

        // Change: обмін першого й останнього рядків
        TEST_METHOD(ChangeTest)
        {
            const int rowCount = 3, colCount = 3;
            int data[] = { 1, 2, 3,
                           4, 5, 6,
                           7, 8, 9 };
            int expected[] = { 7, 8, 9,
                               4, 5, 6,
                               1, 2, 3 };
            int** T = MakeMatrix(rowCount, colCount, data);

            Change(T, 0, 2, colCount, 0);

            AssertMatrix(T, rowCount, colCount, expected);

            FreeMatrix(T, rowCount);
        }

        // Sort: ключі ↑ ↓ ↑ (1-й стовпчик за зростанням, 2-й за спаданням,
        // 3-й за зростанням); 4-й стовпчик – мітка, щоб перевірити,
        // що рядки переставляються цілком
        TEST_METHOD(SortTest)
        {
            const int rowCount = 5, colCount = 4;
            int data[] = { 5, 1, 9, 100,
                           2, 3, 4, 101,
                           5, 4, 1, 102,
                           5, 4, 0, 103,
                           2, 3, 1, 104 };
            int expected[] = { 2, 3, 1, 104,
                               2, 3, 4, 101,
                               5, 4, 0, 103,
                               5, 4, 1, 102,
                               5, 1, 9, 100 };
            int** T = MakeMatrix(rowCount, colCount, data);

            Sort(T, rowCount, colCount, 0);

            AssertMatrix(T, rowCount, colCount, expected);

            FreeMatrix(T, rowCount);
        }
    };
}