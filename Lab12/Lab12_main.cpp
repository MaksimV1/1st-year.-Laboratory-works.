#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

using namespace std;

class Pair {
    int first;
    double second;
public:
    Pair() { first = 0; second = 0; };
    Pair(int F, double S) { first = F; second = S; };
    Pair(const Pair& t) { first = t.first; second = t.second; };
    ~Pair() {};

    int get_first() const { return first; };
    double get_second() const { return second; };
    void set_first(int F) { first = F; };
    void set_second(double S) { second = S; };

    Pair& operator=(const Pair&);
    Pair operator+(int);
    Pair operator+(double);
    Pair operator-(const Pair&);
    bool operator<(const Pair& other) const;
    bool operator<=(const Pair& other) const;
    bool operator>=(const Pair& other) const;
    bool operator==(const Pair& other) const;

    friend istream& operator>>(istream& in, Pair& t);
    friend ostream& operator<<(ostream& out, const Pair& t);
};

Pair& Pair::operator=(const Pair& t) {
    if (&t == this) return *this;
    first = t.first;
    second = t.second;
    return *this;
}

Pair Pair::operator+(int F) {
    Pair result = *this;
    result.first += F;
    return result;
}

Pair Pair::operator+(double S) {
    Pair result = *this;
    result.second += S;
    return result;
}

Pair Pair::operator-(const Pair& t) {
    Pair result = *this;
    result.first -= t.first;
    result.second -= t.second;
    return result;
}

bool Pair::operator<(const Pair& other) const {
    if (first != other.first) return first < other.first;
    return second < other.second;
}

bool Pair::operator<=(const Pair& other) const {
    return *this < other || *this == other;
}

bool Pair::operator>=(const Pair& other) const {
    return !(*this < other);
}

bool Pair::operator==(const Pair& other) const {
    return first == other.first && second == other.second;
}

istream& operator>>(istream& in, Pair& t) {
    cout << "First: "; in >> t.first;
    cout << "Second: "; in >> t.second;
    return in;
}

ostream& operator<<(ostream& out, const Pair& t) {
    return (out << t.first << " : " << t.second);
}

// ЗАДАЧА 1: Функции для работы с multiset<double>

// Создание и заполнение контейнера
multiset<double> createDoubleMultiset() {
    multiset<double> ms;
    ms.insert(3.14);
    ms.insert(2.71);
    ms.insert(1.41);
    ms.insert(3.14);
    ms.insert(2.0);
    ms.insert(5.5);
    ms.insert(1.0);
    return ms;
}

// Добавление элементов
void addElementsToDoubleMultiset(multiset<double>& ms) {
    ms.insert(7.5);
    ms.insert(3.14); // дубликат
    ms.insert(0.5);
}

// Удаление элементов из заданного диапазона
void removeElementsInRange(multiset<double>& ms, double min_val, double max_val) {
    auto it_low = ms.lower_bound(min_val);
    auto it_high = ms.upper_bound(max_val);
    ms.erase(it_low, it_high);
}

// Найти среднее арифметическое и добавить в конец
void addAverageToEnd(multiset<double>& ms) {
    if (ms.empty()) return;

    double sum = accumulate(ms.begin(), ms.end(), 0.0);
    double average = sum / ms.size();
    ms.insert(average);
    cout << "Среднее арифметическое: " << average << endl;
}

// К каждому элементу добавить сумму мин и макс элементов
void addMinMaxSum(multiset<double>& ms) {
    if (ms.empty()) return;

    double min_elem = *ms.begin();
    double max_elem = *ms.rbegin();
    double sum_min_max = min_elem + max_elem;

    multiset<double> new_ms;
    for (const auto& elem : ms) {
        new_ms.insert(elem + sum_min_max);
    }
    ms = new_ms;
    cout << "Сумма мин и макс элементов: " << sum_min_max << endl;
}

void printDoubleMultiset(const multiset<double>& ms) {
    cout << "Multiset содержит: ";
    for (const auto& elem : ms) {
        cout << elem << " ";
    }
    cout << endl;
}

// ЗАДАЧА 2: Функции для работы с multiset<Pair>

multiset<Pair> createPairMultiset() {
    multiset<Pair> ms;
    ms.insert(Pair(1, 2.5));
    ms.insert(Pair(3, 4.7));
    ms.insert(Pair(2, 1.8));
    ms.insert(Pair(1, 3.2));
    ms.insert(Pair(5, 2.1));
    return ms;
}

void addElementsToPairMultiset(multiset<Pair>& ms) {
    ms.insert(Pair(4, 6.3));
    ms.insert(Pair(1, 2.5)); // дубликат
    ms.insert(Pair(6, 1.1));
}

void removePairElementsInRange(multiset<Pair>& ms, const Pair& min_pair, const Pair& max_pair) {
    auto it_low = ms.lower_bound(min_pair);
    auto it_high = ms.upper_bound(max_pair);
    ms.erase(it_low, it_high);
}

void addAverageToPairMultiset(multiset<Pair>& ms) {
    if (ms.empty()) return;

    int sum_first = 0;
    double sum_second = 0.0;

    for (const auto& pair : ms) {
        sum_first += pair.get_first();
        sum_second += pair.get_second();
    }

    Pair average(sum_first / ms.size(), sum_second / ms.size());
    ms.insert(average);
    cout << "Среднее арифметическое пары: " << average << endl;
}

void addMinMaxSumToPairs(multiset<Pair>& ms) {
    if (ms.empty()) return;

    const Pair& min_pair = *ms.begin();
    const Pair& max_pair = *ms.rbegin();

    int sum_first = min_pair.get_first() + max_pair.get_first();
    double sum_second = min_pair.get_second() + max_pair.get_second();

    multiset<Pair> new_ms;
    for (const auto& pair : ms) {
        new_ms.insert(Pair(pair.get_first() + sum_first, pair.get_second() + sum_second));
    }
    ms = new_ms;
    cout << "Сумма мин и макс пар: (" << sum_first << ", " << sum_second << ")" << endl;
}

void printPairMultiset(const multiset<Pair>& ms) {
    cout << "Multiset содержит:" << endl;
    for (const auto& pair : ms) {
        cout << pair << endl;
    }
}

// ЗАДАЧА 3: Параметризированный класс-список

template<typename T>
class AssociativeList {
private:
    list<T> container;

public:
    AssociativeList() = default;

    void insert(const T& value) {
        container.push_back(value);
        container.sort();
    }

    void erase(const T& value) {
        container.remove(value);
    }

    void addElements(const vector<T>& elements) {
        for (const auto& elem : elements) {
            insert(elem);
        }
    }

    void removeElementsInRange(const T& min_val, const T& max_val) {
        container.remove_if([min_val, max_val](const T& elem) {
            return elem >= min_val && elem <= max_val;
            });
    }

    void addAverageToEnd() {
        if (container.empty()) return;

        T sum = accumulate(container.begin(), container.end(), T{});
        T average = sum / container.size();
        container.push_back(average);
        cout << "Среднее арифметическое: " << average << endl;
    }

    void addMinMaxSum() {
        if (container.empty()) return;

        auto minmax = minmax_element(container.begin(), container.end());
        T sum_min_max = *minmax.first + *minmax.second;

        for (auto& elem : container) {
            elem = elem + sum_min_max;
        }
        cout << "Сумма мин и макс элементов: " << sum_min_max << endl;
    }

    void print() const {
        cout << "Список содержит: ";
        for (const auto& elem : container) {
            cout << elem << " ";
        }
        cout << endl;
    }

    bool empty() const {
        return container.empty();
    }

    size_t size() const {
        return container.size();
    }
};

// Специализация для Pair - нужно добавить операторы для Pair
template<>
void AssociativeList<Pair>::addAverageToEnd() {
    if (container.empty()) return;

    int sum_first = 0;
    double sum_second = 0.0;

    for (const auto& pair : container) {
        sum_first += pair.get_first();
        sum_second += pair.get_second();
    }

    Pair average(sum_first / container.size(), sum_second / container.size());
    container.push_back(average);
    cout << "Среднее арифметическое пары: " << average << endl;
}

template<>
void AssociativeList<Pair>::addMinMaxSum() {
    if (container.empty()) return;

    auto minmax = minmax_element(container.begin(), container.end());
    const Pair& min_pair = *minmax.first;
    const Pair& max_pair = *minmax.second;

    int sum_first = min_pair.get_first() + max_pair.get_first();
    double sum_second = min_pair.get_second() + max_pair.get_second();

    for (auto& pair : container) {
        pair = Pair(pair.get_first() + sum_first, pair.get_second() + sum_second);
    }
    cout << "Сумма мин и макс элементов: (" << sum_first << ", " << sum_second << ")" << endl;
}

template<>
void AssociativeList<Pair>::print() const {
    cout << "Список пар содержит:" << endl;
    for (const auto& pair : container) {
        cout << pair << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "=== ЗАДАЧА 1: multiset<double> ===" << endl;

    // Создание и заполнение
    multiset<double> double_ms = createDoubleMultiset();
    cout << "Исходный контейнер:" << endl;
    printDoubleMultiset(double_ms);

    // Добавление элементов
    addElementsToDoubleMultiset(double_ms);
    cout << "После добавления элементов:" << endl;
    printDoubleMultiset(double_ms);

    // Удаление элементов в диапазоне [2.0, 4.0]
    removeElementsInRange(double_ms, 2.0, 4.0);
    cout << "После удаления элементов в диапазоне [2.0, 4.0]:" << endl;
    printDoubleMultiset(double_ms);

    // Добавление среднего арифметического
    addAverageToEnd(double_ms);
    cout << "После добавления среднего арифметического:" << endl;
    printDoubleMultiset(double_ms);

    // Добавление суммы мин и макс к каждому элементу
    addMinMaxSum(double_ms);
    cout << "После добавления суммы мин и макс к каждому элементу:" << endl;
    printDoubleMultiset(double_ms);

    cout << "\n=== ЗАДАЧА 2: multiset<Pair> ===" << endl;

    // Создание и заполнение
    multiset<Pair> pair_ms = createPairMultiset();
    cout << "Исходный контейнер:" << endl;
    printPairMultiset(pair_ms);

    // Добавление элементов
    addElementsToPairMultiset(pair_ms);
    cout << "После добавления элементов:" << endl;
    printPairMultiset(pair_ms);

    // Удаление элементов в диапазоне
    removePairElementsInRange(pair_ms, Pair(2, 0.0), Pair(4, 10.0));
    cout << "После удаления элементов в диапазоне:" << endl;
    printPairMultiset(pair_ms);

    // Добавление среднего арифметического
    addAverageToPairMultiset(pair_ms);
    cout << "После добавления среднего арифметического:" << endl;
    printPairMultiset(pair_ms);

    // Добавление суммы мин и макс к каждому элементу
    addMinMaxSumToPairs(pair_ms);
    cout << "После добавления суммы мин и макс к каждому элементу:" << endl;
    printPairMultiset(pair_ms);

    cout << "\n=== ЗАДАЧА 3: Параметризированный класс ===" << endl;

    // Для double
    cout << "Работа с AssociativeList<double>:" << endl;
    AssociativeList<double> double_list;

    // Создаем вектор для передачи элементов
    vector<double> double_elements;
    double_elements.push_back(3.14);
    double_elements.push_back(2.71);
    double_elements.push_back(1.41);
    double_elements.push_back(2.0);
    double_elements.push_back(5.5);

    double_list.addElements(double_elements);
    double_list.print();

    double_list.removeElementsInRange(2.0, 4.0);
    cout << "После удаления элементов в диапазоне [2.0, 4.0]:" << endl;
    double_list.print();

    double_list.addAverageToEnd();
    double_list.print();

    double_list.addMinMaxSum();
    double_list.print();

    // Для Pair
    cout << "\nРабота с AssociativeList<Pair>:" << endl;
    AssociativeList<Pair> pair_list;

    // Создаем вектор для передачи элементов Pair
    vector<Pair> pair_elements;
    pair_elements.push_back(Pair(1, 2.5));
    pair_elements.push_back(Pair(3, 4.7));
    pair_elements.push_back(Pair(2, 1.8));
    pair_elements.push_back(Pair(5, 2.1));

    pair_list.addElements(pair_elements);
    pair_list.print();

    pair_list.removeElementsInRange(Pair(2, 0.0), Pair(4, 10.0));
    cout << "После удаления элементов в диапазоне:" << endl;
    pair_list.print();

    pair_list.addAverageToEnd();
    pair_list.print();

    pair_list.addMinMaxSum();
    pair_list.print();

    return 0;
}