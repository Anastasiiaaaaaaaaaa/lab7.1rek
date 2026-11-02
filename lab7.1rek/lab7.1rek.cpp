#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void CreateRow(int** a, const int rowNo, const int colCount, const int Low, const int High, int colNo);
void CreateRows(int** a, const int rowCount, const int colCount, const int Low, const int High, int rowNo);

void PrintRow(int** a, const int rowNo, const int colCount, int colNo);
void PrintRows(int** a, const int rowCount, const int colCount, int rowNo);

void ChangeRow(int** a, const int row1, const int row2, const int colCount, int colNo);
void Change(int** a, const int row1, const int row2, const int colCount);
void Sort(int** a, const int rowCount, const int colCount, int i0, int i1);

void CalcRow(int** a, const int rowNo, const int colCount, int colNo, int& S, int& k);
void CalcRows(int** a, const int rowCount, const int colCount, int rowNo, int& S, int& k);

int main()
{
    srand((unsigned)time(NULL));

    
    int Low = -42;
    int High = 51;
    int rowCount = 7;
    int colCount = 6;

    // Динамічне виділення пам'яті під матрицю T
    int** t = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        t[i] = new int[colCount];

    // 1. Рекурсивне формування та виведення початкової матриці
    CreateRows(t, rowCount, colCount, Low, High, 0);
    cout << "Initial Matrix T:" << endl;
    PrintRows(t, rowCount, colCount, 0);

    // 2. Рекурсивне впорядкування за ключами ↑ ↓ ↑ та виведення
    Sort(t, rowCount, colCount, 0, 0);
    cout << "Sorted Matrix T (keys: ^ v ^):" << endl;
    PrintRows(t, rowCount, colCount, 0);

    // 3. Рекурсивне обчислення за критерієм та заміна нулями
    int S = 0;
    int k = 0;
    CalcRows(t, rowCount, colCount, 0, S, k);

    // 4. Виведення результатів та модифікованої матриці
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    cout << "Modified Matrix T (with zeros):" << endl;
    PrintRows(t, rowCount, colCount, 0);

    // Звільнення пам'яті
    for (int i = 0; i < rowCount; i++)
        delete[] t[i];
    delete[] t;

    return 0;
}

// Рекурсивне формування елементів поточного рядка
void CreateRow(int** a, const int rowNo, const int colCount, const int Low, const int High, int colNo)
{
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < colCount - 1)
        CreateRow(a, rowNo, colCount, Low, High, colNo + 1);
}

// Рекурсивне формування всіх рядків матриці
void CreateRows(int** a, const int rowCount, const int colCount, const int Low, const int High, int rowNo)
{
    CreateRow(a, rowNo, colCount, Low, High, 0);
    if (rowNo < rowCount - 1)
        CreateRows(a, rowCount, colCount, Low, High, rowNo + 1);
}

// Рекурсивне виведення елементів поточного рядка
void PrintRow(int** a, const int rowNo, const int colCount, int colNo)
{
    cout << setw(5) << a[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

// Рекурсивне виведення всіх рядків матриці
void PrintRows(int** a, const int rowCount, const int colCount, int rowNo)
{
    PrintRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

// Рекурсивний обмін елементів двох рядків
void ChangeRow(int** a, const int row1, const int row2, const int colCount, int colNo)
{
    int tmp = a[row1][colNo];
    a[row1][colNo] = a[row2][colNo];
    a[row2][colNo] = tmp;

    if (colNo < colCount - 1)
        ChangeRow(a, row1, row2, colCount, colNo + 1);
}

void Change(int** a, const int row1, const int row2, const int colCount)
{
    ChangeRow(a, row1, row2, colCount, 0);
}

// Рекурсивне сортування рядків 
void Sort(int** a, const int rowCount, const int colCount, int i0, int i1)
{
   
    if ((a[i1][0] > a[i1 + 1][0]) ||
        (a[i1][0] == a[i1 + 1][0] && a[i1][1] < a[i1 + 1][1]) ||
        (a[i1][0] == a[i1 + 1][0] && a[i1][1] == a[i1 + 1][1] && a[i1][2] > a[i1 + 1][2]))
    {
        Change(a, i1, i1 + 1, colCount);
    }

    if (i1 < rowCount - i0 - 2)
    {
        Sort(a, rowCount, colCount, i0, i1 + 1);
    }
    else if (i0 < rowCount - 2)
    {
        Sort(a, rowCount, colCount, i0 + 1, 0);
    }
}

// Рекурсивне обчислення елементів поточного рядка]
void CalcRow(int** a, const int rowNo, const int colCount, int colNo, int& S, int& k)
{
    // Перевірка критерію: НЕ є додатним і кратним 5
    if (!(a[rowNo][colNo] > 0 && a[rowNo][colNo] % 5 == 0))
    {
        S += a[rowNo][colNo];
        k++;
        a[rowNo][colNo] = 0;
    }

    if (colNo < colCount - 1)
        CalcRow(a, rowNo, colCount, colNo + 1, S, k);
}

// Рекурсивна обробка всіх рядків для обчислення та обнулення
void CalcRows(int** a, const int rowCount, const int colCount, int rowNo, int& S, int& k)
{
    CalcRow(a, rowNo, colCount, 0, S, k);
    if (rowNo < rowCount - 1)
        CalcRows(a, rowCount, colCount, rowNo + 1, S, k);
}