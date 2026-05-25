#include "Salary.h"
#include <iostream>
#include <string>
using namespace std;

Salary make_salary()
{
	string s;
	int i;
	double d;
	cout << "Input FIO: ";
	cin >> s;
	cout << "Input sal: ";
	cin >> d;
	cout << "Input prize: ";
	cin >> i;
	Salary t(s, d, i);
	return t;
}

void print_salary(Salary t)
{
	t.show();
}

void main()
{
	Salary t1;
	t1.show();
	Salary t2("Ivanov Ivan Ivanovich", 45000, 20);
	t2.show();
	Salary t3 = t2;
	t3.set_FIO("Telephon");
	t3.set_sal(20000);
	t3.set_prize(5);
	print_salary(t3);
	t1 = make_salary();
	t1.show();
}