#include <iostream>
#include <tchar.h>
#include <conio.h>
#include <stdlib.h>
#include <locale>

int _tmain(int argc, _TCHAR* argv[])
{
    std::setlocale(LC_ALL, "Russian");
	system("cls");
	int base;
	wchar_t num1[256], *endptr;
	std::wcout<<L"Введите число для конвертации: ";
	std::wcin>>num1;
	std::wcout<<L"Введите систему счисления заданного числа: ";
	std::wcin>>base;
	long result=std::wcstol(num1, &endptr, base);
	std::wcout<<L"Выполнен перевод заданного числа в десятичную систему счисления: "<< result;
    _getch();
}
