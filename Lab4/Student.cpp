#include "Student.h"
Student::Student(void) :Person()
{
	subject = "";
	mark = 0;
}

Student::~Student(void)
{
}

Student::Student(string N, int A, string S, int M) :Person(N, A)
{
	subject = S;
	mark = M;
}

Student::Student(const Student& S)
{
	name = S.name;
	age = S.age;
	subject = S.subject;
	mark = S.mark;
}

void Student::Set_mark(int M)
{
	mark = M;
}

Student& Student::operator=(const Student& S)
{
	if (&S == this) return *this;
	name = S.name;
	age = S.age;
	subject = S.subject;
	mark = S.mark;
	return *this;
}

istream& operator>>(istream& in, Student& S)
{
	cout << "Name: "; in >> S.name;
	cout << "Age: ";in >> S.age;
	cout << "Subject: ";in >> S.subject;
	cout << "Mark: ";in >> S.mark;
	return in;
}

ostream& operator<<(ostream& out, const Student& S)
{
	out << "Name: " << S.name << endl;
	out << "Age: " << S.age << endl;
	out << "Subject: " << S.subject << endl;
	out << "Mark: " << S.mark << endl;
	out << "\n";
	return out;
}

void Student::Check_mark()
{
	if (mark <= 2) cout << "Неудовлетворительная оценка" << endl;
	else cout << "Удовлетворительная оценка" << endl;
}