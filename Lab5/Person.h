#pragma once
#include <iostream>
#include <string>
using namespace std;

class Person 
{
private:
    string name;
    int age;

public:
    Person();
    Person(string n, int a);
    Person(const Person& other);
    virtual ~Person();
    virtual void Check() const = 0;
    void Get_Name(string& f) const;
    void Get_Age(int& a) const;
    void Set_Name(string f);
    void Set_Age(int s);
    bool operator==(const Person& other) const;
    bool operator!=(const Person& other) const;
};