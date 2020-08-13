/*
    * Project Name: EndlessListGroup
    * File Name: Source.cpp
    * Programmer(s): Ryan Durland, Michael Taylor, Joshua Reingold, Reed Landon
    * Last Modified: May 22, 2020
    * Project Purpose:
         This project adds support for a template object named EndlessList. The
        EndlessList is a circular list which uses a "cursor" to track where you
        are editing in the list, instead of a base node.
    * File Description:
         This source file includes the main function for this project. It runs
        a series of tests on the EndlessList to both prove the functionality of
        the class and to provide an example of proper class usage.
*/

#include <iostream>
#include "EndlessList.h"

using namespace std;

// For debugging, this will throw unexpected errors
const bool THROW_ERRORS = false;

/*
    * Function Name: main
    * Description:
         Starting point of the program. Tests the EndlessList object and sneds
        the formatted results to cout
    * Input:
        - void
    * Output:
        + int errorCode ~ A number representing program success
            0 -> No probems
            other -> Something definitely went wrong somewhere
    * Pre Conditions:
         If THROW_ERRORS is false, this function will attempt to catch and
        ignore any unexpected exceptions. If false, it will rethrow any
        unexpected exceptions
    * Post Conditions:
         cout will have the formatted output. The function will pause execution
        so that the user can review the data
*/
int main()
{
    // We'll test two main, stable datatypes: int and char
    EndlessList<int> intList;
    EndlessList<char> charList;
    // Tracking success and failiure stats
    unsigned int emptyPasses = 0;
    unsigned int emptyFails = 0;
    unsigned int fullPasses = 0;
    unsigned int fullFails = 0;
    unsigned int movePasses = 0;
    unsigned int moveFails = 0;
    unsigned int totalTests;
    // Let's format to a fancy table, so it's easy to read
    // Start by testing all the functions that shouldn't work with empty lists
    cout <<
        "|---------------------------------------------|\n"
        "|              Empty List Tests               |\n"
        "|---------------------------------------------|\n"
        "| Function | Result for int | Result for char |\n"
        "|----------|----------------|-----------------|\n";
    cout << "| remove   | ";
    try
    {
        intList.remove();
        cout << "Failed         | ";
        emptyFails++;
    }
    catch (out_of_range& e)
    {
        cout << "Passed         | ";
        emptyPasses++;
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        emptyFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        charList.remove();
        cout << "Failed          |\n";
        emptyFails++;
    }
    catch (out_of_range& e)
    {
        cout << "Passed          |\n";
        emptyPasses++;
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        emptyFails++;
        if (THROW_ERRORS)
            throw;
    }
    cout << "| getValue | ";
    try
    {
        intList.getValue();
        cout << "Failed         | ";
        emptyFails++;
    }
    catch (out_of_range& e)
    {
        cout << "Passed         | ";
        emptyPasses++;
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        emptyFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        charList.getValue();
        cout << "Failed          |\n";
        emptyFails++;
    }
    catch (out_of_range& e)
    {
        cout << "Passed          |\n";
        emptyPasses++;
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        emptyFails++;
        if (THROW_ERRORS)
            throw;
    }
    cout << "| setValue | ";
    try
    {
        intList.setValue(10);
        cout << "Failed         | ";
        emptyFails++;
    }
    catch (out_of_range& e)
    {
        cout << "Passed         | ";
        emptyPasses++;
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        emptyFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        charList.setValue('a');
        cout << "Failed          |\n";
        emptyFails++;
    }
    catch (out_of_range& e)
    {
        cout << "Passed          |\n";
        emptyPasses++;
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        emptyFails++;
        if (THROW_ERRORS)
            throw;
    }
    cout << "| getNext  | ";
    try
    {
        intList.getNext();
        cout << "Failed         | ";
        emptyFails++;
    }
    catch (out_of_range& e)
    {
        cout << "Passed         | ";
        emptyPasses++;
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        emptyFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        charList.getNext();
        cout << "Failed          |\n";
        emptyFails++;
    }
    catch (out_of_range& e)
    {
        cout << "Passed          |\n";
        emptyPasses++;
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        emptyFails++;
        if (THROW_ERRORS)
            throw;
    }
    // Test isEmpty, for convenience
    cout << "| isEmpty  | ";
    try
    {
        if (intList.isEmpty())
        {
            cout << "Passed         | ";
            emptyPasses++;
        }
        else
        {
            cout << "Failed         | ";
            emptyFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        emptyFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        if (charList.isEmpty())
        {
            cout << "Passed          |\n";
            emptyPasses++;
        }
        else
        {
            cout << "Failed          |\n";
            emptyFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        emptyFails++;
        if (THROW_ERRORS)
            throw;
    }
    // Testing with loaded (full) lists
    cout <<
        "|---------------------------------------------|\n"
        "|               Full List Tests               |\n"
        "|---------------------------------------------|\n"
        "| Function | Result for int | Result for char |\n"
        "|----------|----------------|-----------------|\n";
    // Load the lists with prime numbers (and 1) and vowels
    // We add an extra so we can immediately remove it
    // List will look like: 11, 1, 2, 3, 5, 7
    cout << "| addNext  | ";
    try
    {
        // If this fails, most others probably will too
        intList.addNext(1);
        intList.addNext(2);
        intList.addNext(3);
        intList.addNext(5);
        intList.addNext(7);
        intList.addNext(11);
        cout << "Passed         | ";
        fullPasses++;
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        fullFails++;
        if (THROW_ERRORS)
            throw;
    }
    // List will look like: 'a', 'a', 'e', 'i', 'o', 'u' 
    try
    {
        // If this fails, most others probably will too
        charList.addNext('a');
        charList.addNext('e');
        charList.addNext('i');
        charList.addNext('o');
        charList.addNext('u');
        charList.addNext('a');
        cout << "Passed          |\n";
        fullPasses++;
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        fullFails++;
        if (THROW_ERRORS)
            throw;
    }
    cout << "| remove   | ";
    try
    {
        if (intList.remove() == 11)
        {
            cout << "Passed         | ";
            fullPasses++;
        }
        else
        {
            cout << "Failed         | ";
            fullFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        fullFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        if (charList.remove() == 'a')
        {
            cout << "Passed          |\n";
            fullPasses++;
        }
        else
        {
            cout << "Failed          |\n";
            fullFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        fullFails++;
        if (THROW_ERRORS)
            throw;
    }
    cout << "| getValue | ";
    try
    {
        if (intList.getValue() == 1)
        {
            cout << "Passed         | ";
            fullPasses++;
        }
        else
        {
            cout << "Failed         | ";
            fullFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        fullFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        if (charList.getValue() == 'a')
        {
            cout << "Passed          |\n";
            fullPasses++;
        }
        else
        {
            cout << "Failed          |\n";
            fullFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        fullFails++;
        if (THROW_ERRORS)
            throw;
    }
    cout << "| setValue | ";
    try
    {
        if (intList.setValue(11) == 1)
        {
            cout << "Passed         | ";
            fullPasses++;
        }
        else
        {
            cout << "Failed         | ";
            fullFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        fullFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        if (charList.setValue('u') == 'a')
        {
            cout << "Passed          |\n";
            fullPasses++;
        }
        else
        {
            cout << "Failed          |\n";
            fullFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        fullFails++;
        if (THROW_ERRORS)
            throw;
    }
    cout << "| getNext  | ";
    try
    {
        if (intList.getNext() == 2)
        {
            cout << "Passed         | ";
            fullPasses++;
        }
        else
        {
            cout << "Failed         | ";
            fullFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        fullFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        if (charList.getNext() == 'e')
        {
            cout << "Passed          |\n";
            fullPasses++;
        }
        else
        {
            cout << "Failed          |\n";
            fullFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        fullFails++;
        if (THROW_ERRORS)
            throw;
    }
    cout << "| isEmpty  | ";
    try
    {
        if (!intList.isEmpty())
        {
            cout << "Passed         | ";
            fullPasses++;
        }
        else
        {
            cout << "Failed         | ";
            fullFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        fullFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        if (!charList.isEmpty())
        {
            cout << "Passed          |\n";
            fullPasses++;
        }
        else
        {
            cout << "Failed          |\n";
            fullFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        fullFails++;
        if (THROW_ERRORS)
            throw;
    }
    // This last section is reserved for moveToNext, since it's its own beast
    cout <<
        "|---------------------------------------------|\n"
        "|              moveToNext Tests               |\n"
        "|---------------------------------------------|\n"
        "| Version  | Result for int | Result for char |\n"
        "|----------|----------------|-----------------|\n";
    // To help make these tests easier, we'll carefully control what's in
    //  each list, as well as the cursor position
    // First, let's empty the lists
    while (!intList.isEmpty())
        intList.remove();
    while (!charList.isEmpty())
        charList.remove();
    cout << "| empty    | ";
    try
    {
        if (!intList.moveToNext(1))
        {
            cout << "Passed         | ";
            movePasses++;
        }
        else
        {
            cout << "Failed         | ";
            moveFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        moveFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        if (!charList.moveToNext('a'))
        {
            cout << "Passed          |\n";
            movePasses++;
        }
        else
        {
            cout << "Failed          |\n";
            moveFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        moveFails++;
        if (THROW_ERRORS)
            throw;
    }
    // Add a single numebr
    intList.addNext(2);
    charList.addNext('b');
    cout << "| single   | ";
    try
    {
        if (!intList.moveToNext(2))
        {
            cout << "Passed         | ";
            movePasses++;
        }
        else
        {
            cout << "Failed         | ";
            moveFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        moveFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        if (!charList.moveToNext('b'))
        {
            cout << "Passed          |\n";
            movePasses++;
        }
        else
        {
            cout << "Failed          |\n";
            moveFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        moveFails++;
        if (THROW_ERRORS)
            throw;
    }
    // Fill lists, all the way
    intList.addNext(3);
    intList.addNext(4);
    intList.addNext(5);
    intList.addNext(1);
    charList.addNext('c');
    charList.addNext('d');
    charList.addNext('e');
    charList.addNext('a');
    cout << "| for self | ";
    try
    {
        if (!intList.moveToNext(1))
        {
            cout << "Passed         | ";
            movePasses++;
        }
        else
        {
            cout << "Failed         | ";
            moveFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        moveFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        if (!charList.moveToNext('a'))
        {
            cout << "Passed          |\n";
            movePasses++;
        }
        else
        {
            cout << "Failed          |\n";
            moveFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        moveFails++;
        if (THROW_ERRORS)
            throw;
    }
    cout << "| for fake | ";
    try
    {
        if (!intList.moveToNext(0))
        {
            cout << "Passed         | ";
            movePasses++;
        }
        else
        {
            cout << "Failed         | ";
            moveFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        moveFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        if (!charList.moveToNext('z'))
        {
            cout << "Passed          |\n";
            movePasses++;
        }
        else
        {
            cout << "Failed          |\n";
            moveFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        moveFails++;
        if (THROW_ERRORS)
            throw;
    }
    cout << "| for four | ";
    try
    {
        if (intList.moveToNext(4))
        {
            cout << "Passed         | ";
            movePasses++;
        }
        else
        {
            cout << "Failed         | ";
            moveFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        moveFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        if (charList.moveToNext('d'))
        {
            cout << "Passed          |\n";
            movePasses++;
        }
        else
        {
            cout << "Failed          |\n";
            moveFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        moveFails++;
        if (THROW_ERRORS)
            throw;
    }
    cout << "| for last | ";
    try
    {
        if (intList.moveToNext(3))
        {
            cout << "Passed         | ";
            movePasses++;
        }
        else
        {
            cout << "Failed         | ";
            moveFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed         | ";
        moveFails++;
        if (THROW_ERRORS)
            throw;
    }
    try
    {
        if (charList.moveToNext('c'))
        {
            cout << "Passed          |\n";
            movePasses++;
        }
        else
        {
            cout << "Failed          |\n";
            moveFails++;
        }
    }
    catch (exception& e)
    {
        cout << "Failed          |\n";
        moveFails++;
        if (THROW_ERRORS)
            throw;
    }
    // It's finally over. Display the end stats
    cout << 
        "|---------------------------------------------|\n";
    totalTests = emptyPasses + emptyFails + fullPasses + fullFails
        + movePasses + moveFails;
    cout << "| Total tests: " << totalTests << endl;
    cout << "| Empty list fail count: " << emptyFails << endl;
    cout << "| Full list fail count: " << fullFails << endl;
    cout << "| moveToNext fail count: " << moveFails << endl;
    cout << "| Failure rate: "
        << (emptyFails + fullFails + moveFails) * 100. / totalTests
        << "%\n";
    cout << 
      //"|---------------------------------------------|\n";
        "|  *Please note that a high failure rate may\n"
        "|   be due to a chain reaction of one error\n"
        "|   instead of a large quantities of errors\n|\n\n";
    cout << "Press enter to exit the program\n";
    getchar();
    return 0;
}