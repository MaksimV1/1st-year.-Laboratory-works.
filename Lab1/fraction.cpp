#pragma once
#include <iostream>
#include "fraction.h"
#include <cmath>
using namespace std;

void fraction::Init(double F, int S)
{
	first = F;
	second = S;
}

void fraction::Read()
{
	cout << "\nfirst? ";
	cin >> first;
	cout << "\nsecond? ";
	cin >> second;
}

void fraction::Show()
{
	cout << "\nfirst = " << first;
	cout << "\nsecond = " << second << endl;
}

double fraction::Power()
{
	return pow(first, second);
}

double fraction::Element(int j)
{
	return first * pow(second, j);
}