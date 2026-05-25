#include "Person.h"
Person::Person(void)
{
	name = "";
	age = 0;
}

Person::~Person(void)
{
}

Person::Person(string N, int A)
{
	name = N;
	age = A;
}

Person::Person(const Person& person)
{
	name = person.name;
	age = person.age;
}

void Person::Set_age(int A)
{
	age = A;
}
void Person::Set_name(string N)
{
	name = N;

}

Person& Person::operator=(const Person& c)
{
	if (&c == this) return *this;
	name = c.name;
	age = c.age;
	return *this;
}

istream& operator>>(istream& in, Person& c)
{
	cout << "Name: "; in >> c.name;
	cout << "Age: ";in >> c.age;
	return in;
}

ostream& operator<<(ostream& out, const Person& c)
{
	out << "Name: " << c.name << endl;
	out << "Age: " << c.age << endl;
	return out;
}