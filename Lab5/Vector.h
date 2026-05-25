#pragma once
#include "Person.h"

class Vector
{
private:
    Person** elements;
    int size;
    int capacity;

    void Resize()
    {
        capacity *= 2;
        Person** new_elements = new Person * [capacity];
        for (int i = 0; i < size; ++i)
            new_elements[i] = elements[i];
        delete[] elements;
        elements = new_elements;
    }
public:
    Vector();
    ~Vector();
    void Add(Person* element);
    friend ostream& operator<<(ostream& os, const Vector& vec);
};