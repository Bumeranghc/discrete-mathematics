#include <iostream>
#include <tchar.h>
#include <conio.h>
#include <stdlib.h>
#include <locale>

int _tmain(int argc, _TCHAR *argv[])
{
    std::setlocale(LC_ALL, "Russian");
    system("cls");
    int i, j, cnt, V, *T, *H, **G, s, t, *X, v, max, m;
    std::wcout << L"Введите количество вершин: ";
    std::wcin >> V;
    T = new int[V];
    G = new int *[V];
    H = new int[V];
    X = new int[V];
    for (i = 0; i < V; i++)
        G[i] = new int[V];
    system("cls");
    std::wcout << L"Введите матрицу смежностей графа: \n";
    cnt = 2;
    max = 0;
    for (i = 0; i < V; i++)
    {
        for (j = 0; j < V; j++)
        {
            gotoxy(j + cnt, i + 2);
            std::wcin >> G[i][j];
            cnt++;
            if (G[i][j] < 0)
            {
                j--;
                cnt--;
            }
            max = max + G[i][j];
        }
        cnt = 2;
    }
    for (i = 0; i < V; i++)
    {
        T[i] = max + 1;
        H[i] = 0;
        X[i] = 0;
    }
    std::wcout << L"Введите V1: ";
    std::wcin >> s;
    std::wcout << L"Введите V2: ";
    std::wcin >> t;
    H[s - 1] = 0;
    T[s - 1] = 0;
    X[s - 1] = 1;
    v = s;
    cnt = 0;
    while (1)
    {
        for (i = 0; i < V; i++)
        {
            if (X[i] == 0 && T[i] > (T[v - 1] + G[v - 1][i]) && G[v - 1][i] != 0)
            {
                T[i] = T[v - 1] + G[v - 1][i];
                H[i] = v;
            }
        }
        m = max + 1;
        v = 0;
        for (i = 0; i < V; i++)
        {
            if (X[i] == 0 && T[i] < m)
            {
                v = i + 1;
                m = T[i];
                cnt++;
            }
        }
        if (v == 0 || v == t)
            break;
        X[v - 1] = 1;
    }
    std::wcout << std::endl;
    int temp = t;
    cnt = 0;
    while (1)
    {
        X[cnt] = temp;
        temp = H[temp - 1];
        cnt++;
        if (temp == s)
        {
            X[cnt] = s;
            break;
        }
    }
    std::wcout << L"Путь: ";
    for (i = cnt; i > -1; i--)
    {
        std::wcout << X[i] << L" ";
    }
    std::wcout << std::endl;
    std::wcout << L"Длина пути: ";
    std::wcout << T[t - 1] << " ";
    delete[] T;
    delete[] H;
    delete[] X;
    for (i = 0; i < V; i++)
        delete[] G[i];
    delete[] G;
    _getch();
}
