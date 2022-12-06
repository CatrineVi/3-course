#pragma once
#include"String.h"
#include "operators.h"

void ModifyObject(String& s)
{
	String a;
	while (true)
	{
		system("cls");
		int choice;
		cout << "1) adding string \n2) repeating symbol \n3) cuting off string \n4) substring search\n"
			"5) filling with a substring \n6) comparison on inequality \n7) checking for emptiness\n"
			"8) flipping a line \n9) string lenght \n10) printing \n0) exit\n";
		cin >> choice;
		if (choice == 1)
		{
			cout << "enter new string: "; cin >> a;
			s = s + a;
		}
		else if (choice == 2)
			s += s;
		else if (choice == 3)
		{
			cout << "what do you want to cut off?: "; cin >> a;
			s -= a;
		}
		else if (choice == 4)
		{
			cout << "what are you looking for?: "; cin >> a;
			if (s * a >= 0)
				cout << "string has " << a.getSTR() << endl;
			else cout << "string hasn't " << a.getSTR() << endl;
			system("pause");
		}
		else if (choice == 5)
		{
			cout << "enter new string: "; cin >> a;
			s *= a;
		}
		else if (choice == 6)
		{
			cout << "enter new string: "; cin >> a;
			if (s == a)
				cout << "strings are the same\n";
			else if (s != a)
				cout << "strings aren't the same\n";
			system("pause");
		}
		else if (choice == 7)
		{
			if (!s) cout << "string is empty\n";
			else cout << "strings isn't empty\n";
			system("pause");
		}
		else if (choice == 8)
			s = ~s;
		else if (choice == 9) {
			cout << "string lenght = " << (int)s << endl;
			system("pause");
		}
		else if (choice == 10) {
			cout << s << endl;
			system("pause");
		}
		else if (choice == 0)
		{
			exit(0); break;
		}
	}
}