#pragma once
#include "Palette.h"

using namespace std;

void modifyPalette(Palette pal)
{
	while (true)
	{
		int choice;
		system("cls");
		cout << "1) setting the start index \n2) changing the item by index"
			"\n3) sorting \n4) conversion to RGB \n5) palette output \n0) exit" << endl;
		cin >> choice;
		if (choice == 1)
		{
			system("cls");
			cout << "diaposone before: [" << pal.getIndex() << ", " << pal.getIndex() + pal.getSize() - 1 << "]" << endl;
			pal.print();
			int indBefore = pal.getIndex();
			//Palette pal_before = pal;
			int index;
			cout << "Enter the index: ";
			cin >> index;
			pal.setIndex(index);
			//pal = pal_before;
			cout << "diaposone after: [" << pal.getIndex() << ", " << pal.getIndex() + pal.getSize() - 1 << "]" << endl;
			pal.print();
			system("pause");
		}
		else if (choice == 2)
		{
			system("cls");
			int index;
			cout << "Enter the index for editig: ";
			cin >> index;
			pal.ModifyElement(index - pal.getIndex());
		}
		else if (choice == 3)
		{
			system("cls");
			int ch;
			cout << "1) sort in ascending order \n2) sort in descending oreder" << endl;
			cin >> ch;
			if (ch == 1)
				pal.sortInAscendingOrder();
			else if (ch == 2)
				pal.sortInDescendingOreder();
			else
				cout << "There is no such command." << endl;
		}
		else if (choice == 4)
		{
			system("cls");
			int index;
			cout << "Enter the index for conversion to RGB: ";
			cin >> index;
			pal.toRGB(index-pal.getIndex());
		}
		else if (choice == 5)
		{
			system("cls");
			pal.print();
			system("pause");
		}			
		else if (choice == 0)
		{
			exit(0);
			break;
		}
		else
			cout << "There is no such command. Try again." << endl;
	}
}