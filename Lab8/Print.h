#pragma once
#include <iostream>
#include <string>
using namespace std;

class Print 
{
protected:
    string title;
    string author;
public:
    Print(const string& t = "", const string& a = "") : title(t), author(a) {}
    virtual ~Print() {}
    virtual void input() = 0;
    virtual void output() const = 0;
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    void setTitle(const string& t) { title = t; }
    void setAuthor(const string& a) { author = a; }
    Print& operator=(const Print& other) {
        if (this != &other) {
            title = other.title;
            author = other.author;
        }
        return *this;
    }
};