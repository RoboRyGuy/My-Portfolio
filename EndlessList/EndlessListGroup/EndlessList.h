/*
    * Project Name: EndlessListGroup
    * File Name: EndlessList.h
    * Programmer(s): Ryan Durland, Michael Taylor, Joshua Reingold, Reed Landon
    * Last Modified: May 22, 2020
    * Project Purpose:
         This project adds support for a template object named EndlessList. The
        EndlessList is a circular list which uses a "cursor" to track where you
        are editing in the list, instead of a base node.
    * File Description:
         This file is the template file for the EndlessList object. As such, it
        includes both the declerations for the object as well as all the source
        code required to compile the object.
*/
#ifndef _ENDLESS_LIST_
#define _ENDLESS_LIST_

#include <vector>

/*
    * Template Class Name: EndlessList
    * Description:
         The template list is a circular list which uses a "cursor" to track
        where you are editting the list, instead of a base node.
    * Member Data:
       > Template:
          - class E ~ The type of data the list will store
       > Private:
          - vector<E> list ~ The vector that actually contains the stored data
          - unsigned int cursorPos ~ The number that tracks where the cursor is
       > Public:
          + void
*/
template <class E>
class EndlessList
{
private:
    std::vector<E> list;
    unsigned int cursor = 0;

    /*
        * Function Name: stepCursor
        * Description:
             Steps the cursor one forward while keeping it in list bounds
        * Input:
            - void
        * Output:
            + void
        * Pre Conditions:
             None
        * Post Conditions:
             The cursor will be moved one forward, circling as necessary
    */
    inline void stepCursor()
    {
        cursor++;
        if (cursor >= list.size())
            cursor = 0;
    }

public:
    /*
        * Function Name: addNext
        * Description:
             Adds an item to the list right after the cursor, then moves the
            cursor to that new value. If the list is empty, this simply adds
            an item, and sets the cursor to that item
        * Input:
            - E value ~ The item to be added to the list
        * Output:
            + void
        * Pre Conditions:
             None
        * Post Conditions:
             The list will grow one; The cursor will be pointing at the new
            item
    */
    void addNext(E value)
    {
        if (isEmpty())
            list.push_back(value);
        else
            list.insert(list.begin() + (++cursor), value);
    }

    /*
        * Function Name: remove
        * Description:
             Removes the item that the cursor is pointing to, and moves the
            cursor to point at the next item in the list
        * Input:
            - void
        * Output:
            + E removed ~ The item that was removed from the list
        * Pre Conditions:
             The list must not be empty. If it is, this will throw
            a std::out_of_range
        * Post Conditions:
             The list will be one shorter, and the cursor will be moved one
            forward, so as to point at the next item in the list.
    */
    E remove()
    {
        // getValue checks if list is empty
        E temp = getValue();
        list.erase(list.begin() + cursor);
        if (cursor >= list.size())
            cursor = 0;
        return temp;
    }

    /*
        * Function Name: getValue
        * Description:
             Returns the item that the cursor is pointing at, without altering
            the list
        * Input:
            - void
        * Output:
            + E value ~ The item that the cursor is pointing at
        * Pre Conditions:
             The list must not be empty. If it is, this will throw
            a std::out_of_range
        * Post Conditions:
             None
    */
    E getValue() const
    {
        if (isEmpty())
            throw std::out_of_range("List is empty");
        return list[cursor];
    }

    /*
        * Function Name: setValue
        * Description:
             Changes the value of the item being pointed at to a new value
        * Input:
            - E value ~ The new value of the item
        * Output:
            + E oldValue ~ The original value of the item
        * Pre Conditions:
             The list must not be empty. If it is, this will throw
            a std::out_of_range
        * Post Conditions:
             The item's value will be altered
    */
    E setValue(E value)
    {
        // getValue checks if list is empty
        E data = getValue();
        list[cursor] = value;
        return data;
    }

    /*
        * Function Name: getNext
        * Description:
             Steps the cursor one forward, then returns the value that is being
            pointed at
        * Input:
            - void
        * Output:
            + E value ~ The new value the cursor is pointing at
        * Pre Conditions:
             The list must not be empty. If it is, this will throw
            a std::out_of_range
        * Post Conditions:
             The cursor will always be moved one forward, if there's an 
            exception. This may cause further errors if not handled properly.
    */
    E getNext()
    {
        stepCursor();
        // getValue checks if list is empty
        return getValue();
    }

    /*
        * Function Name: moveToNext
        * Description:
             Cycles through the list looking for a value, starting at the
            cursor's current position. Should the item be found, the cursor's
            position will be set to the item's position. Otherwise, the cursor
            will remain unmoved. Returns based on whether the item was found.
        * Input:
            - E value ~ The item to look for
        * Output:
            + bool wasFound ~ True if the value was found, false otherwise
        * Pre Conditions:
             None, but if the list is empty or only has one value then this
            function will always return false.
        * Post Conditions:
             If the item is found, the cursor's position will be moved to the
            item. Otherwise, the cursor's position will remain unchanged.
    */
    bool moveToNext(E value)
    {
        for (unsigned int i = 1; i < list.size(); i++)
        {
            stepCursor();
            // We don't have to check if list is empty
            if (list[cursor] == value)
                return true;
        }
        // Step back to start position. Works even if list has 0 or 1 elements
        stepCursor();
        return false;
    }

    /*
        * Function Name: isEmpty
        * Description:
             Checks if the list is empty
        * Input:
            - void
        * Output:
            + bool empty ~ True if the list is empty, false otherwise
        * Pre Conditions:
             None
        * Post Conditions:
             None
    */
    bool isEmpty() const
    {
        return list.empty();
    }
};

#endif