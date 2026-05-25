#include "Vector.h"

Vector::Vector() : size(0), capacity(2) {
    elements = new Person * [capacity];
}

Vector::~Vector() {
    for (int i = 0; i < size; ++i)
        delete elements[i];
    delete[] elements;
}

void Vector::Add(Person* element) {
    if (size == capacity) Resize();
    elements[size++] = element;
}

ostream& operator<<(ostream& os, const Vector& vec) {
    os << "Vector contents:" << endl;
    for (int i = 0; i < vec.size; ++i) {
        os << i + 1 << ": ";
        vec.elements[i]->Check();
    }
    return os;
}