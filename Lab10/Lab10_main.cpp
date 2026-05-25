#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Pair {
    int first;
    double second;

public:
    Pair() { first = 0; second = 0; };
    Pair(int F, double S) { first = F; second = S; };
    Pair(const Pair& t) { first = t.first; second = t.second; };
    ~Pair() {};

    int get_first() { return first; };
    double get_second() { return second; };
    void set_first(int F) { first = F; };
    void set_second(double S) { second = S; };

    Pair& operator=(const Pair&);
    Pair operator+(int);
    Pair operator+(double);
    Pair operator-(const Pair&);
    bool operator<(const Pair&) const;
    bool operator==(const Pair&) const;

    friend istream& operator>>(istream& in, Pair& t);
    friend ostream& operator<<(ostream& out, const Pair& t);
    friend ifstream& operator>>(ifstream& in, Pair& t);
    friend ofstream& operator<<(ofstream& out, const Pair& t);
};

// Реализация операторов
Pair& Pair::operator=(const Pair& t) {
    if (&t == this) return *this;
    first = t.first;
    second = t.second;
    return *this;
}

Pair Pair::operator+(int F) {
    Pair temp = *this;
    temp.first += F;
    return temp;
}

Pair Pair::operator+(double S) {
    Pair temp = *this;
    temp.second += S;
    return temp;
}

Pair Pair::operator-(const Pair& t) {
    Pair temp;
    temp.first = first - t.first;
    temp.second = second - t.second;
    return temp;
}

bool Pair::operator<(const Pair& t) const {
    if (first < t.first) return true;
    if (first == t.first && second < t.second) return true;
    return false;
}

bool Pair::operator==(const Pair& t) const {
    return (first == t.first && second == t.second);
}

istream& operator>>(istream& in, Pair& t) {
    cout << "Первое число (int): ";
    in >> t.first;
    cout << "Второе число (double): ";
    in >> t.second;
    return in;
}

ostream& operator<<(ostream& out, const Pair& t) {
    return (out << t.first << " : " << t.second);
}

ifstream& operator>>(ifstream& in, Pair& t) {
    in >> t.first >> t.second;
    return in;
}

ofstream& operator<<(ofstream& out, const Pair& t) {
    out << t.first << " " << t.second << endl;
    return out;
}

// Функция для создания и сохранения объектов в файл
void createAndSaveObjects() {
    ofstream file("pairs.txt", ios::app);
    if (!file) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    int count;
    cout << "Введите количество пар для добавления: ";
    cin >> count;

    for (int i = 0; i < count; i++) {
        Pair p;
        cout << "\nПара " << (i + 1) << ":" << endl;
        cin >> p;
        file << p;
    }

    file.close();
    cout << "Объекты успешно сохранены в файл!" << endl;
}

// Функция для чтения и просмотра объектов из файла
void readAndDisplayObjects() {
    ifstream file("pairs.txt");
    if (!file) {
        cout << "Файл не найден или не может быть открыт!" << endl;
        return;
    }

    Pair p;
    int index = 1;
    cout << "\nСодержимое файла:" << endl;
    cout << "№\tПара" << endl;
    cout << "----------------" << endl;

    while (file >> p) {
        cout << index << "\t" << p << endl;
        index++;
    }

    if (index == 1) {
        cout << "Файл пуст!" << endl;
    }

    file.close();
}

// Функция для удаления записей меньших заданного значения
void deleteRecordsLessThan() {
    vector<Pair> pairs;
    ifstream inFile("pairs.txt");

    if (!inFile) {
        cout << "Файл не найден!" << endl;
        return;
    }

    // Читаем все пары из файла
    Pair p;
    while (inFile >> p) {
        pairs.push_back(p);
    }
    inFile.close();

    if (pairs.empty()) {
        cout << "Файл пуст!" << endl;
        return;
    }

    // Получаем значение для сравнения
    Pair threshold;
    cout << "Введите пороговое значение:" << endl;
    cin >> threshold;

    // Удаляем элементы меньше порогового значения
    int initialSize = pairs.size();
    pairs.erase(remove_if(pairs.begin(), pairs.end(),
        [&threshold](const Pair& p) { return p < threshold; }),
        pairs.end());

    // Записываем обратно в файл
    ofstream outFile("pairs.txt");
    for (const auto& pair : pairs) {
        outFile << pair;
    }
    outFile.close();

    cout << "Удалено " << (initialSize - pairs.size()) << " записей." << endl;
}

// Функция для увеличения записей с заданным значением на число L
void increaseRecordsByValue() {
    vector<Pair> pairs;
    ifstream inFile("pairs.txt");

    if (!inFile) {
        cout << "Файл не найден!" << endl;
        return;
    }

    // Читаем все пары
    Pair p;
    while (inFile >> p) {
        pairs.push_back(p);
    }
    inFile.close();

    if (pairs.empty()) {
        cout << "Файл пуст!" << endl;
        return;
    }

    // Получаем значение для поиска и число для увеличения
    Pair target;
    cout << "Введите значение для поиска:" << endl;
    cin >> target;

    double L;
    cout << "Введите число L для увеличения: ";
    cin >> L;

    int count = 0;
    for (auto& pair : pairs) {
        if (pair == target) {
            pair = pair + L;
            count++;
        }
    }

    // Записываем обратно в файл
    ofstream outFile("pairs.txt");
    for (const auto& pair : pairs) {
        outFile << pair;
    }
    outFile.close();

    cout << "Увеличено " << count << " записей." << endl;
}

// Функция для добавления K записей после элемента с заданным номером
void addRecordsAfterPosition() {
    vector<Pair> pairs;
    ifstream inFile("pairs.txt");

    if (!inFile) {
        cout << "Файл не найден!" << endl;
        return;
    }

    // Читаем все пары
    Pair p;
    while (inFile >> p) {
        pairs.push_back(p);
    }
    inFile.close();

    if (pairs.empty()) {
        cout << "Файл пуст!" << endl;
        return;
    }

    cout << "Текущее количество записей: " << pairs.size() << endl;

    int position, K;
    cout << "Введите номер элемента (1-" << pairs.size() << "): ";
    cin >> position;

    if (position < 1 || position > pairs.size()) {
        cout << "Неверный номер элемента!" << endl;
        return;
    }

    cout << "Введите количество записей для добавления: ";
    cin >> K;

    vector<Pair> newPairs;
    for (int i = 0; i < K; i++) {
        Pair newPair;
        cout << "\nНовая пара " << (i + 1) << ":" << endl;
        cin >> newPair;
        newPairs.push_back(newPair);
    }

    // Вставляем новые элементы после указанной позиции
    pairs.insert(pairs.begin() + position, newPairs.begin(), newPairs.end());

    // Записываем обратно в файл
    ofstream outFile("pairs.txt");
    for (const auto& pair : pairs) {
        outFile << pair;
    }
    outFile.close();

    cout << "Добавлено " << K << " записей после позиции " << position << "." << endl;
}

// Функция для изменения объектов в файле
void modifyObjects() {
    vector<Pair> pairs;
    ifstream inFile("pairs.txt");

    if (!inFile) {
        cout << "Файл не найден!" << endl;
        return;
    }

    // Читаем все пары
    Pair p;
    while (inFile >> p) {
        pairs.push_back(p);
    }
    inFile.close();

    if (pairs.empty()) {
        cout << "Файл пуст!" << endl;
        return;
    }

    // Показываем текущие записи
    cout << "\nТекущие записи:" << endl;
    for (size_t i = 0; i < pairs.size(); i++) {
        cout << (i + 1) << ". " << pairs[i] << endl;
    }

    int position;
    cout << "\nВведите номер записи для изменения (1-" << pairs.size() << "): ";
    cin >> position;

    if (position < 1 || position > pairs.size()) {
        cout << "Неверный номер записи!" << endl;
        return;
    }

    cout << "Текущее значение: " << pairs[position - 1] << endl;
    cout << "Введите новое значение:" << endl;
    cin >> pairs[position - 1];

    // Записываем обратно в файл
    ofstream outFile("pairs.txt");
    for (const auto& pair : pairs) {
        outFile << pair;
    }
    outFile.close();

    cout << "Запись успешно изменена!" << endl;
}

// Главное меню
void showMenu() {
    cout << "\n=== МЕНЮ ===" << endl;
    cout << "1. Создать и сохранить объекты" << endl;
    cout << "2. Просмотреть объекты из файла" << endl;
    cout << "3. Удалить записи меньше заданного значения" << endl;
    cout << "4. Увеличить записи с заданным значением" << endl;
    cout << "5. Добавить записи после заданной позиции" << endl;
    cout << "6. Изменить запись" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите опцию: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            createAndSaveObjects();
            break;
        case 2:
            readAndDisplayObjects();
            break;
        case 3:
            deleteRecordsLessThan();
            break;
        case 4:
            increaseRecordsByValue();
            break;
        case 5:
            addRecordsAfterPosition();
            break;
        case 6:
            modifyObjects();
            break;
        case 0:
            cout << "Программа завершена." << endl;
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    } while (choice != 0);

    return 0;
}