#include <iostream>
#include <tchar.h>
#include <conio.h>
#include <stdlib.h>
#include <locale>

int _tmain(int argc, _TCHAR *argv[])
{
    std::setlocale(LC_ALL, "Russian");
    system("cls");

    int a, b, i, j, c, **matrix1, **matrix2, count = 0, f, re, m;
    int **array;
    std::wcout << L"Введите количество маршрутов: ";
    std::wcin >> a;
    std::wcout << L"Введите количество остановок: ";
    std::wcin >> b;

    array = new int *[a];
    for (i = 0; i < a; i++)
        array[i] = new int[b];
    for (i = 0; i < a; i++)
        matrix1 = new int *[b];
    for (c = 0; c < b; c++)
        matrix1[c] = new int[20];
    for (c = 0; c < b; c++)
        for (j = 0; j < 20; j++)
            matrix1[c][j] = 0;

    system("cls");
    for (i = 0; i < a; i++)
    {
        std::wcout << L"Введите " << i + 1 << L" маршрут, указывая номера остановок через Enter, чтобы закончить ввод, введите опять номер самой первой остановки: " << std::endl;
        for (j = 0; j < 20; j++)
        {
            std::wcin >> array[i][j];
            if (array[i][j] == array[i][0] && j > 1)
            {
                count = count + j;
                system("cls");
                break;
            }
        }

        for (c = 1; c < j; c++)
        {
            matrix1[array[i][c - 1] - 1][array[i][c] - 1] = 1;
            matrix1[array[i][c] - 1][array[i][c - 1] - 1] = 1;
        }
    }
    system("cls");
    std::wcout << L"Матрица смежности: " << std::endl;
    for (c = 0; c < b; c++)
    {
        for (j = 0; j < b; j++)
            std::wcout << matrix1[c][j] << ", ";
        std::wcout << std::endl;
    }

    int **edge;
    edge = new int *[count];
    for (i = 0; i < count; i++)
        edge[i] = new int[2];

    int cnt = 0;

    for (i = 0; i < a; i++)
    {
        for (j = 0; j < b; j++)
        {
            if (array[i][j] == array[i][0] && j > 1)
                break;
            edge[cnt][0] = array[i][j];
            edge[cnt][1] = array[i][j + 1];
            cnt++;
        }
    }

    int **edge2;
    edge2 = new int *[cnt];
    for (i = 0; i < cnt; i++)
        edge2[i] = new int[2];

    int cnt2 = 0;
    for (j = 0; j < cnt; j++)
    {
        if (matrix1[edge[j][0] - 1][edge[j][1] - 1] == 1)
        {
            re = 0;
            for (m = 0; m < cnt2; m++)
            {
                if ((edge[j][0] == edge2[m][0] && edge[j][1] == edge2[m][1]) ||
                    (edge[j][0] == edge2[m][1] && edge[j][1] == edge2[m][0]))
                {
                    re = 1;
                    break;
                }
            }
            if (re == 0)
            {
                edge2[cnt2][0] = edge[j][0];
                edge2[cnt2][1] = edge[j][1];
                cnt2++;
            }
        }
    }

    matrix2 = new int *[b];
    for (c = 0; c < b; c++)
        matrix2[c] = new int[cnt2];

    for (c = 0; c < b; c++)
    {
        for (j = 0; j < cnt2; j++)
            matrix2[c][j] = 0;
    }

    for (i = 0; i < cnt2; i++)
    {
        matrix2[edge2[i][0] - 1][i] = 1;
        matrix2[edge2[i][1] - 1][i] = 1;
    }

    std::wcout << L"Матрица инцидентности: " << std::endl;
    for (c = 0; c < b; c++)
    {
        for (f = 0; f < cnt2; f++)
        {
            std::wcout << matrix2[c][f] << ", ";
        }
        std::wcout << std::endl;
    }

    for (c = 0; c < b; c++)
        delete[] matrix1[c];
    delete[] matrix1;

    for (c = 0; c < b; c++)
        delete[] matrix2[c];
    delete[] matrix2;

    for (i = 0; i < a; i++)
        delete[] array[i];
    delete[] array;

    for (i = 0; i < count; i++)
        delete[] edge[i];
    delete[] edge;

    for (i = 0; i < cnt2; i++)
        delete[] edge2[i];
    delete[] edge2;

    _getch();
}
