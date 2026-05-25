#include <iostream>
#include "Person.h"
#include "Student.h"

using namespace std;
void main()
{
	setlocale(LC_ALL, "Russian");
	Person a;
	cin >> a;
	cout << a;
	Person b("Max", 24);
	cout << b;
	a = b;
	cout << a;
	Student c;
	cin >> c;
	c.Check_mark();
	cout << c;
}