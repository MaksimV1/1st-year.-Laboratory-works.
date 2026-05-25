#include <iostream>
using namespace std;

class Vector
{
private:
    int* data;
    int size;
    int capacity;

    void Resize() {
        capacity *= 2;
        int* new_data = new int[capacity];
        for (int i = 0; i < size; ++i)
            new_data[i] = data[i];
        delete[] data;
        data = new_data;
    }

public:
    Vector() : size(0), capacity(1) {
        data = new int[capacity];
    }

    ~Vector() {
        delete[] data;
    }

    void PushBack(int value) {
        if (size == capacity)
            Resize();
        data[size++] = value;
    }

    void Erase(int index) {
        if (index >= 0 && index < size) {
            for (int i = index; i < size - 1; ++i)
                data[i] = data[i + 1];
            size--;
        }
    }

    int Find(int value) const {
        for (int i = 0; i < size; ++i)
            if (data[i] == value)
                return i;
        return -1;
    }

    int& operator[](int index) {
        return data[index];
    }

    const int& operator[](int index) const {
        return data[index];
    }

    int Size() const {
        return size;
    }

    void Clear() {
        size = 0;
    }

    int GetCapacity() { return capacity; }
};
class SetIterator;

class List {
private:
    Vector elements;

public:
    List() {}
    List(const List& other) { elements = other.elements; }
    ~List() {}

    friend ostream& operator<<(ostream& os, const List& s);
    friend istream& operator>>(istream& is, List& s);
    List& operator=(const List& other);

    int operator[](int index) const;
    bool operator==(const List& other) const;
    bool operator!=(const List& other) const;
    void operator*(const List& other);
    SetIterator operator++(int n) const;

    void Add(int val);
    void Remove(int val);
    int Size() const;
};

class SetIterator {
private:
    List* data;
    int index;
public:
    SetIterator(List* d, int i) : data(d), index(i) {}
    void Next() { if (index < data->Size()) index++; }
    int GetCurrent() const {
        if (index < data->Size()) return (*data)[index];
        return -1;
    }
};
    
void List::Add(int num) {
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
        int num;
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

int List::operator[](int index) const {
    if (index >= 0 && index < elements.Size())
        return elements[index];
    cerr << "Ошибка: Индекс за пределами списка!" << endl;
    return -1;
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
        elements[i] *= other.elements[i];
}



int main() {
    setlocale(LC_ALL, "ru");
    List x1;
    x1.Add(3);
    x1.Add(4);
    x1.Add(1);
    x1.Add(2);
    x1.Add(3);
    x1.Add(4);
    List x2;
    x2.Add(1);
    x2.Add(3);
    x2.Add(2);
    List x3;
    x3.Add(4);
    x3.Add(5);
    x3.Add(6);
    cout << "Список x1: " << x1 << endl;
    cout << "Список x2: " << x2 << endl;
    cout << "Список x3: " << x3 << endl;
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
    x2 * x3;
    cout << x2 << endl;
    cout << "\nОператор + (итератор):" << endl;
    SetIterator it(&x1, 0);
    cout << "Первый элемент: " << it.GetCurrent() << endl;
    it.Next();
    cout << "Следующий элемент: " << it.GetCurrent() << endl;
    cout << "\nПеребор элементов:" << endl;
    while (it.GetCurrent() != -1) {
        cout << it.GetCurrent() << " ";
        it.Next();
    }
    cout << endl;
    cout << endl;
    List wf;
    cout << "Операции ввода-вывода:" << endl;
    cout << "Введите элементы списка wf:" << endl;
    cin >> wf;
    cout << "\nВведенный список: " << wf << endl;
    return 0;
}