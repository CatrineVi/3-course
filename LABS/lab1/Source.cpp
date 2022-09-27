/*Создать абстрактный базовый класс Memory с виртуальными функциями считыания из памяти, запись в память. Поля класса, название,
скорость чтения/записи. Реализовать произволные классы HHD, SSD, RAM, реализующие собственнные функции. Определить операторы и
конструкторы:
	1. operator=
	2. operator= для разного типа данных
	3. operator<<
	4. operator<
	5. конструктор по умолчанию
	6. конструктор копирования
	7. деструктор
Задание реализовать с разделением классов на интерфейс и реализацию. */

#include <iostream>;
#include <fstream>;
#include <string>;

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

	// оператор= присваивания (a=b)
	/*Memory operator=(Memory a)
	{
		name = a.name;
		speed_reading = a.speed_reading;
		speed_writing = a.speed_writing;
		return *this;
	}*/

	//оператор = для разного типа данных
	//Memory operator=(type a);

	//оператор< сравнения (a<b)
	bool operator<(Memory a)
	{
		float speed_reading1 = speed_reading;
		float speed_reading2 = a.speed_reading;
		return (speed_reading1 < speed_reading2);
	}

	virtual string getName() { return name; }
	virtual float getSpeed_reading() { return speed_reading; }
	virtual float getSpeed_writing() { return speed_writing; }

	virtual void reading() const = 0;
	virtual void writing() const = 0;

};

class HDD : public Memory
{
	float memory_capacity;
public:
	HDD() : memory_capacity(0) {}
	HDD(string name, float speed_reading, float speed_writing, float memory_capacity)
		:Memory(name,speed_reading,speed_writing)
	{ this->memory_capacity = memory_capacity; }
	HDD(Memory& a) {}
	~HDD() { }

	string getName() { return name; }
	float getSpeed_reading() { return speed_reading; }
	float getSpeed_writing() { return speed_writing; }
	float getMemory_capacity() { return memory_capacity; }

	void reading() const{}
	void writing() const{}
};

// оператор<< вывод (cout << a)
ostream& operator<<(ostream& str, HDD a)
{
	return(str << a.getName() << " " << a.getSpeed_reading() << " " << a.getSpeed_writing() << " " << a.getMemory_capacity() << endl);
}

class SSD : public Memory
{
	float memory_capacity;
public:
	SSD() : memory_capacity(0) {}
	SSD(string name, float speed_reading, float speed_writing, float memory_capacity)
		:Memory(name, speed_reading, speed_writing)
	{
		this->memory_capacity = memory_capacity;
	}
	//SSD(Memory& a) {}
	~SSD() { }

	string getName() { return name; }
	float getSpeed_reading() { return speed_reading; }
	float getSpeed_writing() { return speed_writing; }
	float getMemory_capacity() { return memory_capacity; }

	void reading() const{}
	void writing() const{}
};

// оператор<< вывод (cout << a)
ostream& operator<<(ostream& str, SSD a)
{
	return(str << a.getName() << " " << a.getSpeed_reading() << " " << a.getSpeed_writing() << " " << a.getMemory_capacity() << endl);
}

class RAM : public Memory
{
public:
	void reading() const{}
	void writing() const{}
};

int main()
{
	HDD a("HDD",65,54,10000);
	cout << a;
	
	return 0;
}