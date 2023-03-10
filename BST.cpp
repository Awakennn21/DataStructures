#include <iostream>
using namespace std;

struct node 
{
    int key;
    struct node* left, * right;
};

struct node* newNode(int item) 
{
    struct node* temp = new node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void Find(node* root, int key,bool& Out_Found)
{
    if (root != NULL)
    {
        if (key < root->key)
        {
            Find(root->left, key, Out_Found);
        }

        if (root->key == key)
        {
            cout << "1" << endl;
            Out_Found = true;
            return;
        }
        if (key >= root->key)
        {
            Find(root->right, key, Out_Found);
        }
    }
}

node* insert(node* node, int key) 
{
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    return node;
}

node* minValueNode(node* node) 
{
    struct node* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

node* MaxValueNode(node* node)
{
    struct node* current = node;

    while (current && current->right != NULL)
        current = current->right;

    return current;
}

node* deleteNode(node* root, int key) 
{
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else 
    {
        if (root->left == NULL) 
        {
            struct node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) 
        {
            struct node* temp = root->left;
            delete root;
            return temp;
        }

        struct node* temp = minValueNode(root->right);

        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}