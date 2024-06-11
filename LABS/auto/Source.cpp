#include <iostream>

using namespace std;

class Subject
{
protected:
	int rs;
public:
	virtual void print() = 0;
};

class RealSubject: public Subject
{
public:
	RealSubject(int r) { rs = r; }
	~RealSubject() {}
	void print() { cout << "Real"<< rs << endl; }
};

class Proxy: public Subject 
{
	RealSubject* realSubject;
public:
	Proxy(int r) 
	{
		realSubject = new RealSubject(r);
	}
	~Proxy() {
		delete realSubject;
	}
	void print() {
		cout << " Proxy" << endl;
		realSubject->print();
	}
};

int main() {
	Subject* p;
	p = new RealSubject(10);
	p->print();
	delete p;
	p = new Proxy(5);
	p->print();
	return 0;
}