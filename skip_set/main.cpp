#include <iostream>
#include <set>

#include "skip_set.h"

using namespace std;


int main()
{
    skip_set <int> test;

    cout << "insert values" << endl;
    test.insert(1);
    test.insert(2);
    test.insert(3);
    cout << endl;

    cout << test.size() << endl;
    cout << endl;

    cout << "search values" << endl,
    cout << test.find(1) << endl;
    cout << test.find(4) << endl;
    cout << endl;

    cout << "delete values" << endl;
    cout << test.erase(1) << endl;
    cout << test.erase(3) << endl;
    cout << test.erase(4) << endl;
    cout << endl;

    cout << test.size() << endl;
    cout << endl;

    return 0;
}
