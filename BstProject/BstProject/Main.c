#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Node.h"
#include "BST.h"

void testStartEnd();
void testEmpty();
void testSorted();
void testReverseSorted();
void testBalanced();
void testGiant();
void printTree(BST* tree);
//void printNodes(Node* node, int spaces);
void printNodes(Node* node, bool* lines, int level, 
    bool isRightNode, double* data);

int main()
{
    // Being nice to whoever sees this in my portfolio
    printf("%s\n", "Warning: Your page will scroll a lot. Press Enter.");
    getchar();

    printf("%s\n", "==========================================");
    printf("%s\n", "             TESTING BST");
    printf("%s\n", "         1 = true, 0 = false");
    printf("%s\n", "==========================================");
    testStartEnd();
    printf("%s\n", "==========================================");
    testEmpty();
    printf("%s\n", "==========================================");
    testSorted();
    printf("%s\n", "==========================================");
    testReverseSorted();
    printf("%s\n", "==========================================");
    testBalanced();
    printf("%s\n", "==========================================");
    testGiant();
    //end
    getchar();
}

void testStartEnd()
{
    //test initializeBST
    BST* tree = initializeBST();
    printf("%s\n", "POST BST INITIALIZATION:");
    printf("tree is initialized = %i\n", (tree->count == 0));
    //test deleteBST
    deleteBST(tree);
    printf("%s\n", "POST BST DELETE:");
    printf("tree is initialized = %i\n", (tree->count == 0));
}

void testEmpty()
{
    //start
    BST* tree = initializeBST();
    //testing with no nodes
    printf("%s\n", "WITHOUT NODES:");
    //test list
    double* arr1 = list(tree);
    printf("tree list is empty = %i\n", (arr1 == NULL));
    //test contains
    printf("contains 7 = %i\n", contains(tree, 7));
    //test delete
    printf("deleted 7 = %i\n", delete(tree, 7));
    //test isEmpty
    printf("tree is empty = %i\n", isEmpty(tree));
    //test size
    printf("count = %i\n", size(tree));
    //end
    deleteBST(tree);
}

void testSorted()
{
    //start
    BST* tree = initializeBST();
    printf("%s\n", "WITH SORTED NODES:");
    //test adding unique values
    printf("add 3 = %i\n", insert(tree, 3));
    printf("add 6 = %i\n", insert(tree, 6));
    printf("add 7 = %i\n", insert(tree, 7));
    printf("add 13 = %i\n", insert(tree, 13));
    printf("add 14 = %i\n", insert(tree, 14));
    printTree(tree);
    //test adding a duplicate
    printf("add 6 again = %i\n", insert(tree, 6));
    //test the size function
    printf("count = %i\n", size(tree));
    //test contains with an existing value
    printf("contains 7 = %i\n", contains(tree, 7));
    //test delete with an existing value
    printf("deleting 7 = %i\n", delete(tree, 7));
    printTree(tree);
    //test delete with a non-existant value
    printf("deleting 8 = %i\n", delete(tree, 8));
    //check size again after deleting
    printf("count = %i\n", size(tree));
    //test contains with a non-existant value
    printf("contains 7 = %i\n", contains(tree, 7));
    //test list
    double* arr = list(tree);
    for (int i = 0; i < size(tree); i++)
        printf("%f ", arr[i]);
    printf("\n");
    free(arr);
    //end
    deleteBST(tree);
}

void testReverseSorted()
{
    //start
    BST* tree = initializeBST();
    printf("%s\n", "WITH REVERSE SORTED NODES:");
    //test adding unique values
    printf("add 14 = %i\n", insert(tree, 14));
    printf("add 13 = %i\n", insert(tree, 13));
    printf("add 7 = %i\n", insert(tree, 7));
    printf("add 6 = %i\n", insert(tree, 6));
    printf("add 3 = %i\n", insert(tree, 3));
    printTree(tree);
    //test adding a duplicate
    printf("add 6 again = %i\n", insert(tree, 6));
    //test the size function
    printf("count = %i\n", size(tree));
    //test contains with an existing value
    printf("contains 7 = %i\n", contains(tree, 7));
    //test delete with an existing value
    printf("deleting 7 = %i\n", delete(tree, 7));
    printTree(tree);
    //test delete with a non-existant value
    printf("deleting 8 = %i\n", delete(tree, 8));
    //check size again after deleting
    printf("count = %i\n", size(tree));
    //test contains with a non-existant value
    printf("contains 7 = %i\n", contains(tree, 7));
    //test list
    double* arr = list(tree);
    for (int i = 0; i < size(tree); i++)
        printf("%f ", arr[i]);
    printf("\n");
    free(arr);
    //end
    deleteBST(tree);
}

void testBalanced()
{
    // Start
    BST* tree = initializeBST();
    printf("%s\n", "WITH BALANCED NODES:");
    //test adding unique values
    printf("add 10 = %i\n", insert(tree, 10));
    printf("add 5 = %i\n", insert(tree, 5));
    printf("add 15 = %i\n", insert(tree, 15));
    printf("add 3 = %i\n", insert(tree, 3));
    printf("add 7 = %i\n", insert(tree, 7));
    printf("add 13 = %i\n", insert(tree, 13));
    printf("add 17 = %i\n", insert(tree, 17));
    printTree(tree);
    //test adding a duplicate
    printf("add duplicate 17 again = %i\n", insert(tree, 17));
    //test the size function
    printf("count = %i\n", size(tree));
    //test contains with an existing value
    printf("contains existing 3 = %i\n", contains(tree, 3));
    //test delete with an existing value
    printf("deleting existing 10 = %i\n", delete(tree, 10));
    printTree(tree);
    //test delete with a non-existant value
    printf("deleting non-existant 8 = %i\n", delete(tree, 8));
    //check size again after deleting
    printf("count = %i\n", size(tree));
    //test contains with a non-existant value
    printf("contains non-existant 7 = %i\n", contains(tree, 7));
    //test list
    double* arr = list(tree);
    for (int i = 0; i < size(tree); i++)
        printf("%f ", arr[i]);
    printf("\n");
    free(arr);
    //end
    deleteBST(tree);
}

void testGiant()
{
    // Start
    BST* tree = initializeBST();
    printf("%s\n", "WITH GIANT DATAPOOL:");
    // This test is somewhat random, but also auto-generated
    double enteredValues[50];
    double choice;
    for (int i = 0; i < 50; i++) {
        double newValue;
        bool tryAgain;
        do
        {
            tryAgain = false;
            // Truly random numbers, eh?
            newValue = rand() % 100; // Readability
            newValue += (rand() % 1000) * .001;
            if (rand() % 2 == 1)
                newValue *= -1;
            // Chance of prexistence is 1 in 200000. Even so...
            for (int j = 0; j < i; j++)
                if (enteredValues[j] == newValue)
                    tryAgain = true;
        } while (tryAgain);
        enteredValues[i] = newValue;
        printf("add %f = %i\n", newValue, insert(tree, newValue));
    }
    printTree(tree);
    //test adding a duplicate
    choice = enteredValues[15];
    printf("add duplicate %f again = %i\n", choice, insert(tree, choice));
    //test the size function
    printf("count = %i\n", size(tree));
    //test contains with an existing value
    choice = enteredValues[37];
    printf("contains existing %f = %i\n", choice, contains(tree, choice));
    //test delete with an existing value
    choice = enteredValues[23];
    printf("deleting existing %f = %i\n", choice, delete(tree, choice));
    printTree(tree);
    //test delete with a non-existant value
    choice = 101.223;
    printf("deleting non-existant %f = %i\n", choice, delete(tree, choice));
    //check size again after deleting
    printf("count = %i\n", size(tree));
    //test contains with a non-existant value
    choice = -105.263;
    printf("contains non-existant %f = %i\n", choice, contains(tree, choice));
    //test list
    double* arr = list(tree);
    printf("Tree in inorder list form:");
    for (int i = 0; i < size(tree); i++)
    {
        // I added some basic formatting
        if (i % 5 == 0)
            printf("\n ");
        if (arr[i] > 0)
            printf("+");
        if (arr[i] > -10 && arr[i] < 10)
            printf(" ");
        printf("%f, ", arr[i]);
    }
    printf("\n");
    free(arr);
    //end
    deleteBST(tree);
}

#pragma region OldVersion
/*
 * The following functions can be used to print out the entire tree structure horizontally
 * using a simple recursive function. It is good for testing correct insertion and deletion.
 */

/* Useful, but doesn't work so well when the tree gets really big
void printTree(BST* tree)
{
    printf("\n%s\n", "Current tree structure: ");
    printNodes(tree->root, 4);
    printf("\n");
}

void printNodes(Node* node, int spaces)
{
    int i;
    if (node != NULL)
    {
        printNodes(node->right, spaces + 10);
        for (i = 0; i < spaces; i++)
            printf(" ");
        printf("%f\n", node->value);
        printNodes(node->left, spaces + 10);
    }
}
*/
#pragma endregion

// Sorry for overwriting your version, but I wanted to add some features
// Mainly, lines between connected nodes, since it was sometimes hard to see
// It sorta just grew from there
void printTree(BST* tree)
{
    printf("\n%s\n", "Current tree structure: ");
    bool* lines = malloc(sizeof(bool));
    // True means space. This is because true is the default when malloc-ing
    lines[0] = true;
    double* treeData = malloc(sizeof(double) * 3); // Count, height, sum
    treeData[0] = 0;
    treeData[1] = 0;
    treeData[2] = 0;
    printNodes(tree->root, lines, 0, false, treeData);
    printf(" %s%i%s\n", "Printed ", (int)treeData[0], " nodes");
    printf(" %s%i%s\n", "Height: ", (int)treeData[1], " lines");
    printf(" %s%f\n", "Average value: ", treeData[2] / treeData[0]);
    printf("\n");
    // Cleanup
    free(lines);
    free(treeData);
}

// This is really inefficient when it comes to memory
// I'm just too lazy to implement a growable array at the moment
void printNodes(Node* node, bool* lines, int level, 
    bool isRightNode, double* data)
{
    const int HORIZONTAL_GAP = 9;
    // Each node is responsible for only lines touching it
    if (node->left != NULL)
    {
        // Duplicate our current formatting array
        bool* leftLines = malloc(sizeof(bool) * (level + 1));
        for (int i = 0; i < level; i++)
            leftLines[i] = lines[i];
        // Check if we need to remove our parent's line
        if (!isRightNode && level != 0)
            leftLines[level - 1] = true;
        // We want a line to our child
        leftLines[level] = false;
        printNodes(node->left, leftLines, level + 1, false, data);
        free(leftLines);
    }
    // We're just printing our own data here, with gaps and lines added in
    for (int i = 0; i < level; i++)
    {
        for (int j = 1; j < HORIZONTAL_GAP; j++)
            printf(" ");
        if (lines[i])
            printf(" ");
        else
            printf("|");
    }
    // Looks neater
    if (node->value >= 0)
        printf("+");
    printf("%f\n", node->value);
    // We're going to update the input data now
    data[0]++;
    data[1] = max(data[1], level);
    data[2] += node->value;
    // Same as with the left node, except for some logical symmetry
    if (node->right != NULL)
    {
        // Duplicate our current formatting array
        bool* rightLines = malloc(sizeof(bool) * (level + 1));
        for (int i = 0; i < level; i++)
            rightLines[i] = lines[i];
        // Check if we need to remove our parent's line
        if (isRightNode && level != 0)
            rightLines[level - 1] = true;
        // We want a line to our child
        rightLines[level] = false;
        printNodes(node->right, rightLines, level + 1, true, data);
        free(rightLines);
    }
}