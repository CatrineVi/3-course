#include <iostream>
#include <string>
#include <set>
#include <stack>
#include <vector>

using namespace std;

int Prior(char);
stack<char> InStack(stack<char> _s, char _i) {
	stack<char> s {_s};
	s.push(_i);
	return s;
}
stack<char> OutStack(stack<char> _s) {
	stack<char> s{ _s };
	s.pop();
	return s;
}
double Rezult(string, stack<char>);
vector<pair<char, int>> Cells;
double mas[201]; // ������ ��� ����������
set <char> znak { '*', '/', '+', '-', '^' }; // ��������� ��������-������
int Kol = 8;
//-------- ������� ���������� ���������� ��������-----------
int Prior(char a) {
	switch (a) {
	case '^': return 4;
	case '*': case '/': return 3;
	case '-': case '+': return 2;
	case '(': return 1;
	}
	return 0;
}
//---------------- ������ ��������������� ��������� ----------------------------
double Rezult(string Str, stack<char> begin) {
	char ch, ch1, ch2;
	double op1, op2, rez;
	char chr = 'z' + 1;

	for (int i = 0; i < Str.length(); i++) {
		ch = Str[i];
		if (!znak.count(ch)) begin = InStack(begin, ch);
		else {
			ch1 = begin.top();
			auto pp1 = find_if(Cells.cbegin(), Cells.cend(), [&ch1](const auto& p) { return p.first == ch1; });
			begin = OutStack(begin);
			ch2 = begin.top();
			auto pp2 = find_if(Cells.cbegin(), Cells.cend(), [&ch2](const auto& p) { return p.first == ch2; });
			begin = OutStack(begin);
			op1 = mas[pp1->second];
			op2 = mas[pp2->second];
				switch (ch) {
				case '+': rez = op2 + op1; break;
				case '-': rez = op2 - op1; break;
				case '*': rez = op2 * op1; break;
				case '/': rez = op2 / op1; break;
				case '^': rez = pow(op2, op1); break;
				}
			mas[int(pp2->second)] = rez;
			begin = InStack(begin, pp2->first);
			//mas[int(chr)] = rez;
			//begin = InStack(begin, chr);
			//chr++;
		}
	}
	return rez;
}
void print(string _in, string _out)
{
	cout << endl << "enter: " << _in;
	cout << endl << "translate: " << _out;
}
void print(double _rez)
{
	cout << endl << "result: " << _rez;
}
int main()
{
	//--------------- ����� �������-����������� FormCreate -------------
	char b = 'a';
	//vector<double> Cells{ 9.7, 8.2, 3.6, 4.1, 0.5 };
	
	for (int i = 0; i < Kol; i++) {
		Cells.push_back({ b++,i });
	}
	mas[0] = 9.7; mas[1] = 8.2; mas[2] = 3.6; mas[3] = 4.1; mas[4] = 0.5;

	//---------------------- ����� �������-����������� ������ ��������� --------
	stack<char> t;
	stack<char> begin; // ���� �������� ����
	char ss, a;
	string OutStr = "";
	string InStr = "a * (b - c + d) / e";
	int len = InStr.length(), k;
	for (k = 0; k < len; k++) {
		ss = InStr[k];
		// ����������� ������ ���������� � ����
		if (ss == '(') begin = InStack(begin, ss);
		if (ss == ')') {
			// ����������� �� ����� ��� ����� �������� �� ����������� ������
			while (begin.top() != '(') {
				a = begin.top();
				begin = OutStack(begin); // ��������� ������� �� �����
				OutStr += a; // ���������� � ������
			}
			begin = OutStack(begin); // ������� �� ����� '(' ������
		}
		// ����� (�������) ������� � �������� ������
		if (ss >= 'a' && ss <= 'z') OutStr += ss;
		/* ���� ���� ��������, �� ������������ �� ����� � �������� ������ ���
		�������� � ������� ��� ������ ����������� */
		if (znak.count(ss)) {
			while (!begin.empty() && Prior(begin.top()) >= Prior(ss)) {
				a = begin.top();
				begin = OutStack(begin);
				OutStr += a;
			}
			begin = InStack(begin, ss);
		}
	}
	// ���� ���� �� ����, ������������ ��� �������� � �������� ������
	while (!begin.empty()) {
		a = begin.top();
		begin = OutStack(begin);
		OutStr += a;
	}

	print(InStr, OutStr);
	print(Rezult(OutStr, begin));
	return 0;
}