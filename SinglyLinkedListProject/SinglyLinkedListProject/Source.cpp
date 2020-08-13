#include "LinkedList.h"
#include <iostream>
#include <string>

using std::cout;
using std::string;

int main()
{
    LinkedList<string> names;
    names.insertFront("Dave");
    names.insertFront("Charlie");
    names.insertFront("Ben");
    names.insertFront("Andy");

    auto display = [&names]() {
        for (unsigned int i = 0; i < names.getCount(); i++)
            cout << names.get(i) << '\n';
        cout << "\nBreak\n\n";
    };

    display();

    names.removeAt(2);

    display();

    names.insertAt(1, "Barry");

    display();

    getchar();
}