#include "Salary.h"
#include <iostream>
#include <string>
using namespace std;

Salary::Salary()
{
	FIO = "";
	prize = 0;
	sal = 0;
	cout << "Constructor without atributes for object" << this << endl;
}

Salary::Salary(string N, double S, int K)
{
	FIO = N;
	prize = K;
	sal = S;
	cout << "Constructor with atributes for object" << this << endl;
}

Salary::Salary(const Salary& t)
{
	FIO = t.FIO;
	prize = t.prize;
	sal = t.sal;
	cout << "Copy constructor for object" << this << endl;
}

Salary::~Salary()
{
	cout << "Destruct object" << this << endl;
}

string Salary::get_FIO()
{
	return FIO;
}
int Salary::get_prize()
{
	return prize;
}
double Salary::get_sal()
{
	return sal;
}

void Salary::set_FIO(string N)
{
	FIO = N;
}
void Salary::set_prize(int K)
{
	prize = K;
}
void Salary::set_sal(double S)
{
	sal = S;
}

void Salary::show()
{
	cout << "FIO: " << FIO << endl;
	cout << "sal: " << sal << endl;
	cout << "prize: " << prize << endl;
}