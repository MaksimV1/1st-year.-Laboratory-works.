#pragma once
#include "Print.h"

class Magazin : public Print {
private:
    int pageCount;
    string group;

public:
    Magazin(const string& t = "", const string& a = "", int p = 0, const string& pub = "")
        : Print(t, a), pageCount(p), group(pub) {
    }

    void input() override {
        cout << "Enter the title: ";
        getline(cin, title);
        cout << "Enter the author: ";
        getline(cin, author);
        cout << "Enter the page count: ";
        cin >> pageCount;
        cin.ignore();
        cout << "Enter the publisher: ";
        getline(cin, group);
    }

    void output() const override {
        cout << "Title: " << title << ", Author: " << author
            << ", Pages: " << pageCount << ", Publisher: " << group << endl;
    }

    int getPageCount() const { return pageCount; }
    string getPublisher() const { return group; }
    void setPageCount(int p) { pageCount = p; }
    void setPublisher(const string& pub) { group = pub; }

    Magazin& operator=(const Magazin& other) {
        if (this != &other) {
            Print::operator=(other);
            pageCount = other.pageCount;
            group = other.group;
        }
        return *this;
    }

    // Операторы сравнения для дерева (по названию)
    bool operator<(const Magazin& other) const {
        return title < other.title;
    }

    bool operator>(const Magazin& other) const {
        return title > other.title;
    }

    bool operator==(const Magazin& other) const {
        return title == other.title;
    }

    bool operator!=(const Magazin& other) const {
        return !(*this == other);
    }
};