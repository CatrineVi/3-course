/* Lab1.1
������� ����������� ������� ����� Memory � ������������ ��������� ��������� �� ������, ������ � ������.
���� ������, ��������, �������� ������/������. ����������� ����������� ������ HHD, SSD, RAM, 
����������� ������������ �������. ���������� ��������� � ������������:
	1. operator=
	2. operator= ��� ������� ���� ������
	3. operator<<
	4. operator<
	5. ����������� �� ���������
	6. ����������� �����������
	7. ����������
������� ����������� � ����������� ������� �� ��������� � ����������.

 Lab1.2
 1. �������� operator>>;
 2. ��� �������, ���������� �� ������ ����� ������, �� ������ operator>>, ����������� ������� 
 ���������� �� ����� �� �������������.
 3. �� ������ �������� �� ������� ����������� ������� ������� �������� �������� ��������� 
 ���������������� ��������� �������� ������ � �������� ������.
*/

#include "Memory.h";
#include "HDD.h";
#include "SSD.h";
#include "RAM.h";

//template <class Os> Overload(Os)->Overload<Os>;

/*template <class Os> Os& operator<< (Os& os, const variant<HDD, SSD, RAM>& a)
{
	/*os << "Name: " << visit(
		Overload{
			[](HDD b) {b.getName(); },
			[](SSD b) {b.getName(); },
			[](RAM b) {b.getName(); }
		}, a) << endl;

	os << "Name: " << visit([](const auto& k) {
		using T = decay_t<decltype(k)>;
		if constexpr (is_same_v < T, HDD>)
			k.getName();
		else if constexpr(is_same_v < T, SSD>)
			k.getName();
		else if constexpr (is_same_v<T, RAM>)
			k.getName();
		}, a);
	
	return os;
}*/

/*template<typename ... Ts>
struct Overload : Ts ... {
	using Ts::operator() ...;
};
template<class... Ts> Overload(Ts...)->Overload<Ts...>;

auto TypeOfIntegral = Overload{
		[](HDD& a) {cout << a; },
		[](SSD& a) {cout << a; },
		[](RAM& a) {cout << a; },
};*/

float Avg(vector<Memory*> m)
{
	float avg=0;
	for (int i = 0; i < m.size(); i++)
		avg += m[i]->getSpeed_reading() / m[i]->getSpeed_writing();
	avg = avg / m.size();
	return avg;
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

	RAM e;
	//cin >> e;
	//cout << e;

	//vector<variant<HDD, SSD, RAM>> m;

	vector<Memory*> m;

	ifstream file("disks.txt");

	if (!file.is_open()) 
		cout << "Not found file!" << endl;
	else
	{
		unsigned n = 0;
		file >> n;
		for (int i = 0; i < n; i++)
		{
			string type;
			file >> type;
			if (type == "HDD")
			{
				
				HDD disk;
				file >> disk;
				Memory* p = new HDD(disk);
				m.push_back(p);
			}
			else if (type == "SSD")
			{
				SSD disk;
				file >> disk;
				Memory* p = new SSD(disk);
				m.push_back(p);
			}
			else if (type == "RAM")
			{
				RAM disk;
				file >> disk;
				Memory* p = new RAM(disk);
				m.push_back(p);

			}
		}
		
		//visit(TypeOfIntegral, m[0]);
	}
	for (int i = 0; i < m.size(); i++)
		cout << *m[i];

	/*for (int i = 0; i < m.size(); i++) {
		visit(TypeOfIntegral, m[i]);
	}*/

	cout << "\nAvg(r/w) = " << Avg(m);
	return 0;
}