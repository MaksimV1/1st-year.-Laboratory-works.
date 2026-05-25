#pragma once
#include <iostream>
#include "Pair.h"
using namespace std;
template <class T>
class Vector
{
private:
	Pair* data;
	int size;
	int capacity;


	void Resize() {
		capacity *= 2;
		Pair* new_data = new Pair[capacity, 99.0];
		for (int i = 0; i < size; ++i)
			new_data[i] = data[i];
		delete[] data;
		data = new_data;
	}

public:
	Vector() : size(0), capacity(1) {
		data = new Pair[capacity, 99.0];
	}

	~Vector() {
		delete[] data;
	}

	void PushBack(Pair value) {
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

	int Find(Pair value) const {
		for (int i = 0; i < size; ++i)
			if (data[i] == value)
				return i;
		return -1;
	}

	Pair& operator[](int index) {
		return data[index];
	}

	const Pair& operator[](int index) const {
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