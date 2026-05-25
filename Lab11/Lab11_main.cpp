#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

// Класс Pair для задач 2 и 4
class Pair {
private:
    int first;
    double second;

public:
    // Конструкторы
    Pair() : first(0), second(0.0) {}
    Pair(int F, double S) : first(F), second(S) {}
    Pair(const Pair& t) : first(t.first), second(t.second) {}

    // Деструктор
    ~Pair() {}

    // Геттеры и сеттеры
    int get_first() const { return first; }
    double get_second() const { return second; }
    void set_first(int F) { first = F; }
    void set_second(double S) { second = S; }

    // Операторы присваивания и арифметические
    Pair& operator=(const Pair& t) {
        if (&t == this) return *this;
        first = t.first;
        second = t.second;
        return *this;
    }

    Pair operator+(int F) {
        Pair result(*this);
        result.first += F;
        return result;
    }

    Pair operator+(double S) {
        Pair result(*this);
        result.second += S;
        return result;
    }

    Pair operator-(const Pair& t) {
        Pair result(*this);
        result.first -= t.first;
        result.second -= t.second;
        return result;
    }

    // Операторы сравнения для priority_queue
    bool operator<(const Pair& other) const {
        return first < other.first;
    }

    bool operator>(const Pair& other) const {
        return first > other.first;
    }

    bool operator==(const Pair& other) const {
        return first == other.first && second == other.second;
    }

    // Дружественные функции для ввода/вывода
    friend istream& operator>>(istream& in, Pair& t) {
        cout << "First: ";
        in >> t.first;
        cout << "Second: ";
        in >> t.second;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Pair& t) {
        return out << t.first << " : " << t.second;
    }
};

// ============================================================================
// ЗАДАЧА 1: Список с элементами типа double (глобальные функции)
// ============================================================================

void task1_fill_list(list<double>& container) {
    container = { 1.5, 2.7, 3.2, 4.8, 5.1, 6.3, 7.9 };
    cout << "Список заполнен начальными значениями\n";
}

void task1_add_elements(list<double>& container) {
    container.push_back(8.5);
    container.push_front(0.5);
    cout << "Добавлены элементы в начало (0.5) и конец (8.5)\n";
}

void task1_remove_elements(list<double>& container) {
    container.remove_if([](double x) { return x < 2.0; });
    cout << "Удалены элементы меньше 2.0\n";
}

// Задание 3: Найти среднее арифметическое и добавить его в конец контейнера
void task1_find_average_and_add(list<double>& container) {
    if (container.empty()) return;

    double sum = accumulate(container.begin(), container.end(), 0.0);
    double average = sum / container.size();
    container.push_back(average);

    cout << "Среднее арифметическое: " << average << " добавлено в конец\n";
}

// Задание 4: Найти элементы с ключами из заданного диапазона и удалить их
void task1_remove_by_key_range(list<double>& container, double min_key, double max_key) {
    container.remove_if([min_key, max_key](double x) {
        return x >= min_key && x <= max_key;
        });
    cout << "Удалены элементы в диапазоне [" << min_key << ", " << max_key << "]\n";
}

// Задание 5: К каждому элементу добавить сумму минимального и максимального элементов
void task1_add_min_max_sum(list<double>& container) {
    if (container.empty()) return;

    auto minmax = minmax_element(container.begin(), container.end());
    double sum_min_max = *minmax.first + *minmax.second;

    for (auto& elem : container) {
        elem += sum_min_max;
    }

    cout << "К каждому элементу добавлена сумма мин и макс: " << sum_min_max << "\n";
}

void task1_print_list(const list<double>& container) {
    cout << "Содержимое списка: ";
    for (const auto& elem : container) {
        cout << elem << " ";
    }
    cout << "\n";
}

// ============================================================================
// ЗАДАЧА 2: Список с элементами типа Pair (глобальные функции)
// ============================================================================

void task2_fill_list(list<Pair>& container) {
    container = { Pair(1, 1.5), Pair(3, 2.7), Pair(5, 3.2), Pair(2, 4.8), Pair(7, 5.1) };
    cout << "Список Pair заполнен начальными значениями\n";
}

void task2_add_elements(list<Pair>& container) {
    container.push_back(Pair(8, 8.5));
    container.push_front(Pair(0, 0.5));
    cout << "Добавлены элементы Pair в начало (0:0.5) и конец (8:8.5)\n";
}

void task2_remove_elements(list<Pair>& container) {
    container.remove_if([](const Pair& p) { return p.get_first() < 2; });
    cout << "Удалены элементы Pair с first < 2\n";
}

// Задание 3: Найти среднее арифметическое и добавить его в конец
void task2_find_average_and_add(list<Pair>& container) {
    if (container.empty()) return;

    double sum_first = 0, sum_second = 0;
    for (const auto& p : container) {
        sum_first += p.get_first();
        sum_second += p.get_second();
    }

    int avg_first = static_cast<int>(sum_first / container.size());
    double avg_second = sum_second / container.size();

    Pair average(avg_first, avg_second);
    container.push_back(average);

    cout << "Среднее арифметическое Pair: (" << average << ") добавлено в конец\n";
}

// Задание 4: Найти элементы с ключами из заданного диапазона и удалить их
void task2_remove_by_key_range(list<Pair>& container, int min_key, int max_key) {
    container.remove_if([min_key, max_key](const Pair& p) {
        int key = p.get_first();
        return key >= min_key && key <= max_key;
        });
    cout << "Удалены элементы с ключами в диапазоне [" << min_key << ", " << max_key << "]\n";
}

// Задание 5: К каждому элементу добавить сумму минимального и максимального элементов
void task2_add_min_max_sum(list<Pair>& container) {
    if (container.empty()) return;

    auto min_it = min_element(container.begin(), container.end(),
        [](const Pair& a, const Pair& b) { return a.get_first() < b.get_first(); });
    auto max_it = max_element(container.begin(), container.end(),
        [](const Pair& a, const Pair& b) { return a.get_first() < b.get_first(); });

    int sum_min_max = min_it->get_first() + max_it->get_first();

    for (auto& elem : container) {
        elem.set_first(elem.get_first() + sum_min_max);
    }

    cout << "К каждому элементу добавлена сумма мин и макс first: " << sum_min_max << "\n";
}

void task2_print_list(const list<Pair>& container) {
    cout << "Содержимое списка Pair: ";
    for (const auto& elem : container) {
        cout << "(" << elem << ") ";
    }
    cout << "\n";
}

// ============================================================================
// ЗАДАЧА 3: Параметризированный класс Список
// ============================================================================

template<typename T>
class MyList {
private:
    list<T> data;

public:
    void fill_container() {
        if constexpr (is_same_v<T, double>) {
            data = { 1.5, 2.7, 3.2, 4.8, 5.1, 6.3, 7.9 };
        }
        else if constexpr (is_same_v<T, Pair>) {
            data = { Pair(1, 1.5), Pair(3, 2.7), Pair(5, 3.2), Pair(2, 4.8), Pair(7, 5.1) };
        }
        cout << "Параметризированный список заполнен\n";
    }

    void add_elements() {
        if constexpr (is_same_v<T, double>) {
            data.push_back(8.5);
            data.push_front(0.5);
        }
        else if constexpr (is_same_v<T, Pair>) {
            data.push_back(Pair(8, 8.5));
            data.push_front(Pair(0, 0.5));
        }
        cout << "Элементы добавлены в параметризированный список\n";
    }

    void remove_elements() {
        if constexpr (is_same_v<T, double>) {
            data.remove_if([](T x) { return x < 2.0; });
        }
        else if constexpr (is_same_v<T, Pair>) {
            data.remove_if([](const T& p) { return p.get_first() < 2; });
        }
        cout << "Элементы удалены из параметризированного списка\n";
    }

    // Задание 3: Найти среднее арифметическое и добавить его в конец
    void find_average_and_add() {
        if constexpr (is_same_v<T, double>) {
            if (data.empty()) return;

            T sum = accumulate(data.begin(), data.end(), T(0));
            T average = sum / data.size();
            data.push_back(average);

            cout << "Среднее арифметическое: " << average << " добавлено\n";
        }
        else if constexpr (is_same_v<T, Pair>) {
            if (data.empty()) return;

            double sum_first = 0, sum_second = 0;
            for (const auto& p : data) {
                sum_first += p.get_first();
                sum_second += p.get_second();
            }

            int avg_first = static_cast<int>(sum_first / data.size());
            double avg_second = sum_second / data.size();

            T average(avg_first, avg_second);
            data.push_back(average);

            cout << "Среднее арифметическое Pair: (" << average << ") добавлено\n";
        }
    }

    // Задание 4: Удалить элементы с ключами из диапазона
    void remove_by_key_range(double min_key, double max_key) {
        if constexpr (is_same_v<T, double>) {
            data.remove_if([min_key, max_key](T x) {
                return x >= min_key && x <= max_key;
                });
            cout << "Удалены элементы в диапазоне [" << min_key << ", " << max_key << "]\n";
        }
        else if constexpr (is_same_v<T, Pair>) {
            int min_k = static_cast<int>(min_key);
            int max_k = static_cast<int>(max_key);
            data.remove_if([min_k, max_k](const T& p) {
                int key = p.get_first();
                return key >= min_k && key <= max_k;
                });
            cout << "Удалены элементы с ключами в диапазоне [" << min_k << ", " << max_k << "]\n";
        }
    }

    // Задание 5: К каждому элементу добавить сумму мин и макс элементов
    void add_min_max_sum() {
        if constexpr (is_same_v<T, double>) {
            if (data.empty()) return;

            auto minmax = minmax_element(data.begin(), data.end());
            T sum_min_max = *minmax.first + *minmax.second;

            for (auto& elem : data) {
                elem += sum_min_max;
            }

            cout << "К каждому элементу добавлена сумма мин и макс: " << sum_min_max << "\n";
        }
        else if constexpr (is_same_v<T, Pair>) {
            if (data.empty()) return;

            auto min_it = min_element(data.begin(), data.end(),
                [](const T& a, const T& b) { return a.get_first() < b.get_first(); });
            auto max_it = max_element(data.begin(), data.end(),
                [](const T& a, const T& b) { return a.get_first() < b.get_first(); });

            int sum_min_max = min_it->get_first() + max_it->get_first();

            for (auto& elem : data) {
                elem.set_first(elem.get_first() + sum_min_max);
            }

            cout << "К каждому элементу добавлена сумма мин и макс first: " << sum_min_max << "\n";
        }
    }

    void print_container() const {
        cout << "Параметризированный список: ";
        for (const auto& elem : data) {
            cout << elem << " ";
        }
        cout << "\n";
    }

    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }
};

// ============================================================================
// ЗАДАЧА 4: Очередь с приоритетами с элементами типа Pair (глобальные функции)
// ============================================================================

void task4_fill_priority_queue(priority_queue<Pair>& container) {
    container.push(Pair(1, 1.5));
    container.push(Pair(5, 2.7));
    container.push(Pair(3, 3.2));
    container.push(Pair(7, 4.8));
    container.push(Pair(2, 5.1));
    cout << "Очередь с приоритетами заполнена\n";
}

void task4_add_elements(priority_queue<Pair>& container) {
    container.push(Pair(8, 8.5));
    container.push(Pair(0, 0.5));
    cout << "Элементы добавлены в очередь с приоритетами\n";
}

void task4_remove_elements(priority_queue<Pair>& container) {
    if (!container.empty()) {
        cout << "Удален элемент с наивысшим приоритетом: (" << container.top() << ")\n";
        container.pop();
    }
}

// Задание 3: Найти среднее арифметическое и добавить его в конец
void task4_find_average_and_add(priority_queue<Pair>& container) {
    if (container.empty()) return;

    priority_queue<Pair> temp = container;
    double sum_first = 0, sum_second = 0;
    int count = 0;

    while (!temp.empty()) {
        sum_first += temp.top().get_first();
        sum_second += temp.top().get_second();
        temp.pop();
        count++;
    }

    int avg_first = static_cast<int>(sum_first / count);
    double avg_second = sum_second / count;

    Pair average(avg_first, avg_second);
    container.push(average);

    cout << "Среднее арифметическое Pair: (" << average << ") добавлено\n";
}

// Задание 4: Удалить элементы с ключами из диапазона
void task4_remove_by_key_range(priority_queue<Pair>& container, int min_key, int max_key) {
    priority_queue<Pair> temp_queue;

    while (!container.empty()) {
        Pair current = container.top();
        container.pop();

        int key = current.get_first();
        if (!(key >= min_key && key <= max_key)) {
            temp_queue.push(current);
        }
    }

    container = temp_queue;
    cout << "Удалены элементы с ключами в диапазоне [" << min_key << ", " << max_key << "]\n";
}

// Задание 5: К каждому элементу добавить сумму минимального и максимального элементов
void task4_add_min_max_sum(priority_queue<Pair>& container) {
    if (container.empty()) return;

    priority_queue<Pair> temp = container;
    Pair max_elem = temp.top();
    Pair min_elem = max_elem;

    while (!temp.empty()) {
        Pair current = temp.top();
        temp.pop();
        if (current.get_first() < min_elem.get_first()) {
            min_elem = current;
        }
    }

    int sum_min_max = min_elem.get_first() + max_elem.get_first();

    // Пересоздаем очередь с обновленными значениями
    temp = container;
    priority_queue<Pair> new_queue;

    while (!temp.empty()) {
        Pair current = temp.top();
        temp.pop();
        current.set_first(current.get_first() + sum_min_max);
        new_queue.push(current);
    }

    container = new_queue;
    cout << "К каждому элементу добавлена сумма мин и макс first: " << sum_min_max << "\n";
}

void task4_print_priority_queue(priority_queue<Pair> container) {
    cout << "Содержимое очереди с приоритетами: ";
    while (!container.empty()) {
        cout << "(" << container.top() << ") ";
        container.pop();
    }
    cout << "\n";
}

// ============================================================================
// ЗАДАЧА 5: Параметризированный класс с адаптером очереди с приоритетами
// ============================================================================

template<typename T>
class MyPriorityQueue {
private:
    priority_queue<T> data;

public:
    void fill_container() {
        if constexpr (is_same_v<T, double>) {
            vector<double> values = { 1.5, 2.7, 3.2, 4.8, 5.1, 6.3, 7.9 };
            for (const auto& val : values) {
                data.push(val);
            }
        }
        else if constexpr (is_same_v<T, Pair>) {
            vector<Pair> values = { Pair(1, 1.5), Pair(5, 2.7), Pair(3, 3.2), Pair(7, 4.8), Pair(2, 5.1) };
            for (const auto& val : values) {
                data.push(val);
            }
        }
        cout << "Параметризированная очередь с приоритетами заполнена\n";
    }

    void add_elements() {
        if constexpr (is_same_v<T, double>) {
            data.push(8.5);
            data.push(0.5);
        }
        else if constexpr (is_same_v<T, Pair>) {
            data.push(Pair(8, 8.5));
            data.push(Pair(0, 0.5));
        }
        cout << "Элементы добавлены в параметризированную очередь\n";
    }

    void remove_elements() {
        if (!data.empty()) {
            cout << "Удален элемент с наивысшим приоритетом\n";
            data.pop();
        }
    }

    // Задание 3: Найти среднее арифметическое и добавить его в конец
    void find_average_and_add() {
        if constexpr (is_same_v<T, double>) {
            if (data.empty()) return;

            priority_queue<T> temp = data;
            T sum = 0;
            int count = 0;

            while (!temp.empty()) {
                sum += temp.top();
                temp.pop();
                count++;
            }

            T average = sum / count;
            data.push(average);

            cout << "Среднее арифметическое: " << average << " добавлено\n";
        }
        else if constexpr (is_same_v<T, Pair>) {
            if (data.empty()) return;

            priority_queue<T> temp = data;
            double sum_first = 0, sum_second = 0;
            int count = 0;

            while (!temp.empty()) {
                sum_first += temp.top().get_first();
                sum_second += temp.top().get_second();
                temp.pop();
                count++;
            }

            int avg_first = static_cast<int>(sum_first / count);
            double avg_second = sum_second / count;

            T average(avg_first, avg_second);
            data.push(average);

            cout << "Среднее арифметическое Pair: (" << average << ") добавлено\n";
        }
    }

    // Задание 4: Удалить элементы с ключами из диапазона
    void remove_by_key_range(double min_key, double max_key) {
        if constexpr (is_same_v<T, double>) {
            priority_queue<T> temp_queue;

            while (!data.empty()) {
                T current = data.top();
                data.pop();

                if (!(current >= min_key && current <= max_key)) {
                    temp_queue.push(current);
                }
            }

            data = temp_queue;
            cout << "Удалены элементы в диапазоне [" << min_key << ", " << max_key << "]\n";
        }
        else if constexpr (is_same_v<T, Pair>) {
            int min_k = static_cast<int>(min_key);
            int max_k = static_cast<int>(max_key);
            priority_queue<T> temp_queue;

            while (!data.empty()) {
                T current = data.top();
                data.pop();

                int key = current.get_first();
                if (!(key >= min_k && key <= max_k)) {
                    temp_queue.push(current);
                }
            }

            data = temp_queue;
            cout << "Удалены элементы с ключами в диапазоне [" << min_k << ", " << max_k << "]\n";
        }
    }

    // Задание 5: К каждому элементу добавить сумму мин и макс элементов
    void add_min_max_sum() {
        if constexpr (is_same_v<T, double>) {
            if (data.empty()) return;

            // Находим мин и макс элементы
            priority_queue<T> temp = data;
            T max_elem = temp.top();
            T min_elem = max_elem;

            while (!temp.empty()) {
                T current = temp.top();
                temp.pop();
                if (current < min_elem) min_elem = current;
            }

            T sum_min_max = min_elem + max_elem;

            // Пересоздаем очередь с обновленными значениями
            temp = data;
            priority_queue<T> new_queue;

            while (!temp.empty()) {
                new_queue.push(temp.top() + sum_min_max);
                temp.pop();
            }

            data = new_queue;
            cout << "К каждому элементу добавлена сумма мин и макс: " << sum_min_max << "\n";
        }
        else if constexpr (is_same_v<T, Pair>) {
            if (data.empty()) return;

            // Находим мин и макс элементы по first
            priority_queue<T> temp = data;
            T max_elem = temp.top();
            T min_elem = max_elem;

            while (!temp.empty()) {
                T current = temp.top();
                temp.pop();
                if (current.get_first() < min_elem.get_first()) min_elem = current;
            }

            int sum_min_max = min_elem.get_first() + max_elem.get_first();

            // Пересоздаем очередь с обновленными значениями
            temp = data;
            priority_queue<T> new_queue;

            while (!temp.empty()) {
                T current = temp.top();
                temp.pop();
                current.set_first(current.get_first() + sum_min_max);
                new_queue.push(current);
            }

            data = new_queue;
            cout << "К каждому элементу добавлена сумма мин и макс first: " << sum_min_max << "\n";
        }
    }

    void print_container() {
        cout << "Параметризированная очередь с приоритетами: ";
        priority_queue<T> temp = data;
        while (!temp.empty()) {
            cout << temp.top() << " ";
            temp.pop();
        }
        cout << "\n";
    }

    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }
};

// ============================================================================
// ГЛАВНАЯ ФУНКЦИЯ
// ============================================================================

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "=================================================================\n";
    cout << "ЛАБОРАТОРНАЯ РАБОТА: КОНТЕЙНЕРЫ STL\n";
    cout << "=================================================================\n\n";

    // ========================================================================
    // ЗАДАЧА 1: Список с элементами типа double (глобальные функции)
    // ========================================================================
    cout << "=== ЗАДАЧА 1: Список с элементами типа double ===\n";
    list<double> list1;

    task1_fill_list(list1);
    task1_print_list(list1);

    task1_add_elements(list1);
    task1_print_list(list1);

    task1_remove_elements(list1);
    task1_print_list(list1);

    cout << "\n--- Выполнение заданий 3-5 для задачи 1 ---\n";
    task1_find_average_and_add(list1);
    task1_print_list(list1);

    task1_remove_by_key_range(list1, 3.0, 6.0);
    task1_print_list(list1);

    task1_add_min_max_sum(list1);
    task1_print_list(list1);

    // ========================================================================
    // ЗАДАЧА 2: Список с элементами типа Pair (глобальные функции)
    // ========================================================================
    cout << "\n=== ЗАДАЧА 2: Список с элементами типа Pair ===\n";
    list<Pair> list2;

    task2_fill_list(list2);
    task2_print_list(list2);

    task2_add_elements(list2);
    task2_print_list(list2);

    task2_remove_elements(list2);
    task2_print_list(list2);

    cout << "\n--- Выполнение заданий 3-5 для задачи 2 ---\n";
    task2_find_average_and_add(list2);
    task2_print_list(list2);

    task2_remove_by_key_range(list2, 3, 6);
    task2_print_list(list2);

    task2_add_min_max_sum(list2);
    task2_print_list(list2);

    // ========================================================================
    // ЗАДАЧА 3: Параметризированный класс Список
    // ========================================================================
    cout << "\n=== ЗАДАЧА 3: Параметризированный класс Список ===\n";

    cout << "\n--- Работа с типом double ---\n";
    MyList<double> myList_double;

    myList_double.fill_container();
    myList_double.print_container();

    myList_double.add_elements();
    myList_double.print_container();

    myList_double.remove_elements();
    myList_double.print_container();

    cout << "\n--- Выполнение заданий 3-5 для задачи 3 (double) ---\n";
    myList_double.find_average_and_add();
    myList_double.print_container();

    myList_double.remove_by_key_range(3.0, 6.0);
    myList_double.print_container();

    myList_double.add_min_max_sum();
    myList_double.print_container();

    cout << "\n--- Работа с типом Pair ---\n";
    MyList<Pair> myList_pair;

    myList_pair.fill_container();
    myList_pair.print_container();

    myList_pair.add_elements();
    myList_pair.print_container();

    myList_pair.remove_elements();
    myList_pair.print_container();

    cout << "\n--- Выполнение заданий 3-5 для задачи 3 (Pair) ---\n";
    myList_pair.find_average_and_add();
    myList_pair.print_container();

    myList_pair.remove_by_key_range(3.0, 6.0);
    myList_pair.print_container();

    myList_pair.add_min_max_sum();
    myList_pair.print_container();

    // ========================================================================
    // ЗАДАЧА 4: Очередь с приоритетами с элементами типа Pair
    // ========================================================================
    cout << "\n=== ЗАДАЧА 4: Очередь с приоритетами с элементами типа Pair ===\n";
    priority_queue<Pair> pq;

    task4_fill_priority_queue(pq);
    task4_print_priority_queue(pq);

    task4_add_elements(pq);
    task4_print_priority_queue(pq);

    task4_remove_elements(pq);
    task4_print_priority_queue(pq);

    cout << "\n--- Выполнение заданий 3-5 для задачи 4 ---\n";
    task4_find_average_and_add(pq);
    task4_print_priority_queue(pq);

    task4_remove_by_key_range(pq, 2, 5);
    task4_print_priority_queue(pq);

    task4_add_min_max_sum(pq);
    task4_print_priority_queue(pq);

    // ========================================================================
    // ЗАДАЧА 5: Параметризированный класс с очередью с приоритетами
    // ========================================================================
    cout << "\n=== ЗАДАЧА 5: Параметризированный класс с очередью с приоритетами ===\n";

    cout << "\n--- Работа с типом double ---\n";
    MyPriorityQueue<double> myPQ_double;

    myPQ_double.fill_container();
    myPQ_double.print_container();

    myPQ_double.add_elements();
    myPQ_double.print_container();

    myPQ_double.remove_elements();
    myPQ_double.print_container();

    cout << "\n--- Выполнение заданий 3-5 для задачи 5 (double) ---\n";
    myPQ_double.find_average_and_add();
    myPQ_double.print_container();

    myPQ_double.remove_by_key_range(3.0, 6.0);
    myPQ_double.print_container();

    myPQ_double.add_min_max_sum();
    myPQ_double.print_container();

    cout << "\n--- Работа с типом Pair ---\n";
    MyPriorityQueue<Pair> myPQ_pair;

    myPQ_pair.fill_container();
    myPQ_pair.print_container();

    myPQ_pair.add_elements();
    myPQ_pair.print_container();

    myPQ_pair.remove_elements();
    myPQ_pair.print_container();

    cout << "\n--- Выполнение заданий 3-5 для задачи 5 (Pair) ---\n";
    myPQ_pair.find_average_and_add();
    myPQ_pair.print_container();

    myPQ_pair.remove_by_key_range(2.0, 5.0);
    myPQ_pair.print_container();

    myPQ_pair.add_min_max_sum();
    myPQ_pair.print_container();

    cout << "\n=================================================================\n";
    cout << "ЛАБОРАТОРНАЯ РАБОТА ЗАВЕРШЕНА\n";
    cout << "Все задания (3, 4, 5) выполнены для каждой из пяти задач\n";
    cout << "=================================================================\n";

    return 0;
}
