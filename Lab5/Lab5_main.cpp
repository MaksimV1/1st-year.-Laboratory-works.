#include <iostream>
#include "Person.h"
#include "Student.h"
#include "Vector.h"

int main() {
    setlocale(LC_ALL, "ru");
    Student* student1 = new Student("Maksim", 20, "History", 4);
    Student* student2 = new Student("Tom", 19, "Math", 2);
    Student* student3 = new Student("Richard", 22, "Math", 5);

    cout << "=== Demonstration with Student class ===" << endl;
    cout << "student1: "; student1->Check();
    cout << "student2: "; student2->Check();

    cout << "=== Demonstration with Vector class ===" << endl;
    Vector vec;
    vec.Add(student1);
    vec.Add(student2);
    vec.Add(student3);
    Student* student4 = new Student("Kate", 19, "History", 2);
    vec.Add(student4);
    cout << vec;

    cout << "=== Polymorphism demonstration ===" << endl;
    Person* person1 = new Student("Harry", 21, "Literature", 5);
    Person* person2 = new Student("Veronica", 20, "Physics", 2);
    cout << "person1: "; person1->Check();
    cout << "person2: "; person2->Check();
    vec.Add(person1);
    vec.Add(person2);
    cout << "=== Final vector contents ===" << endl;
    cout << vec;
}

