#pragma once
#include "Person.h"

class Student : public Person {
private:
    string subject;
    int mark;

public:
    Student();
    Student(string n, int a, string s, int m);
    Student(const Student& other);
    ~Student() override;
    void Set_Subject(string s);
    void Set_Mark(int m);
    void Get_Subject(string& h) const;
    void Get_Mark(int& m) const;
    void Check() const override;
};