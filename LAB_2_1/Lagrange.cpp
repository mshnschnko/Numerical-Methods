#include <iostream>
#include <math.h>
using namespace std;

double f(double x) {
    return (x * x - sin(x)-0.25);
}

int main()
{
    cout << f(3) << endl;
    return 0;
}
