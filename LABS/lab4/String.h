#pragma once
#include <iostream>
#include <string>
using namespace std;

class String
{
	string str;
public:
	String() :str("") {};
	String(string s) { str = s; }
	//~String();
	string getSTR() { return str; }
	void setSTR(string s) { this->str = s; }
	operator int()
	{
		return str.size();
	}
};
