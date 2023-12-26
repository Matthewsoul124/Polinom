#include <iostream>
#include "TList.h"
#include "TPolinom.h"
using namespace std;


int main() {

    TPolinom sum;
    string str1, str2;

    cout << "Enter the first polynom\n";
    cin >> str1;
    TPolinom p1(str1);
    
    cout << "Enter the second polynom\n";
    cin >> str2;
    TPolinom p2(str2);

    sum = p1 + p2;

    cout << "First Polynom: " << p1.ToString() << endl;
    cout << "Second Polynom: " << p2.ToString() << endl;
    cout << "Result: " << sum.ToString() << endl;

    return 0;
}
