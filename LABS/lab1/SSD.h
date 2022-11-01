#pragma once
#include <iostream>;
#include <fstream>;
#include <string>;
#include "Memory.h";

using namespace std;

class SSD : public Memory
{
public:
	SSD() {}
	SSD(string name, float speed_reading, float speed_writing, float memory_capacity)
		:Memory(name, speed_reading, speed_writing) {}
	SSD(SSD& a)
	{
		name = a.name;
		speed_reading = a.speed_reading;
		speed_writing = a.speed_writing;
	}
	~SSD() { name = ""; speed_reading = 0; speed_writing = 0; }

	float service_time()
	{
		return (speed_reading * speed_writing);
	}

	// оператор= присваивания (a=b)
	SSD& operator=(const SSD& a)
	{
		if (this == &a)
			return *this;
		this->name = a.name;
		this->speed_reading = a.speed_reading;
		this->speed_writing = a.speed_writing;
		return *this;
	}

	string getName() { return name; }
	float getSpeed_reading() { return speed_reading; }
	float getSpeed_writing() { return speed_writing; }

	void setMemory(const string name, const float speed_reading, const float speed_writing)
	{
		Memory::setMemory(name, speed_reading, speed_writing);
	}

	void reading() const {}
	void writing() const {}
};

// оператор<< вывод (cout << a)
ostream& operator<<(ostream& out, SSD& a)
{
	out << "Name: " << a.getName() << endl;
	out << "Speed reading: " << a.getSpeed_reading() << endl;
	out << "Speed writing: " << a.getSpeed_writing() << endl;
	return out;
}


istream& operator>>(istream& in, SSD& a)
{
	string name;
	float speed_reading, speed_writing;
	in >> name >> speed_reading >> speed_writing;
	a.setMemory(name, speed_reading, speed_writing);
	return in;
}