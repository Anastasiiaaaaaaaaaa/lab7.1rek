#include "pch.h"
#include "CppUnitTest.h"
#include "../lab7.1rek/lab7.1rek.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest71Rec
{
    TEST_CLASS(UnitTest71Rec)
    {
    public:

        TEST_METHOD(TestCalcRows)
        {
            const int rowCount = 2;
            const int colCount = 2;

            // Виділення пам'яті під тестову матрицю 2x2
            int** t = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
                t[i] = new int[colCount];

            // Заповнення тестовими значеннями:
            //  5  -> додатне кратне 5 (ІГНОРУЄТЬСЯ)
            // -10 -> від'ємне (ВРАХОВУЄТЬСЯ, замінюється на 0)
            //  3  -> додатне не кратне 5 (ВРАХОВУЄТЬСЯ, замінюється на 0)
            // 15  -> додатне кратне 5 (ІГНОРУЄТЬСЯ)
            t[0][0] = 5;
            t[0][1] = -10;
            t[1][0] = 3;
            t[1][1] = 15;

            int S = 0;
            int k = 0;

            // Виклик рекурсивної функції з початкового рядка 0
            CalcRows(t, rowCount, colCount, 0, S, k);

            // 1. Перевірка обчисленої суми (-10 + 3 = -7)
            Assert::AreEqual(-7, S);

            // 2. Перевірка кількості порахованих елементів (k = 2)
            Assert::AreEqual(2, k);

            // 3. Перевірка коректності обнулення в матриці
            Assert::AreEqual(5, t[0][0]);   // не підпадало під критерій — залишилося 5
            Assert::AreEqual(0, t[0][1]);   // підпадало — обнулено
            Assert::AreEqual(0, t[1][0]);   // підпадало — обнулено
            Assert::AreEqual(15, t[1][1]);  // не підпадало — залишилося 15

            // Звільнення пам'яті
            for (int i = 0; i < rowCount; i++)
                delete[] t[i];
            delete[] t;
        }
    };
}