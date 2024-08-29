#include <iostream>
#include <fstream>
#include <tchar.h>
#include <conio.h>
#include <stdlib.h>
#include <locale>

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
    int GetLen() { return tos; }
    int GetCurrent(int cnt) { return stck[tos - 1 - cnt]; }
};
Stack st(10), repeat(10);
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
    wchar_t FileName[100], ch;
    std::wstring str;
    int **G, v, s, t, i, j, cnt, tmp, *V, first = 0, *repeat, check;
    std::wcout << L"Введите имя файла: ";
    std::wcin >> FileName;
    std::wifstream fin(FileName);
    if (!fin)
    {
        std::wcout << L"Неверное имя! Программа завершает работу.";
        _getch();
        exit(1);
    }
    std::getline(fin, str);
    v = str.length();
    fin.close();
    G = new int *[v];
    V = new int[v];
    fin.open(FileName);
    for (i = 0; i < v; i++)
        G[i] = new int[v];
    std::wcout << L"Матрица смежностей: " << std::endl;
    for (i = 0; i < v; i++)
    {
        V[i] = 0;
        for (j = 0; j < v; j++)
        {
            fin.get(ch);
            G[i][j] = ch - L'0';
            std::cout << G[i][j] << " ";
        }
        fin.get(ch);
        std::cout << std::endl;
    }
    fin.close();
    std::wcout << L"Введите первую вершину: ";
    std::wcin >> s;
    std::wcout << L"Введите вторую вершину: ";
    std::wcin >> t;
    st.push(t);
    tmp = v + 1;
    V[t - 1] = 1;
    std::wcout << L"Пути: " << std::endl;
    while (1)
    {
        for (i = 0; i < v; i++)
        {
            if (st.GetCurrent(0) == s)
                break;
            if (G[st.GetCurrent(0) - 1][i] == 1 && V[i] == 0)
            {
                if (i == tmp - 1)
                {
                    tmp = v + 1;
                    continue;
                }
                st.push(i + 1);
                V[i] = 1;
                break;
            }
            if (V[i] == 1 && st.GetCurrent(0) != t)
            {
                tmp = st.pop();
            }
            if (V[i] == 1 && st.GetCurrent(0) == t)
            {
                for (i = 0; i < v; i++)
                {
                    V[i] = 0;
                }
            }
        }
        if (st.GetCurrent(0) == s)
        {
            cnt = st.GetLen();
            if (first == 0)
            {
                first = 1;
                repeat = new int[st.GetLen()];
                check = st.GetLen();
                for (i = 0; i < st.GetLen(); i++)
                {
                    repeat[i] = st.GetCurrent(cnt - i);
                }
            }
            else
            {
                if (check == cnt)
                    for (i = 0; i < cnt; i++)
                    {
                        if (repeat[i] == st.GetCurrent(cnt - i))
                            first = 2;
                        else
                        {
                            first = 1;
                            break;
                        }
                    }
            }
            if (first != 2)
            {
                for (i = 0; i < cnt; i++)
                {
                    std::wcout << st.GetCurrent(i) << " ";
                }
                std::wcout << std::endl;
                V[(tmp = st.pop()) - 1] = 0;
            }
        }
        if (first == 2)
            break;
    }
    for (i = 0; i < v; i++)
        delete[] G[i];
    delete[] repeat;
    delete[] G;
    delete[] V;

    _getch();
}
