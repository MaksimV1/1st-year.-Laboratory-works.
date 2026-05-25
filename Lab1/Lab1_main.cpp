#include <iostream>
#include "fraction.h"
using namespace std;

fraction make_fraction(double F, int S)
{
    fraction t;
    t.Init(F, S);
    return t;
}

void main()
{
    fraction A;
    fraction B;
    fraction C;
    A.Init(3.0, 2);
    A.Show();
    B.Read();
    C = make_fraction(1.2, 4);
    C.Show();
    cout << "A.Element = " << A.Element(5) << endl;
    cout << "B.Element = " << B.Element(5) << endl;
    cout << "C.Element = " << C.Element(5) << endl;
}
