#include <iostream>
#include <tchar.h>
#include <conio.h>
#include <stdlib.h>
#include <locale>

int n;
class Stack
{
protected:
    int *stck;
    int tos;
    int length;

public:
    Stack(int size);
    ~Stack() { delete[] stck; }
    void push(int item);
    int pop();
    int GetLen() { return length; }
    int GetCurrent() { return tos; }
};

Stack ::Stack(int size)
{
    stck = new int[size];
    if (!stck)
    {
        return;
    }
    length = size;
    tos = 0;
}
void Stack::push(int item)
{
    if (tos == length)
    {
        return;
    }
    stck[tos] = item;
    tos++;
}
int Stack ::pop()
{
    if (tos == 0)
    {
        return 0;
    }
    tos--;
    return stck[tos];
}

int _tmain(int argc, _TCHAR *argv[])
{
    std::setlocale(LC_ALL, "Russian");
    system("cls");
    int V, *x, i, j, **G, v, u, **G2, cnt;
    std::wcout << L"Введите количество вершин: ";
    std::cin >> V;
    Stack T(V);
    x = new int[V];
    G = new int *[V];
    for (i = 0; i < V; i++)
        G[i] = new int[V];
    G2 = new int *[V];
    for (i = 0; i < V; i++)
        G2[i] = new int[V];
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            G2[i][j] = 0;

    system("cls");
    std::wcout << L"Введите матрицу смежностей графа: \n";
    cnt = 2;
    for (i = 0; i < V; i++)
    {
        for (j = 0; j < V; j++)
        {
            gotoxy(j + cnt, i + 2);
            std::wcin >> G[i][j];
            cnt++;
            if (G[i][j] > 1 || G[i][j] < 0)
            {
                j--;
                cnt--;
            }
        }
        cnt = 2;
    }

    system("cls");
    std::wcout << std::endl << L"Введите вершину начала обхода: ";
    std::wcin >> v;
    v--;

    for (i = 0; i < V; i++)
        x[i] = 0;

    T.push(v);
    x[v] = 1;

    while (T.GetCurrent() != 0)
    {
        u = T.pop();
        for (i = 0; i < V; i++)
        {
            if (G[u][i] == 1 && x[i] == 0)
            {
                T.push(i);
                x[i] = 1;
                G2[u][i] = 1;
                G2[i][u] = 1;
                break;
            }
        }
    }

    std::wcout << std::endl << L"Матрица смежностей поиска в глубину:" << std::endl;
    for (i = 0; i < V; i++)
    {
        for (j = 0; j < V; j++)
            std::wcout << " " << G2[i][j];
        std::wcout << std::endl;
    }
    for (i = 0; i < V; i++)
        delete[] G[i];
    delete[] G;
    for (i = 0; i < V; i++)
        delete[] G2[i];
    delete[] G2;
    delete[] x;

    _getch();
    return 0;
}
