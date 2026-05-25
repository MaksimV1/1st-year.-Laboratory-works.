#include "Pair.h"
#include <iostream>
using namespace std;

Pair& Pair::operator=(const Pair& t)
{
	if (&t == this) return *this;
	first = t.first;
	second = t.second;
	return *this;
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
