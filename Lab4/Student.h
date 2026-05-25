#pragma once
#include "person.h"

class Student : public Person
{
public:
	Student(void);
public:
	~Student(void);
	Student(string, int, string, int);
	Student(const Student&);
	string Get_subject() { return subject; }
	int Get_mark() { return mark; }
	void Set_subject(string);
	void Set_mark(int);
	void Check_mark();
	Student& operator=(const Student&);
	friend istream& operator>>(istream& in, Student& l);
	friend ostream& operator<<(ostream& out, const Student& l);
protected:
	string subject;
	int mark;
};
