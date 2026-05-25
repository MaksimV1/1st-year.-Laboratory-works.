#include <iostream>
#include <list>
#include <queue>
#include <map>
#include <algorithm>
#include <numeric>
#include <functional>
#include <vector>
#include <string>

using namespace std;

class Pair {
    int first;
    double second;
public:
    Pair() { first = 0; second = 0; }
    Pair(int F, double S) { first = F; second = S; }
    Pair(const Pair& t) { first = t.first; second = t.second; }
    ~Pair() {}

    int get_first() const { return first; }
    double get_second() const { return second; }
    void set_first(int F) { first = F; }
    void set_second(double S) { second = S; }

    Pair& operator=(const Pair& t);
    Pair operator+(int F) const;
    Pair operator+(double S) const;
    Pair operator-(const Pair& t) const;
    bool operator<(const Pair& other) const;
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

Pair Pair::operator+(int F) const {
    return Pair(first + F, second);
}

Pair Pair::operator+(double S) const {
    return Pair(first, second + S);
}

Pair Pair::operator-(const Pair& t) const {
    return Pair(first - t.first, second - t.second);
}

bool Pair::operator<(const Pair& other) const {
    return first < other.first;
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

// Задача 1: Последовательный контейнер (список)
class Task1 {
private:
    list<Pair> container;

public:
    void fillContainer() {
        container = { Pair(1, 1.5), Pair(3, 2.7), Pair(2, 3.1), Pair(5, 1.2), Pair(4, 4.8) };
        cout << "Контейнер заполнен элементами:\n";
        for_each(container.begin(), container.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n\n";
    }

    void replaceElements() {
        cout << "=== Замена элементов ===\n";

        // replace_if: заменить элементы с first > 3
        replace_if(container.begin(), container.end(),
            [](const Pair& p) { return p.get_first() > 3; },
            Pair(0, 0.0));

        cout << "После replace_if (first > 3 заменены на 0:0): ";
        for_each(container.begin(), container.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // replace_copy в новый контейнер
        list<Pair> copied;
        replace_copy(container.begin(), container.end(), back_inserter(copied),
            Pair(0, 0.0), Pair(10, 10.0));

        cout << "replace_copy (0:0 -> 10:10): ";
        for_each(copied.begin(), copied.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // replace_copy_if
        list<Pair> copied_if;
        replace_copy_if(container.begin(), container.end(), back_inserter(copied_if),
            [](const Pair& p) { return p.get_first() == 1; },
            Pair(99, 99.9));

        cout << "replace_copy_if (first == 1 -> 99:99.9): ";
        for_each(copied_if.begin(), copied_if.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // fill: заполнить первые 2 элемента
        fill_n(container.begin(), 2, Pair(7, 7.7));

        cout << "После fill_n (первые 2 элемента = 7:7.7): ";
        for_each(container.begin(), container.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n\n";
    }

    void removeElements() {
        cout << "=== Удаление элементов ===\n";

        // Восстановим контейнер
        container = { Pair(1, 1.5), Pair(3, 2.7), Pair(2, 3.1), Pair(5, 1.2), Pair(4, 4.8), Pair(2, 6.6) };

        cout << "Исходный контейнер: ";
        for_each(container.begin(), container.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // remove: удалить конкретный элемент
        auto new_end = remove(container.begin(), container.end(), Pair(2, 3.1));
        container.erase(new_end, container.end());

        cout << "После remove (2:3.1): ";
        for_each(container.begin(), container.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // remove_if: удалить элементы с first < 3
        new_end = remove_if(container.begin(), container.end(),
            [](const Pair& p) { return p.get_first() < 3; });
        container.erase(new_end, container.end());

        cout << "После remove_if (first < 3): ";
        for_each(container.begin(), container.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // remove_copy и remove_copy_if
        container = { Pair(1, 1.5), Pair(3, 2.7), Pair(2, 3.1), Pair(5, 1.2), Pair(4, 4.8) };

        list<Pair> removed_copy;
        remove_copy(container.begin(), container.end(), back_inserter(removed_copy), Pair(3, 2.7));

        cout << "remove_copy (удален 3:2.7): ";
        for_each(removed_copy.begin(), removed_copy.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        list<Pair> removed_copy_if;
        remove_copy_if(container.begin(), container.end(), back_inserter(removed_copy_if),
            [](const Pair& p) { return p.get_first() > 3; });

        cout << "remove_copy_if (удалены first > 3): ";
        for_each(removed_copy_if.begin(), removed_copy_if.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n\n";
    }

    void sortContainer() {
        cout << "=== Сортировка ===\n";

        // Восстановим контейнер
        container = { Pair(1, 1.5), Pair(3, 2.7), Pair(2, 3.1), Pair(5, 1.2), Pair(4, 4.8) };

        cout << "Исходный контейнер: ";
        for_each(container.begin(), container.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // Сортировка по возрастанию
        container.sort([](const Pair& a, const Pair& b) {
            return a.get_first() < b.get_first();
            });

        cout << "Сортировка по возрастанию first: ";
        for_each(container.begin(), container.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // Сортировка по убыванию
        container.sort([](const Pair& a, const Pair& b) {
            return a.get_first() > b.get_first();
            });

        cout << "Сортировка по убыванию first: ";
        for_each(container.begin(), container.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n\n";
    }

    void findElements() {
        cout << "=== Поиск элементов ===\n";

        Pair target(3, 2.7);
        auto found = find(container.begin(), container.end(), target);

        if (found != container.end()) {
            cout << "Элемент " << target << " найден\n";
        }
        else {
            cout << "Элемент " << target << " не найден\n";
        }

        // find_if: поиск элемента с условием
        auto found_if = find_if(container.begin(), container.end(),
            [](const Pair& p) { return p.get_first() == 5; });

        if (found_if != container.end()) {
            cout << "Элемент с first == 5 найден: " << *found_if << "\n";
        }
        else {
            cout << "Элемент с first == 5 не найден\n";
        }

        // count: подсчет конкретных элементов
        int count_exact = count(container.begin(), container.end(), Pair(5, 1.2));
        cout << "Количество элементов 5:1.2: " << count_exact << "\n";

        // count_if: подсчет элементов с first > 2
        int count = count_if(container.begin(), container.end(),
            [](const Pair& p) { return p.get_first() > 2; });
        cout << "Количество элементов с first > 2: " << count << "\n\n";
    }

    void calculateAverage() {
        cout << "=== Задание 3: Среднее арифметическое ===\n";

        if (container.empty()) return;

        double sum_first = 0, sum_second = 0;
        for_each(container.begin(), container.end(), [&](const Pair& p) {
            sum_first += p.get_first();
            sum_second += p.get_second();
            });

        Pair average(sum_first / container.size(), sum_second / container.size());
        container.push_back(average);

        cout << "Среднее арифметическое добавлено: " << average << "\n";
        cout << "Контейнер: ";
        for_each(container.begin(), container.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n\n";
    }

    void removeByRange() {
        cout << "=== Задание 4: Удаление по диапазону ===\n";

        int min_key = 2, max_key = 4;
        auto new_end = remove_if(container.begin(), container.end(),
            [min_key, max_key](const Pair& p) {
                return p.get_first() >= min_key && p.get_first() <= max_key;
            });
        container.erase(new_end, container.end());

        cout << "Удалены элементы с ключами от " << min_key << " до " << max_key << "\n";
        cout << "Контейнер: ";
        for_each(container.begin(), container.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n\n";
    }

    void addMinMaxSum() {
        cout << "=== Задание 5: Добавление суммы мин/макс ===\n";

        if (container.empty()) return;

        auto min_elem = min_element(container.begin(), container.end(),
            [](const Pair& a, const Pair& b) {
                return a.get_first() < b.get_first();
            });
        auto max_elem = max_element(container.begin(), container.end(),
            [](const Pair& a, const Pair& b) {
                return a.get_first() < b.get_first();
            });

        int sum = min_elem->get_first() + max_elem->get_first();

        for_each(container.begin(), container.end(), [sum](Pair& p) {
            p.set_first(p.get_first() + sum);
            });

        cout << "К каждому элементу добавлена сумма мин и макс (" << sum << ")\n";
        cout << "Контейнер: ";
        for_each(container.begin(), container.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n\n";
    }

    void runAll() {
        cout << "=== ЗАДАЧА 1: СПИСОК ===\n";
        fillContainer();
        replaceElements();
        removeElements();
        sortContainer();
        findElements();
        calculateAverage();
        removeByRange();
        addMinMaxSum();
    }
};

// Задача 2: Адаптер контейнера (очередь с приоритетами)
class Task2 {
private:
    priority_queue<Pair, vector<Pair>, function<bool(const Pair&, const Pair&)>> pq;

public:
    Task2() : pq([](const Pair& a, const Pair& b) { return a.get_first() < b.get_first(); }) {}

    void fillContainer() {
        vector<Pair> data = { Pair(1, 1.5), Pair(3, 2.7), Pair(2, 3.1), Pair(5, 1.2), Pair(4, 4.8) };

        for (const auto& p : data) {
            pq.push(p);
        }

        cout << "Очередь с приоритетами заполнена\n";
        cout << "Размер: " << pq.size() << "\n";

        // Показываем элементы в порядке приоритета (не извлекая)
        auto temp_pq = pq;
        cout << "Элементы в порядке приоритета: ";
        while (!temp_pq.empty()) {
            cout << temp_pq.top() << " ";
            temp_pq.pop();
        }
        cout << "\n\n";
    }

    void replaceElements() {
        cout << "=== Замена элементов в очереди ===\n";

        // Для работы с алгоритмами STL извлекаем в вектор
        vector<Pair> temp_vector;
        while (!pq.empty()) {
            temp_vector.push_back(pq.top());
            pq.pop();
        }

        cout << "Извлеченные элементы: ";
        for_each(temp_vector.begin(), temp_vector.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // replace_if
        replace_if(temp_vector.begin(), temp_vector.end(),
            [](const Pair& p) { return p.get_first() > 3; },
            Pair(0, 0.0));

        cout << "После replace_if (first > 3 -> 0:0): ";
        for_each(temp_vector.begin(), temp_vector.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // replace_copy
        vector<Pair> copied;
        replace_copy(temp_vector.begin(), temp_vector.end(), back_inserter(copied),
            Pair(0, 0.0), Pair(10, 10.0));

        cout << "replace_copy (0:0 -> 10:10): ";
        for_each(copied.begin(), copied.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // replace_copy_if
        vector<Pair> copied_if;
        replace_copy_if(temp_vector.begin(), temp_vector.end(), back_inserter(copied_if),
            [](const Pair& p) { return p.get_first() == 1; },
            Pair(99, 99.9));

        cout << "replace_copy_if (first == 1 -> 99:99.9): ";
        for_each(copied_if.begin(), copied_if.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // fill
        fill_n(temp_vector.begin(), 2, Pair(7, 7.7));

        cout << "После fill_n (первые 2 = 7:7.7): ";
        for_each(temp_vector.begin(), temp_vector.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // Возвращаем элементы в очередь
        for (const auto& p : temp_vector) {
            pq.push(p);
        }
        cout << "\n";
    }

    void removeElements() {
        cout << "=== Удаление элементов из очереди ===\n";

        // Извлекаем в вектор для работы с алгоритмами
        vector<Pair> temp_vector;
        while (!pq.empty()) {
            temp_vector.push_back(pq.top());
            pq.pop();
        }

        // Восстанавливаем исходные данные
        temp_vector = { Pair(1, 1.5), Pair(3, 2.7), Pair(2, 3.1), Pair(5, 1.2), Pair(4, 4.8), Pair(2, 6.6) };

        cout << "Исходный вектор: ";
        for_each(temp_vector.begin(), temp_vector.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // remove
        auto new_end = remove(temp_vector.begin(), temp_vector.end(), Pair(2, 3.1));
        temp_vector.erase(new_end, temp_vector.end());

        cout << "После remove (2:3.1): ";
        for_each(temp_vector.begin(), temp_vector.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // remove_if
        new_end = remove_if(temp_vector.begin(), temp_vector.end(),
            [](const Pair& p) { return p.get_first() < 3; });
        temp_vector.erase(new_end, temp_vector.end());

        cout << "После remove_if (first < 3): ";
        for_each(temp_vector.begin(), temp_vector.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // remove_copy и remove_copy_if
        vector<Pair> original = { Pair(1, 1.5), Pair(3, 2.7), Pair(2, 3.1), Pair(5, 1.2), Pair(4, 4.8) };

        vector<Pair> removed_copy;
        remove_copy(original.begin(), original.end(), back_inserter(removed_copy), Pair(3, 2.7));

        cout << "remove_copy (удален 3:2.7): ";
        for_each(removed_copy.begin(), removed_copy.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        vector<Pair> removed_copy_if;
        remove_copy_if(original.begin(), original.end(), back_inserter(removed_copy_if),
            [](const Pair& p) { return p.get_first() > 3; });

        cout << "remove_copy_if (удалены first > 3): ";
        for_each(removed_copy_if.begin(), removed_copy_if.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // Возвращаем элементы в очередь
        for (const auto& p : temp_vector) {
            pq.push(p);
        }
        cout << "\n";
    }

    void sortContainer() {
        cout << "=== Сортировка очереди ===\n";

        // Извлекаем в вектор
        vector<Pair> temp_vector;
        while (!pq.empty()) {
            temp_vector.push_back(pq.top());
            pq.pop();
        }

        // Восстанавливаем данные
        temp_vector = { Pair(1, 1.5), Pair(3, 2.7), Pair(2, 3.1), Pair(5, 1.2), Pair(4, 4.8) };

        cout << "Исходный вектор: ";
        for_each(temp_vector.begin(), temp_vector.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // sort по возрастанию
        sort(temp_vector.begin(), temp_vector.end(), [](const Pair& a, const Pair& b) {
            return a.get_first() < b.get_first();
            });

        cout << "Сортировка по возрастанию first: ";
        for_each(temp_vector.begin(), temp_vector.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // sort по убыванию
        sort(temp_vector.begin(), temp_vector.end(), [](const Pair& a, const Pair& b) {
            return a.get_first() > b.get_first();
            });

        cout << "Сортировка по убыванию first: ";
        for_each(temp_vector.begin(), temp_vector.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // Возвращаем в очередь
        for (const auto& p : temp_vector) {
            pq.push(p);
        }
        cout << "\n";
    }

    void findElements() {
        cout << "=== Поиск элементов в очереди ===\n";

        // Извлекаем в вектор для поиска
        vector<Pair> temp_vector;
        while (!pq.empty()) {
            temp_vector.push_back(pq.top());
            pq.pop();
        }

        // find
        Pair target(3, 2.7);
        auto found = find(temp_vector.begin(), temp_vector.end(), target);

        if (found != temp_vector.end()) {
            cout << "Элемент " << target << " найден\n";
        }
        else {
            cout << "Элемент " << target << " не найден\n";
        }

        // find_if
        auto found_if = find_if(temp_vector.begin(), temp_vector.end(),
            [](const Pair& p) { return p.get_first() == 5; });

        if (found_if != temp_vector.end()) {
            cout << "Элемент с first == 5 найден: " << *found_if << "\n";
        }
        else {
            cout << "Элемент с first == 5 не найден\n";
        }

        // count
        int count_exact = count(temp_vector.begin(), temp_vector.end(), Pair(5, 1.2));
        cout << "Количество элементов 5:1.2: " << count_exact << "\n";

        // count_if
        int count = count_if(temp_vector.begin(), temp_vector.end(),
            [](const Pair& p) { return p.get_first() > 2; });
        cout << "Количество элементов с first > 2: " << count << "\n";

        // Возвращаем в очередь
        for (const auto& p : temp_vector) {
            pq.push(p);
        }
        cout << "\n";
    }

    void calculateAverage() {
        cout << "=== Задание 3: Среднее арифметическое (очередь) ===\n";

        // Извлекаем в вектор
        vector<Pair> temp_vector;
        while (!pq.empty()) {
            temp_vector.push_back(pq.top());
            pq.pop();
        }

        if (temp_vector.empty()) return;

        double sum_first = 0, sum_second = 0;
        for_each(temp_vector.begin(), temp_vector.end(), [&](const Pair& p) {
            sum_first += p.get_first();
            sum_second += p.get_second();
            });

        Pair average(sum_first / temp_vector.size(), sum_second / temp_vector.size());
        temp_vector.push_back(average);

        cout << "Среднее арифметическое добавлено: " << average << "\n";
        cout << "Вектор: ";
        for_each(temp_vector.begin(), temp_vector.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // Возвращаем в очередь
        for (const auto& p : temp_vector) {
            pq.push(p);
        }
        cout << "\n";
    }

    void removeByRange() {
        cout << "=== Задание 4: Удаление по диапазону (очередь) ===\n";

        // Извлекаем в вектор
        vector<Pair> temp_vector;
        while (!pq.empty()) {
            temp_vector.push_back(pq.top());
            pq.pop();
        }

        int min_key = 2, max_key = 4;
        auto new_end = remove_if(temp_vector.begin(), temp_vector.end(),
            [min_key, max_key](const Pair& p) {
                return p.get_first() >= min_key && p.get_first() <= max_key;
            });
        temp_vector.erase(new_end, temp_vector.end());

        cout << "Удалены элементы с ключами от " << min_key << " до " << max_key << "\n";
        cout << "Вектор: ";
        for_each(temp_vector.begin(), temp_vector.end(), [](const Pair& p) {
            cout << p << " ";
            });
        cout << "\n";

        // Возвращаем в очередь
        for (const auto& p : temp_vector) {
            pq.push(p);
        }
        cout << "\n";
    }

    void addMinMaxSum() {
        cout << "=== Задание 5: Добавление суммы мин/макс (очередь) ===\n";

        // Извлекаем в вектор
        vector<Pair> temp_vector;
        while (!pq.empty()) {
            temp_vector.push_back(pq.top());
            pq.pop();
        }

        if (temp_vector.empty()) return;

        auto min_elem = min_element(temp_vector.begin(), temp_vector.end(),
            [](const Pair& a, const Pair& b) {
                return a.get_first() < b.get_first();
            });
        auto max_elem = max_element(temp_vector.begin(), temp_vector.end(),
            [](const Pair& a, const Pair& b) {
                return a.get_first() < b.get_first();
            });

        int sum = min_elem->get_first() + max_elem->get_first();

        for_each(temp_vector.begin(), temp_vector.end(), [sum](Pair& p) {
            p.set_first(p.get_first() + sum);
            });

        cout << "К каждому элементу добавлена сумма мин и макс (" << sum << ")\n";
        cout << "Вектор: ";
        for_each(temp_vector.begin(), temp_vector.end(), [](const Pair& p)
            {
                cout << p << " ";
            });
        cout << "\n";

        // Возвращаем в очередь
        for (const auto& p : temp_vector) {
            pq.push(p);
        }
        cout << "\n";
    }

    void runAll() {
        cout << "=== ЗАДАЧА 2: ОЧЕРЕДЬ С ПРИОРИТЕТАМИ ===\n";
        fillContainer();
        replaceElements();
        removeElements();
        sortContainer();
        findElements();
        calculateAverage();
        removeByRange();
        addMinMaxSum();
    }
};

// Задача 3: Ассоциативный контейнер (словарь)
class Task3 {
private:
    map<int, Pair> dictionary;

public:
    void fillContainer() {
        dictionary[1] = Pair(1, 1.5);
        dictionary[3] = Pair(3, 2.7);
        dictionary[2] = Pair(2, 3.1);
        dictionary[5] = Pair(5, 1.2);
        dictionary[4] = Pair(4, 4.8);

        cout << "Словарь заполнен:\n";
        for_each(dictionary.begin(), dictionary.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";
    }

    void replaceElements() {
        cout << "=== Замена элементов в словаре ===\n";

        // replace_if для значений (используем for_each так как map не поддерживает replace_if напрямую)
        for_each(dictionary.begin(), dictionary.end(), [](auto& pair) {
            if (pair.second.get_first() > 3) {
                pair.second = Pair(0, 0.0);
            }
            });

        cout << "После замены элементов с first > 3 на 0:0:\n";
        for_each(dictionary.begin(), dictionary.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";

        // replace_copy - копируем в вектор и применяем алгоритм
        vector<pair<int, Pair>> vec_copy;
        copy(dictionary.begin(), dictionary.end(), back_inserter(vec_copy));

        vector<pair<int, Pair>> replaced_copy;
        replace_copy(vec_copy.begin(), vec_copy.end(), back_inserter(replaced_copy),
            make_pair(4, Pair(0, 0.0)), make_pair(4, Pair(10, 10.0)));

        cout << "replace_copy (ключ 4 с 0:0 -> 10:10):\n";
        for_each(replaced_copy.begin(), replaced_copy.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";

        // replace_copy_if
        vector<pair<int, Pair>> replaced_copy_if;
        replace_copy_if(vec_copy.begin(), vec_copy.end(), back_inserter(replaced_copy_if),
            [](const auto& p) { return p.second.get_first() == 1; },
            make_pair(99, Pair(99, 99.9)));

        cout << "replace_copy_if (first == 1 -> 99:99.9):\n";
        for_each(replaced_copy_if.begin(), replaced_copy_if.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";

        // fill - заполняем несколько элементов одинаковым значением
        auto it = dictionary.begin();
        advance(it, 2);
        for_each(dictionary.begin(), it, [](auto& pair) {
            pair.second = Pair(7, 7.7);
            });

        cout << "После fill (первые 2 элемента = 7:7.7):\n";
        for_each(dictionary.begin(), dictionary.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";
    }

    void removeElements() {
        cout << "=== Удаление элементов из словаря ===\n";

        // Восстановим словарь
        dictionary.clear();
        dictionary[1] = Pair(1, 1.5);
        dictionary[3] = Pair(3, 2.7);
        dictionary[2] = Pair(2, 3.1);
        dictionary[5] = Pair(5, 1.2);
        dictionary[4] = Pair(4, 4.8);
        dictionary[6] = Pair(2, 6.6);

        cout << "Исходный словарь:\n";
        for_each(dictionary.begin(), dictionary.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";

        // remove - удаляем конкретное значение
        auto it = dictionary.begin();
        while (it != dictionary.end()) {
            if (it->second == Pair(2, 3.1)) {
                it = dictionary.erase(it);
            }
            else {
                ++it;
            }
        }

        cout << "После remove (значение 2:3.1):\n";
        for_each(dictionary.begin(), dictionary.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";

        // remove_if - удаляем элементы с условием
        it = dictionary.begin();
        while (it != dictionary.end()) {
            if (it->second.get_first() < 3) {
                it = dictionary.erase(it);
            }
            else {
                ++it;
            }
        }

        cout << "После remove_if (first < 3):\n";
        for_each(dictionary.begin(), dictionary.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";

        // remove_copy и remove_copy_if - работаем с векторами
        map<int, Pair> original_dict = { {1, Pair(1, 1.5)}, {3, Pair(3, 2.7)}, {2, Pair(2, 3.1)},
                                       {5, Pair(5, 1.2)}, {4, Pair(4, 4.8)} };

        vector<pair<int, Pair>> vec_original(original_dict.begin(), original_dict.end());

        vector<pair<int, Pair>> removed_copy;
        remove_copy(vec_original.begin(), vec_original.end(), back_inserter(removed_copy),
            make_pair(3, Pair(3, 2.7)));

        cout << "remove_copy (удален 3:2.7):\n";
        for_each(removed_copy.begin(), removed_copy.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";

        vector<pair<int, Pair>> removed_copy_if;
        remove_copy_if(vec_original.begin(), vec_original.end(), back_inserter(removed_copy_if),
            [](const auto& p) { return p.second.get_first() > 3; });

        cout << "remove_copy_if (удалены first > 3):\n";
        for_each(removed_copy_if.begin(), removed_copy_if.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";
    }

    void sortContainer() {
        cout << "=== Сортировка словаря ===\n";

        // Словарь автоматически отсортирован по ключам
        cout << "Словарь автоматически отсортирован по ключам:\n";
        for_each(dictionary.begin(), dictionary.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";

        // Для сортировки по значениям используем вектор пар
        vector<pair<int, Pair>> vec(dictionary.begin(), dictionary.end());

        // sort по возрастанию значений
        sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
            return a.second.get_first() < b.second.get_first();
            });

        cout << "Сортировка по возрастанию значений first:\n";
        for_each(vec.begin(), vec.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";

        // sort по убыванию значений
        sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
            return a.second.get_first() > b.second.get_first();
            });

        cout << "Сортировка по убыванию значений first:\n";
        for_each(vec.begin(), vec.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";
    }

    void findElements() {
        cout << "=== Поиск элементов в словаре ===\n";

        // find по ключу
        auto found = dictionary.find(3);
        if (found != dictionary.end()) {
            cout << "Элемент с ключом 3 найден: " << found->second << "\n";
        }
        else {
            cout << "Элемент с ключом 3 не найден\n";
        }

        // find_if по значению
        auto found_if = find_if(dictionary.begin(), dictionary.end(),
            [](const auto& pair) {
                return pair.second.get_first() == 5;
            });

        if (found_if != dictionary.end()) {
            cout << "Элемент со значением first=5 найден с ключом: " << found_if->first << "\n";
        }
        else {
            cout << "Элемент со значением first=5 не найден\n";
        }

        // count по ключу
        int count_key = dictionary.count(4);
        cout << "Количество элементов с ключом 4: " << count_key << "\n";

        // count_if по значению
        int count = count_if(dictionary.begin(), dictionary.end(),
            [](const auto& pair) {
                return pair.second.get_first() > 3;
            });
        cout << "Количество элементов с first > 3: " << count << "\n\n";
    }

    void calculateAverage() {
        cout << "=== Задание 3: Среднее арифметическое (словарь) ===\n";

        if (dictionary.empty()) return;

        double sum_first = 0, sum_second = 0;
        for_each(dictionary.begin(), dictionary.end(), [&](const auto& pair) {
            sum_first += pair.second.get_first();
            sum_second += pair.second.get_second();
            });

        Pair average(sum_first / dictionary.size(), sum_second / dictionary.size());

        // Находим максимальный ключ и добавляем после него
        int max_key = dictionary.empty() ? 0 : dictionary.rbegin()->first;
        dictionary[max_key + 1] = average;

        cout << "Среднее арифметическое добавлено с ключом " << (max_key + 1) << ": " << average << "\n";
        cout << "Словарь:\n";
        for_each(dictionary.begin(), dictionary.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";
    }

    void removeByRange() {
        cout << "=== Задание 4: Удаление по диапазону ключей (словарь) ===\n";

        int min_key = 2, max_key = 4;

        auto it = dictionary.lower_bound(min_key);
        auto end_it = dictionary.upper_bound(max_key);

        cout << "Удаляем элементы с ключами от " << min_key << " до " << max_key << "\n";
        dictionary.erase(it, end_it);

        cout << "Словарь после удаления:\n";
        for_each(dictionary.begin(), dictionary.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";
    }

    void addMinMaxSum() {
        cout << "=== Задание 5: Добавление суммы мин/макс (словарь) ===\n";

        if (dictionary.empty()) return;

        auto min_elem = min_element(dictionary.begin(), dictionary.end(),
            [](const auto& a, const auto& b) {
                return a.second.get_first() < b.second.get_first();
            });
        auto max_elem = max_element(dictionary.begin(), dictionary.end(),
            [](const auto& a, const auto& b) {
                return a.second.get_first() < b.second.get_first();
            });

        int sum = min_elem->second.get_first() + max_elem->second.get_first();

        for_each(dictionary.begin(), dictionary.end(), [sum](auto& pair) {
            pair.second.set_first(pair.second.get_first() + sum);
            });

        cout << "К каждому элементу добавлена сумма мин и макс (" << sum << ")\n";
        cout << "Словарь:\n";
        for_each(dictionary.begin(), dictionary.end(), [](const auto& pair) {
            cout << "Key: " << pair.first << " Value: " << pair.second << "\n";
            });
        cout << "\n";
    }

    void runAll() {
        cout << "=== ЗАДАЧА 3: СЛОВАРЬ ===\n";
        fillContainer();
        replaceElements();
        removeElements();
        sortContainer();
        findElements();
        calculateAverage();
        removeByRange();
        addMinMaxSum();
    }
};

// Главная функция
int main() {
    setlocale(LC_ALL, "Russian");
    cout << "=== ЛАБОРАТОРНАЯ РАБОТА: STL КОНТЕЙНЕРЫ И АЛГОРИТМЫ ===\n\n";

    // Задача 1: Список
    Task1 task1;
    task1.runAll();

    cout << "\n" << string(60, '=') << "\n\n";

    // Задача 2: Очередь с приоритетами
    Task2 task2;
    task2.runAll();

    cout << "\n" << string(60, '=') << "\n\n";

    // Задача 3: Словарь
    Task3 task3;
    task3.runAll();

    cout << "\n=== ПРОГРАММА ЗАВЕРШЕНА ===\n";

    return 0;
}