#pragma once
#include "String.h"
#include <algorithm>

String operator+(String& a, String& b)
{
	String s;
	string str = a.getSTR() + b.getSTR();
	s.setSTR(str);
	return s;
}

String operator+=(String& a, String& b)
{
	a = a + b;
	return a;
}

String operator-(String& a, String& b)
{
	String s;
	string str;
	if (a*b>=0)
		str = a.getSTR().erase(a.getSTR().rfind(b.getSTR()));
	else
	{
		cout << "not found" << endl;
		str = a.getSTR();
	}
	s.setSTR(str);
	return s;
}

String operator-=(String& a, String& b)
{
	a = a - b;
	return a;
}

int operator*(String& a, String& b)
{
	int n = a.getSTR().find(b.getSTR());
	return n;
}

String operator*=(String& a, String& b)
{
	a.setSTR(b.getSTR());
	return a;
}
bool operator==(String& a, String& b)
{
	if (a.getSTR() == b.getSTR())
		return true;
	else return false;
}

bool operator!=(String& a, String& b)
{
	if (a.getSTR() != b.getSTR())
		return true;
	else return false;
}
bool operator!(String& a)
{
	if (!a.getSTR().size())
		return true;
	else return false;
}

String operator~(String& s)
{	
	string str;
	for (int i = (int)s - 1; i >= 0; i--)
		str.push_back(s.getSTR()[i]);
	s.setSTR(str);
	return s;
}



ostream& operator<<(ostream& os, String& s)
{
	os << s.getSTR();
	return os;
}

istream& operator>>(istream& is, String& s)
{
	string str;
	is >> str;
	s.setSTR(str);
	return is;
}