#include "Person.h"
Person::Person() : name(0), age(0) {}

Person::Person(string n, int a) : name(n), age(a) {}

Person::Person(const Person& other) : name(other.name), age(other.age) {}

Person::~Person() {}

void Person::Get_Name(string& f) const { f = name; }
void Person::Get_Age(int& s) const { s = age; }

void Person::Set_Name(string f) { name = f; }
void Person::Set_Age(int s) { age = s; }

bool Person::operator==(const Person& other) const {
    return (name == other.name) && (age == other.age);
}

bool Person::operator!=(const Person& other) const {
    return !(*this == other);
}