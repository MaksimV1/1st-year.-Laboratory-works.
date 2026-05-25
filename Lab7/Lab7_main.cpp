#include <iostream>
#include "Vector.h"
#include "Pair.h"
#include "List.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    List x1;
    x1.Add(Pair(15, 20.5));
    x1.Add(Pair(1, 2.5));
    x1.Add(Pair(4, 8.7));
    x1.Add(Pair(81, 4.2));
    List x2;
    x2.Add(Pair(6, 7.7));
    x2.Add(Pair(12, 12.5));
    x2.Add(Pair(3, 8.9));
    List x3;
    x3.Add(Pair(15, 20.5));
    x3.Add(Pair(15, 20.5));
    x3.Add(Pair(15, 20.5));
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
    ListIterator it(&x1, 0);
    cout << "Первый элемент: " << it.GetCurrent() << endl;
    it.Next();
    cout << "Следующий элемент: " << it.GetCurrent() << endl;
    cout << "\nПеребор элементов:" << endl;
    while (it.GetCurrent() != Pair(-1, -1)) {
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