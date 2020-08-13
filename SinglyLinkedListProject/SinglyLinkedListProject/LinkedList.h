#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include <stdexcept>
#include <iostream>

template <typename T>
struct Node
{
    Node<T>* previous;
    T data;
    Node<T>* next;
};

template <typename T>
class LinkedList
{
private:
    Node<T>* head;
    unsigned int count;

    Node<T>* getNode(const unsigned int index)
    {
        if (index > count)
            throw std::out_of_range("Error 2");

        Node<T>* curr = head;
        if (index > count / 2)
        {
            for (unsigned int i = count; i > index; i--)
                curr = curr->previous;
        }
        else
        {
            for (unsigned int i = 0; i < index; i++)
                curr = curr->next;
        }
        return curr;
    }

public:
    LinkedList()
    {
        head = nullptr;
        count = 0;
    }

    void insertFront(const T data)
    {
        Node<T>* oldHead = head;
        head = new Node<T>;
        head->data = data;

        if (count == 0)
        {
            head->next = head;
            head->previous = head;
        }
        else
        {
            head->next = oldHead;
            head->previous = oldHead->previous;
            oldHead->previous->next = head;
            oldHead->previous = head;
        }
        count++;
        return;
    }

    void insertAt(const unsigned int index, const T data)
    {
        if (index > count || index < 0)
            throw std::out_of_range("Error");

        else if (index == 0)
        {
            insertFront(data);
            return;
        }

        Node<T>* justBefore = getNode(index - 1);

        Node<T>* newNode = new Node<T>;
        newNode->data = data;
        newNode->next = justBefore->next;
        newNode->previous = justBefore;
        newNode->next->previous = newNode;
        justBefore->next = newNode;

        count++;
        return;
    }

    void removeAt(const unsigned int index)
    {
        if (index > count)
            throw std::out_of_range("Error 3");

        Node<T>* justBefore = getNode(index - 1);

        justBefore->next = justBefore->next->next;
        delete(justBefore->next->previous);
        justBefore->next->previous = justBefore;

        count--;
        return;
    }

    unsigned getCount() 
    { 
        return count; 
    }

    T get(const unsigned int index)
    {
        return getNode(index)->data;
    }

    bool operator==(const LinkedList<T> &other)
    {
        if (count != other.count)
            return false;

        Node<T>* myNode = head;
        Node<T>* otherNode = other.head;

        for (int i = 0; i < count; i++)
        {
            if (myNode->data != otherNode->data)
                return false;
            myNode = myNode->next;
            otherNode = otherNode->next;
        }
        return true;
    }
};

#endif