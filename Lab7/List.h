#pragma once
#include "Vector.h"
#include "Pair.h"

class ListIterator;

class List {
private:
    Vector<Pair> elements;

public:
    List() {}
    List(const List& other) { elements = other.elements; }
    ~List() {}

    friend ostream& operator<<(ostream& os, const List& s);
    friend istream& operator>>(istream& is, List& s);
    List& operator=(const List& other);

    Pair operator[](int index) const;
    bool operator==(const List& other) const;
    bool operator!=(const List& other) const;
    void operator*(const List& other);
    ListIterator operator++(int n) const;

    void Add(Pair val);
    void Remove(int val);
    int Size() const;
};

class ListIterator {
private:
    List* data;
    int index;
public:
    ListIterator(List* d, int i) : data(d), index(i) {}
    void Next() { if (index < data->Size()) index++; }
    Pair GetCurrent() const {
        if (index < data->Size()) return (*data)[index];
        return Pair(-1, -1);
    }
};

void List::Add(Pair num) {
    elements.PushBack(num);
}

void List::Remove(int num) {
    if (num < elements.Size()) elements.Erase(num);
}

int List::Size() const
{
    return elements.Size();
}

ostream& operator<<(ostream& os, const List& s) {
    os << '[';
    for (int i = 0; i < s.elements.Size(); ++i) {
        os << s.elements[i];
        if (i != s.elements.Size() - 1)
            os << ", ";
    }
    os << ']';
    return os;
}

istream& operator>>(istream& is, List& s) {
    s.elements.Clear();
    int count;
    cout << "Введите количество элементов: ";
    is >> count;
    cout << "Введите элементы: ";
    for (int i = 0; i < count; ++i) {
        Pair num;
        is >> num;
        s.Add(num);
    }
    return is;
}

List& List::operator=(const List& other) {
    if (this != &other)
        elements = other.elements;
    return *this;
}

Pair List::operator[](int index) const {
    if (index >= 0 && index < elements.Size())
        return elements[index];
    cerr << "Ошибка: Индекс за пределами списка!" << endl;
    return Pair(0, 0);
}

bool List::operator==(const List& other) const {
    if (elements.Size() != other.elements.Size()) return false;
    for (int i = 0; i < elements.Size(); ++i)
        if (elements[i] != other.elements[i]) return false;
    return true;
}

bool List::operator!=(const List& other) const {
    return !(*this == other);
}

void List::operator*(const List& other) {
    for (int i = 0; i < elements.Size(); ++i)
        elements[i] = elements[i] * other.elements[i];
}
