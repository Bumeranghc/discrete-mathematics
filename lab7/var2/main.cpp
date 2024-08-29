#include <fstream>
#include <iostream>
#include <tchar.h>
#include <conio.h>
#include <stdlib.h>
#include <locale>
#include <process.h>
void sort(int *item, wchar_t *letters, int count);

int _tmain(int argc, _TCHAR* argv[])
{
    std::setlocale(LC_ALL, "Russian");
    system("cls");

    wchar_t FileName[100];
    std::wstring str;
    int i, j, k, c, tmp, repeat, rpt, cnt;
    int *V, **C, **K;
    wchar_t *G;
    int *l, *length, *tmpstr;

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
    std::wcout << L"Первая строка файла:\n" << str << L"\n-=Кодирование алгоритмом Хаффмена=-\n";
    c = str.length();

    i=0;
    tmp=0;

    while (i!=c)
    {
        repeat=0;
        for (j=0; j<i; j++)
        {
            if (str[i]==str[j])
            {
                repeat=1;
                break;
            }
        }
        if (repeat==1)
        {
            i++;
            continue;
        }
        for (j=i; j<c; j++)
        {
            if (str[i]==str[j])
            {
                tmp++;
                break;
            }
        }
        i++;
    }
    rpt=tmp;
    V=new int[rpt];
    G=new wchar_t[rpt];
    C=new int*[rpt];
    K=new int*[rpt];
    l=new int[rpt];
    length=new int[rpt];
    tmpstr=new int[rpt-1];
    for (i=0; i<rpt; i++)
    {
        K[i]=new int[rpt-1];
        C[i]=new int[rpt-1];
    }
    cnt=0;
    i=0;
    while (i!=c)
    {
        tmp=0;
        repeat=0;
        for (j=0; j<i; j++)
        {
            if (str[i]==str[j])
            {
                repeat=1;
                break;
            }
        }
        if (repeat==1)
        {
            i++;
            continue;
        }
        for (j=i; j<c; j++)
        {
            if (str[i]==str[j]) tmp++;
        }
        V[cnt]=tmp;
        G[cnt]=str[i];
        cnt++;
        i++;
    }

    std::wcout<<L"Массив вероятностей букв:\n";

    sort(V, G, rpt);

    for (i=0; i<rpt; i++)
    std::cout<<G[i]<<" ";
    std::cout<<std::endl;
    for (i=0; i<rpt; i++)
    {
        std::cout<<V[i]<<" ";
        for (j=0; j<rpt-1; j++)
        {
            C[i][j]=V[i];
        }
    }
 	std::wcout<<std::endl<<L"Коды: ";

    cnt=rpt-1;
    for (i=0; i<rpt-2; i++)
    {
        tmp=C[cnt-1][i]+C[cnt][i];
        for (j=0; j<cnt; j++)
        {
            if (tmp>=C[j][i])
            {
                l[i]=j;
                break;
            }
        }
        C[l[i]][i+1]=tmp;
        for (j=l[i]+1; j<cnt; j++)
        {
            C[j][i+1]=C[j-1][i];
        }
        cnt--;
    }

    for (i=0; i<rpt; i++)
    for (j=0; j<rpt-1; j++) K[i][j]=2;

    cnt=1;

    K[0][0]=0;
    K[1][0]=1;

    for (k=rpt-3; k>-1; k--)
    {
            repeat=0;
            for (i=0; i<rpt-1; i++)
            {
                tmpstr[i]=K[l[k]][i];
            }
            for (i=l[k]; i<cnt; i++)
            {
                for (j=0; j<rpt-1; j++)
                {
                    K[i][j]=K[i+1][j];
                }
            }
            for (i=0; i<rpt-1; i++)
            {
                if (tmpstr[i]==2&&repeat!=1)
                {
                    repeat=1;
                    K[cnt][i]=0;
                    K[cnt+1][i]=1;
                }
                else
                {
                    K[cnt][i]=tmpstr[i];
                    K[cnt+1][i]=tmpstr[i];
                }
            }
            cnt++;
        }

    std::cout<<std::endl;
    for (i=0; i<rpt; i++)
    {
        std::wcout<<G[i]<<": ";
        for (j=0; j<rpt-1; j++)
        {
            if (K[i][j]!=2) std::wcout<<K[i][j]<<" ";
            else break;
        }
        std::wcout<<std::endl;
    }
    std::wcout<<L"Закодированный текст:"<<std::endl;
    cnt=0;
    for (i=0; i<c; i++)
    {
        for (j=0; j<rpt; j++)
        {
            if (str[i]==G[j])
            {
                cnt=j;
                break;
            }
        }
        for (j=0; j<rpt-1; j++)
        {
            if(K[cnt][j]==2) break;
            std::wcout<<K[cnt][j];
        }
        std::wcout<<L" ";
    }
    delete[] V;
    delete[] G;
    for (i=0; i<rpt-1; i++)
    {
        delete []C[i];
        delete []K[i];
    }
    delete[] C;
    delete[] l;
    delete[] K;
    delete[] length;
    delete[] tmpstr;
    _getch();
}

void sort(int *item, wchar_t *letters, int count)
{
    int i, j;
    int t;
    wchar_t tmp;
    for(i = 0; i < count; i++)
    {
        for(j = count-1; j > i; j--)
        {
        if(item[j-1] < item[j])
            {
                t = item[j-1];
                tmp = letters[j-1];
                item[j-1] = item[j];
                letters[j-1] = letters[j];
                letters[j] = tmp;
                item[j] = t;
            }
            if(item[j-1] == item[j])
            {
                if (letters[j-1] > letters[j])
                {
                        tmp = letters[j-1];
                        letters[j-1] = letters[j];
                        letters[j] = tmp;
                }
            }
        }
    }
}
