#include "Student.h"

Student::Student() : Person() {}

Student::Student(string n, int a, string s, int m) : Person(n, a) {
    Set_Subject(s);
    Set_Mark(m);
}

Student::Student(const Student& other) : Person(other) {}

Student::~Student() {}

void Student::Set_Subject(string h) {
    subject = h;
}

void Student::Set_Mark(int m) {
    mark = m;
}

void Student::Get_Subject(string& s) const { s = subject; }

void Student::Get_Mark(int& m) const { m = mark; }

void Student::Check() const {
    if (mark > 2)
        cout << subject << ": " << mark << " - Good mark" << endl;
    else
        cout << subject << ": " << mark << " - Bad mark" << endl;
}