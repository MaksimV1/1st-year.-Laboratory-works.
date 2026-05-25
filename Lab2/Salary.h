#pragma once
#include <iostream>
#include <string>
using namespace std;
class Salary
{
	string FIO;
	double sal;
	int prize;
public:
	Salary();
	Salary(string, double, int);
	Salary(const Salary&);
	~Salary();
	string get_FIO();
	void set_FIO(string);
	double get_sal();
	void set_sal(double);
	int get_prize();
	void set_prize(int);
	void show();
};