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
	bool operator!=(const Pair&) const;
	Pair operator+(int);
	Pair operator+(double);
	Pair operator-(const Pair&);
	Pair operator*(const Pair&);
	friend istream& operator>>(istream& in, Pair& t);
	friend ostream& operator<<(ostream& out, const Pair& t);
};

Pair& Pair::operator=(const Pair& t)
{
	if (&t == this) return *this;
	first = t.first;
	second = t.second;
	return *this;
}

bool Pair::operator!=(const Pair& t) const
{
	if (first != t.first || second != t.second) return true;
	return false;
}

Pair Pair::operator+(int F)
{
	first += F;
	return *this;
}

Pair Pair::operator+(double S)
{
	second += S;
	return *this;
}

Pair Pair::operator-(const Pair& t)
{
	first -= t.first;
	second -= t.second;
	return *this;
}

Pair Pair::operator*(const Pair& t)
{
	first *= t.first;
	second *= t.second;
	return *this;
}

istream& operator>>(istream& in, Pair& t)
{
	cout << "First: "; in >> t.first;
	cout << "second: "; in >> t.second;
	return in;
}

ostream& operator<<(ostream& out, const Pair& t)
{
	return (out << t.first << " : " << t.second);
}
