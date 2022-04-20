// demoes hashmap implementation
// Mikhail Nesterenko
// 4/15/2014

#include "hashmap.hpp"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{

    hashmap<int, string> birthYears;
    birthYears.insert(pair<int, string>(1999, "Sue"));
    birthYears.insert(make_pair(1982, "Tarry"));

    // x will have type hashmap<int, int>::value_type*
    auto x = birthYears.find(1999);
    if (x != nullptr)
        cout << "4 maps to " << x->second << endl;
    else
        cout << "cannot find 4 in map" << endl;

    birthYears.erase(1999);

    auto x2 = birthYears.find(1999);
    if (x2 != nullptr)
        cout << "1999 maps to " << x2->second << endl;
    else
        cout << "cannot find 1999 in map" << endl;

    birthYears[1999] = "Reggie";
    birthYears[0] = "Jesus";

    auto x3 = birthYears.find(0);
    if (x3 != nullptr)
        cout << "0 maps to " << x3->second << endl;
    else
        cout << "cannot find 0 in map" << endl;

    hashmap<int, string> birthYears2;

    // entering entries with indexing operator
    birthYears2[1999] = "Mike";
    birthYears2[1946] = "Sharon";
    birthYears2[2552] = "Cortana";
    birthYears2[2011] = "Jacob";
    birthYears2[500] = "Bart";

    cout << "Enter new birth year: ";
    int num;
    cin >> num;
    cout << "Enter new name: ";
    string name;
    cin >> name;

    birthYears2[num] = name; // "unsafe" insert

    // searching map
    cout << "Enter birth year to look for: ";
    cin >> num;
    auto it = birthYears2.find(num);
    if (it != nullptr)
        cout << it->first << ":" << it->second << endl;
    else
        cout << "birth year not found" << endl;

    // removing from a map
    cout << "Enter birth year to erase: ";
    cin >> num;
    birthYears2.erase(num);
    // check if not there
    auto removed = birthYears2.find(num);
    if (removed == nullptr)
        cout << "Birth year removed successfully" << endl;
}
