#pragma once
#include <iostream>
using namespace std;

class Pair
{
	int first;
	double second;
public:
	Pair() { first = 0; second = 0; };
	Pair(int F, double S) { first = F; second = S; };
	Pair(const Pair& t) { first = t.first; second = t.second; };
	~Pair() {};
	int get_first() { return first; };
	double get_second() { return second; };
	void set_first(int F) { first = F; };
	void set_second(double S) { second = S; };
	Pair& operator=(const Pair&);
	Pair operator+(int);
	Pair operator+(double);
	Pair operator-(const Pair&);
	friend istream& operator>>(istream& in, Pair& t);
	friend ostream& operator<<(ostream& out, const Pair& t);
};
