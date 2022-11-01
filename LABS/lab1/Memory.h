#pragma once
#include <iostream>;
#include <fstream>;
#include <string>;
#include <vector>
#include <variant>;
#include <typeinfo>;

using namespace std;

class Memory
{
protected:
	string name;
	float speed_reading, speed_writing;
public:
	// конструктор по умолчанию
	Memory() : name(""), speed_reading(0), speed_writing(0) {}

	// конструктор с параметрами
	Memory(string name, float speed_reading, float speed_writing)
	{
		this->name = name;
		this->speed_reading = speed_reading;
		this->speed_writing = speed_writing;
	}

	// конструктор копирования
	Memory(Memory& a)
	{
		name = a.name;
		speed_reading = a.speed_reading;
		speed_writing = a.speed_writing;
	}

	// деструктор
	~Memory() { name = ""; speed_reading = 0; speed_writing = 0; }

	//оператор = для разного типа данных
	//Memory operator=(type a);

	//оператор< сравнения (a<b)
	bool operator<(const Memory& a)
	{
		float speed_reading1 = speed_reading;
		float speed_reading2 = a.speed_reading;
		return (speed_reading1 < speed_reading2);
	}

	string getName() { return name; }
	float getSpeed_reading() { return speed_reading; }
	float getSpeed_writing() { return speed_writing; }

	virtual void setMemory(const string name, const float speed_reading, const float speed_writing)
	{
		this->name = name;
		this->speed_reading = speed_reading;
		this->speed_writing = speed_writing;
	}

	virtual void reading() const = 0;
	virtual void writing() const = 0;


	//friend ostream& operator<<(ostream& out, Memory& a);
};

// оператор<< вывод (cout << a)
ostream& operator<<(ostream& out, Memory& a)
{
	out << "Name: " << a.getName() << endl;
	out << "Speed reading: " << a.getSpeed_reading() << endl;
	out << "Speed writing: " << a.getSpeed_writing() << endl;
	return out;
}

istream& operator>>(istream& in, Memory& a)
{
	string name;
	float speed_reading, speed_writing;
	in >> name >> speed_reading >> speed_writing;
	a.setMemory(name, speed_reading, speed_writing);
	return in;
}
