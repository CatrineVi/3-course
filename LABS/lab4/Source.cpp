#include "String.h"
#include "operators.h"
#include "Modify.h"

int main()
{
	String s;	
	cout << "create new string: "; cin >> s;
	int choice;
	ModifyObject(s);
	return 0;
}