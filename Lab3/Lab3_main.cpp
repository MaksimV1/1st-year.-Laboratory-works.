#include "Pair.h"
#include <iostream>
using namespace std;
void main()
{
	Pair a;
	Pair b(15, 20.5);
	Pair c;
	cin >> a;
	cout << "b = " << b << endl;
	cout << "c = a - b" << endl;
	c = a - b;
	cout << "c = " << c << endl;
	cout << "c = c + 10" << endl;
	c = c + 10;
	cout << "c = c + 4.5" << endl;
	c = c + 4.5;
	cout << "c = " << c << endl;
}