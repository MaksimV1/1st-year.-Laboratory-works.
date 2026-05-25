#include <iostream>
using namespace std;

class Vector {
private:
    int* data;
    size_t capacity;
    size_t length;

    void resize() {
        size_t newCapacity = capacity + 2;
        int* newData = new int[newCapacity];
        for (size_t i = 0; i < length; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Vector() : data(new int[4]), capacity(4), length(0) {}

    ~Vector() {
        delete[] data;
    }

    void push_back(int value) {
        if (length >= capacity)
            resize();
        data[length++] = value;
    }

    int operator[](size_t index) {
        if (index >= length)
            throw "Индекс за пределами массива.";
        return data[index];
    }

    int operator[](size_t index) const {
        if (index >= length)
            throw "Индекс за пределами массива (const).";
        return data[index];
    }

    size_t Size() const {
        return length;
    }

    bool contains(int value) const {
        for (size_t i = 0; i < length; ++i)
            if (data[i] == value)
                return true;
        return false;
    }

    bool operator!=(const Vector& other) const {
        if (length != other.length)
            return true;
        for (size_t i = 0; i < length; ++i)
            if (data[i] != other.data[i])
                return true;
        return false;
    }

    void print() const {
        cout << "[";
        for (size_t i = 0; i < length; ++i) {
            cout << data[i];
            if (i != length - 1)
                cout << ", ";
        }
        cout << "]\n";
    }
};

class IntList {
private:
    Vector elements;

public:
    void add(int value) {
        elements.push_back(value);
    }

    int operator[](size_t index) {
        return elements[index];
    }

    bool operator!=(const IntList& other) const {
        return elements != other.elements;
    }

    size_t Size() const {
        return elements.Size();
    }

    IntList operator*(const IntList& other) {
        IntList list;
        for (int i = 0; i < elements.Size(); ++i)
            list.add(elements[i] * other.elements[i]);
        return list;
    }

    int operator+(int n) const {
        if (n < 0 || static_cast<size_t>(n) >= elements.Size())
            throw "Индекс вне допустимого диапазона.";
        return elements[n];
    }

    void print() const {
        elements.print();
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    try {
        IntList x1;
        x1.add(3);
        x1.add(4);
        x1.add(1);
        x1.add(2);
        x1.add(3);
        x1.add(4);
        IntList x2;
        x2.add(1);
        x2.add(3);
        x2.add(2);
        IntList x3;
        x3.add(4);
        x3.add(5);
        x3.add(6);
        cout << "Список x1: ";
        x1.print();
        cout << "Список x2: ";
        x2.print();
        cout << "Список x3: ";
        x3.print();
        cout << "\nОператор []:" << endl;
        cout << "x1[0] = " << x1[0] << endl;
        cout << "x1[1] = " << x1[1] << endl;
        cout << "x2[2] = " << x2[2] << endl;
        cout << "\nОператор Size():" << endl;
        cout << "x1.Size(): " << x1.Size() << endl;
        cout << "x2.Size(): " << x2.Size() << endl;
        cout << "x3.Size(): " << x3.Size() << endl;
        cout << "\nОператор *:" << endl;
        cout << "x2 * x3: ";
        (x2 * x3).print();
        cout << "x1[10] = " << x1[10] << endl;
    }
    catch (const char* err) {
        std::cerr << "Ошибка: " << err << "\n";
    }
    return 0;
}