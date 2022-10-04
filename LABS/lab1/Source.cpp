/*—оздать абстрактный базовый класс Memory с виртуальными функци€ми считыани€ из пам€ти, запись в пам€ть. ѕол€ класса, название,
скорость чтени€/записи. –еализовать произволные классы HHD, SSD, RAM, реализующие собственнные функции. ќпределить операторы и
конструкторы:
	1. operator=
	2. operator= дл€ разного типа данных
	3. operator<<
	4. operator<
	5. конструктор по умолчанию
	6. конструктор копировани€
	7. деструктор
«адание реализовать с разделением классов на интерфейс и реализацию. */

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

	// конструктор копировани€
	Memory(Memory& a)
	{
		name = a.name;
		speed_reading = a.speed_reading;
		speed_writing = a.speed_writing;
	}

	// деструктор
	~Memory() { name = ""; speed_reading = 0; speed_writing = 0; }

	//оператор = дл€ разного типа данных
	//Memory operator=(type a);

	//оператор< сравнени€ (a<b)
	bool operator<(const Memory& a)
	{
		float speed_reading1 = speed_reading;
		float speed_reading2 = a.speed_reading;
		return (speed_reading1 < speed_reading2);
	}

	string getName() { return name; }
	float getSpeed_reading() { return speed_reading; }
	float getSpeed_writing() { return speed_writing; }

	virtual void reading() const = 0;
	virtual void writing() const = 0;

	friend ostream& operator<<(ostream& out, Memory& a);
};

// оператор<< вывод (cout << a)
ostream& operator<<(ostream& out, Memory& a)
{
	out << "Name: " << a.getName() << endl;
	out << "Speed reading: " << a.getSpeed_reading() << endl;
	out << "Speed writing: " << a.getSpeed_writing() << endl;
	return out;
}

class HDD : public Memory
{
	float memory_capacity;
public:
	HDD() : memory_capacity(0) {}
	HDD(string name, float speed_reading, float speed_writing, float memory_capacity)
		:Memory(name,speed_reading,speed_writing)
	{ this->memory_capacity = memory_capacity; }
	HDD(HDD& a) : Memory(a)
	{
		memory_capacity = a.memory_capacity;
	}
	~HDD() { name = ""; speed_reading = 0; speed_writing = 0; memory_capacity = 0; }

	// оператор= присваивани€ (a=b)
	HDD& operator=(const HDD& a)
	{
		if (this == &a)
			return *this;
		this->name = a.name;
		this->speed_reading = a.speed_reading;
		this->speed_writing = a.speed_writing;
		this->memory_capacity = a.memory_capacity;
		return *this;
	}

	float service_time()
	{
		return (speed_reading * speed_writing);
	}

	string getName() { return name; }
	float getSpeed_reading() { return speed_reading; }
	float getSpeed_writing() { return speed_writing; }
	float getMemory_capacity() { return memory_capacity; }

	void reading() const{}
	void writing() const{}
};

// оператор<< вывод (cout << a)
ostream& operator<<(ostream& out, HDD& a)
{
	out << "Name: " << a.getName() << endl;
	out << "Speed reading: " << a.getSpeed_reading() << endl;
	out << "Speed writing: " << a.getSpeed_writing() << endl;
	out << "Memory capacity: " << a.getMemory_capacity() << endl;
	return out;
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
	SSD(SSD& a): Memory(a) 
	{
		memory_capacity = a.memory_capacity;
	}
	~SSD() { name = ""; speed_reading = 0; speed_writing = 0; memory_capacity = 0; }

	float service_time()
	{
		return (speed_reading * memory_capacity);
	}

	// оператор= присваивани€ (a=b)
	SSD& operator=(const SSD& a)
	{
		if (this == &a)
			return *this;
		this->name = a.name;
		this->speed_reading = a.speed_reading;
		this->speed_writing = a.speed_writing;
		this->memory_capacity = a.memory_capacity;
		return *this;
	}

	string getName() { return name; }
	float getSpeed_reading() { return speed_reading; }
	float getSpeed_writing() { return speed_writing; }
	float getMemory_capacity() { return memory_capacity; }

	void reading() const{}
	void writing() const{}
};

// оператор<< вывод (cout << a)
ostream& operator<<(ostream& out, SSD& a)
{
	out << "Name: " << a.getName() << endl;
	out << "Speed reading: " << a.getSpeed_reading() << endl;
	out << "Speed writing: " << a.getSpeed_writing() << endl;
	out << "Memory capacity: " << a.getMemory_capacity() << endl;
	return out;
}

class RAM : public Memory
{
	float memory_capacity;
public:
	RAM() : memory_capacity(0) {}
	RAM(string name, float speed_reading, float speed_writing, float memory_capacity)
		:Memory(name, speed_reading, speed_writing)
	{
		this->memory_capacity = memory_capacity;
	}
	RAM(RAM& a):Memory(a)
	{
		memory_capacity = a.memory_capacity;
	}
	~RAM() { name = ""; speed_reading = 0; speed_writing = 0; memory_capacity = 0; }

	float service_time()
	{
		return (memory_capacity * speed_writing);
	}

	// оператор= присваивани€ (a=b)
	RAM& operator=(const RAM& a)
	{
		if (this == &a)
			return *this;
		this->name = a.name;
		this->speed_reading = a.speed_reading;
		this->speed_writing = a.speed_writing;
		this->memory_capacity = a.memory_capacity;
		return *this;
	}

	string getName() { return name; }
	float getSpeed_reading() { return speed_reading; }
	float getSpeed_writing() { return speed_writing; }
	float getMemory_capacity() { return memory_capacity; }

	void reading() const{}
	void writing() const{}
};

// оператор<< вывод (cout << a)
ostream& operator<<(ostream& out, RAM& a)
{
	out << "Name: " << a.getName() << endl;
	out << "Speed reading: " << a.getSpeed_reading() << endl;
	out << "Speed writing: " << a.getSpeed_writing() << endl;
	out << "Memory capacity: " << a.getMemory_capacity() << endl;
	return out;
}

int main()
{
	HDD a("HDD",65,54,10000);
	cout << a;
	cout << endl;

	SSD b("ssd", 59,74,512);
	cout << b;
	cout << endl;

	if (b < a)
		cout << b.getName() << " < " << a.getName() << endl;

	cout << endl;

	HDD c(a);
	cout << c;
	cout << endl;

	HDD d;
	d = a;
	cout << d;
	cout << endl;

	cout << "Service time " << a.getName() << ": " << a.service_time() << endl;

	return 0;
}