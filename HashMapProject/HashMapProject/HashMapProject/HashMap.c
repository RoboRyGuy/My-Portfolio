#pragma warning(disable : 4996)
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>
#include "HashMap.h"

/*
 * Function: getLoadFactor
*/
double getLoadFactor(HashMap* map)
{
    int count = 0;
    for (int i = 0; i < map->capacity; i++)
        if (map->nodes[i] != NULL)
            count++;
    return count / map->capacity;
}

/*
 * Function: isPrime
*/
bool isPrime(int num)
{
    if (num <= 1) return false;
    if (num % 2 == 0 && num > 2) return false;
    for (int i = 3; i < num / 2; i++)
        if (num % i == 0)
            return false;
    return true;
}

/*
 * Function: rehash
*/
void rehash(HashMap* map)
{
    // Calculate new size
    int originalSize = map->capacity;
    map->capacity *= 2;
    while (!isPrime(++(map->capacity)));
    // Save all the original data from the map
    Node** tempArray = malloc(sizeof(Node*) * originalSize);
    for (int i = 0; i < originalSize; i++)
        tempArray[i] = map->nodes[i];
    // Remove all data from map
    free(map->nodes);
    map->count = 0;
    // New, bigger node array
    map->nodes = malloc(sizeof(Node*) * map->capacity);
    for (int i = 0; i < map->capacity; i++)
        map->nodes[i] = NULL;
    // Now just add all that data back in
    for (int i = 0; i < originalSize; i++)
    {
        Node* curr = tempArray[i];
        while (curr != NULL) {
            Node* tempRef = curr;
            insert(map, curr->key, curr->value);
            curr = curr->next;
            free(tempRef);
        }
    }
    // Cleanup
    free(tempArray);
}

/*
 * Function: hash
 * Description: Calculates the hash index based on a C-string key
 * Input:
 *     key - the C-string key
 *     capacity - the number of buckets in the HashMap
 * Output:
 *    int - the hash index
 */
int hash(char key[], int capacity)
{
    char* str = tolower(key);
    int length = strlen(str);
    int hash = 1315423911;
    for (unsigned int i = 0; i < length; ++str, ++i)
        hash ^= ((hash << 5) + (*str) + (hash >> 2));
    int index = abs(hash) % capacity;
    return index;
}

/*
 * Function: initializeHashMap
 * Description: Creates a new HashMap on the heap and returns a pointer to it.
 * Output:
 *     HashMap* - a pointer to the new HashMap
 */
HashMap* initializeHashMap()
{
    HashMap* map = malloc(sizeof(HashMap));
    map->capacity = 97;
    map->count = 0;
    map->nodes = malloc(sizeof(Node*) * map->capacity);
    for (int i = 0; i < map->capacity; i++)
        map->nodes[i] = NULL;
    return map;
}

/*
 * Fuction: deleteHashMap
 * Description: Iteratively frees every dynamic node in each list and then
 *              frees the HashMap.
 * Input:
 *     map - the HashMap
 */
void deleteHashMap(HashMap* map)
{
    Node* curr;
    Node* prev;
    for (int i = 0; i < map->capacity; i++)
    {
        if (map->nodes[i] != NULL)
        {
            curr = map->nodes[i];
            while (curr != NULL)
            {
                prev = curr;
                curr = curr->next;
                free(prev);
            }
        }   
    }
    free(map);
}

/*
 * Function: contains
 * Description: Checks if the given HashMap contains the the
                given key.
 * Input:
 *     map - the HashMap
 *     key - the C-string key
 * Output:
 *     bool - true if the map contains the key, false if not
 */
bool contains(HashMap* map, char key[])
{
    int index = hash(key, map->capacity);
    if (map->nodes[index] == NULL)
        return false;
    Node* curr = map->nodes[index];
    while (curr != NULL)
    {
        if (strcmp(tolower(curr->key), tolower(key)) == 0)
            return true;
        else
            curr = curr->next;
    }
    return false;
}

/*
 * Function: insert
 * Description: Adds the given value to the given HashMap, or replaces 
                the value if the key already exists.
 * Input:
 *     map - the HashMap
 *     key - the C-string key
 *     value - the value to be stored
 */
void insert(HashMap* map, char key[], double value)
{
    if (getLoadFactor(map) > .9)
        rehash(map);
    //hash the key
    int index = hash(key, map->capacity);
    //find the list in the map where it belongs
    Node* node = map->nodes[index];
    //make sure key is not already in the list
    while (node != NULL) {
        char* nodeKey = node->key;
        if (strcmp(tolower(node->key), tolower(key)) == 0) {
            //replace data
            node->value = value;
            return;
        }
        node = node->next;
    }
    //make a new node and place it at the start of the list
    Node* newNode = malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = map->nodes[index];
    map->nodes[index] = newNode;
    map->count++;
}

/*
 * Function: get
 * Description: Returns the value with the given key if it exists in the 
                given HashMap.
 * Input:
 *     map - the HashMap
 *     key - the C-string key
 * Output:
 *     double - the value at the given key, or a DBL_MAX if key doesn't exist
 */
double get(HashMap* map, char key[])
{
    int index = hash(key, map->capacity);
    if (map->nodes[index] == NULL)
    {
        return DBL_MAX;
    }
    Node* curr = map->nodes[index];
    while (curr != NULL)
    {
        if (strcmp(tolower(curr->key), tolower(key)) == 0)
            return curr->value;
        else
            curr = curr->next;
    }
    return DBL_MAX;
}

/*
 * Function: delete
 * Description: Removes the value with the given key from the given HashMap.
 * Input:
 *     map - the HashMap
 *     key - the C-string key
 * Output:
 *     bool - true if the map contained the key, false if not
 */
bool delete(HashMap* map, char key[])
{
    int index = hash(key, map->capacity);
    if (map->nodes[index] == NULL)
        return false;
    Node* curr = map->nodes[index];
    Node* prev = NULL;
    while (curr != NULL)
    {
        if (strcmp(tolower(curr->key), tolower(key)) == 0)
        {
            if (prev == NULL) //first node
                map->nodes[index] = curr->next;
            else
                prev->next = curr->next;
            free(curr);
            map->count--;
            return true;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
    return false;
}
