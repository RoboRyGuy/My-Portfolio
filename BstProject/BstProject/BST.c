#include "BST.h"
#include "Node.h"
#include <stdbool.h>
#include <stdlib.h>

void postOrderDelete(Node* node);
int inOrderList(double* arr, Node* node, int index);
bool recursiveContains(Node* node, double value);
bool recursiveInsert(Node* current, Node*parent, double value);
void deleteNode(BST* tree, Node* node, Node* parent);

BST* initializeBST()
{
    BST* tree = malloc(sizeof(BST));
    tree->count = 0;
    tree->root = NULL;
    return tree;
}

void deleteBST(BST* tree)
{
    //post order traversal to delete each node
    if (tree->count > 0)
        postOrderDelete(tree->root);
    //delete BST
    free(tree);
}

void postOrderDelete(Node* node)
{
    // Make sure to delete children first
    if (node->left != NULL)
        postOrderDelete(node->left);
    if (node->right != NULL)
        postOrderDelete(node->right);
    free(node);
}

double* list(BST* tree)
{
    if (tree->count == 0)
        return NULL;
    double* arr = calloc(tree->count, sizeof(double));
    inOrderList(arr, tree->root, 0);
    return arr;
}

int inOrderList(double* arr, Node* node, int index)
{
    // Why not just use a reference to an int instead
    // of passing it around through returns
    if (node->left != NULL)
        index = inOrderList(arr, node->left, index);
    arr[index++] = node->value;
    if (node->right != NULL)
        index = inOrderList(arr, node->right, index);
    return index;
}

bool contains(BST* tree, double value)
{
   return recursiveContains(tree->root, value);
}

bool recursiveContains(Node* node, double value)
{
    // Non-recursive conditions
    if (node == NULL)
        return false;
    else if (value == node->value)
        return true;
    // Recursive statement
    return recursiveContains(
            value < node->value ? node->left : node->right,
            value);
}

bool insert(BST* tree, double value)
{
    //if there are no nodes yet, make this value the root
    if (tree->count == 0)
    {
        tree->root = malloc(sizeof(Node));
        tree->root->value = value;
        tree->root->left = NULL;
        tree->root->right = NULL;
        tree->count++;
        return true;
    }
    //call recursive insert to handle the rest
    if (recursiveInsert(tree->root, NULL, value))
    {
        tree->count++;
        return true;
    }
    else
        return false;
}

bool recursiveInsert(Node* current, Node* parent, double value)
{
    if (current->value == value)
    {
        // Nice and simple
        return false;
    }
    Node* nextNode = value < current->value ? current->left : current->right;
    if (nextNode == NULL)
    {
        // Great, put it there
        Node* newNode = malloc(sizeof(Node));
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        if (value < current->value)
            current->left = newNode;
        else
            current->right = newNode;
        return true;
    }
    else
        return recursiveInsert(nextNode, current, value);
}

bool delete(BST* tree, double value)
{
    //handle if tree is empty
    if (tree->count == 0)
        return false;
    //find the value in the tree and its parent
    Node* node = tree->root;
    Node* parent = NULL;
    bool foundIt = (node->value == value);
    while (node != NULL && !foundIt) {
        if (value < node->value)
        {
            parent = node;
            node = node->left;
        }
        else if (value > node->value)
        {
            parent = node;
            node = node->right;
        }
        else
        {
            foundIt = true;
        }
    }
    if (!foundIt)
        return false;
    //call the deleteNode function to delete the found node
    deleteNode(tree, node, parent);
    tree->count--;
    return true;
}

void deleteNode(BST* tree, Node* node, Node* parent)
{
    Node* newChild;
    // Start with the easiest cases
    if (node->left == NULL)
        newChild = node->right;
    else if (node->right == NULL)
        newChild = node->left;
    // Necessary special case where we sliiide the tree
    else if ((node->left)->right == NULL)
    {
        newChild = node->left;
        newChild->right = node->right;
    }
    // Worst case scenario
    else
    {
        // Find a node value we can use to replace the old node
        Node* toMoveParent = node;
        Node* toMove = node->left;
        do
        {
            toMoveParent = toMove;
            toMove = toMove->right;
        } while (toMove->right != NULL);
        // Remove toMove from where it was in the tree
        toMoveParent->right = toMove->left;
        // Set up newChild
        newChild = toMove;
        newChild->right = node->right;
        newChild->left = node->left;
    }
    // Update our parent's reference
    if (parent == NULL)
        tree->root = newChild;
    else
    {
        if (node->value < parent->value)
            parent->left = newChild;
        else
            parent->right = newChild;
    }
    free(node);
}

bool isEmpty(BST* tree)
{
    return (tree->count == 0);
}

int size(BST* tree)
{
    return tree->count;
}
