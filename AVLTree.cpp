#include "AVLNode.h"
#include "AVLTree.h"
#include <iostream>
#include <string>
using namespace std;

AVLTree::AVLTree()
{
    root = NULL;
}

AVLTree::~AVLTree()
{
    delete root;
    root = NULL;
}

// insert finds a position for x in the tree and places it there, rebalancing
// as necessary.
void AVLTree::insert(const string &x)
{
    if (root == NULL)
    {
        root = new AVLNode();
        root->value = x;
    }
    else
    {
        insert(root, x);
    }
    // printTree();
}

void AVLTree::insert(AVLNode *&i, const string &s)
{

    if (i == NULL)
    {
        i = new AVLNode();
        i->value = s;
    }
    int number = i->value.compare(s);
    if (number > 0)
    {
        insert(i->left, s);
    }
    if (number < 0)
    {
        insert(i->right, s);
    }
    i->height = max(height(i->left), height(i->right)) + 1;
    if (i != NULL)
    {
        balance(i);
    }
}

// remove finds x's position in the tree and removes it, rebalancing as
// necessary.
void AVLTree::remove(const string &x)
{
    root = remove(root, x);
}

// pathTo finds x in the tree and returns a string representing the path it
// took to get there.
string AVLTree::pathTo(const string &x) const
{
    if (find(x) != true)
    {
        return "";
    }
    if (root != NULL)
    {
        string result = pathTo(root, x);
        return result;
    }

    return NULL;
}

string AVLTree::pathTo(AVLNode *const &someNode, const string &x) const
{
    string result;
    int num = someNode->value.compare(x);
    if (num == 0)
    {
        result += someNode->value;
        result += " ";
    }
    if (num > 0)
    {
        result += someNode->value;
        result += " ";
        if (someNode->left != NULL)
        {
            result += pathTo(someNode->left, x);
        }
    }
    if (num < 0)
    {
        result += someNode->value;
        result += " ";
        if (someNode->right != NULL)
        {
            result += pathTo(someNode->right, x);
        }
    }
    return result;
}

// find determines whether or not x exists in the tree.
bool AVLTree::find(const string &x) const
{
    if (root == NULL)
    {
        return false;
    }
    bool result = find(root, x);
    return result;
}

bool AVLTree::find(AVLNode *const &someNode, const string &someString) const
{
    if (someNode == NULL)
    {
        return false;
    }
    if (someNode->value == someString)
    {
        return true;
    }
    if (someNode->value > someString)
    {
        return find(someNode->left, someString);
    }
    if (someNode->value < someString)
    {
        return find(someNode->right, someString);
    }
}

// numNodes returns the total number of nodes in the tree.
int AVLTree::numNodes() const
{
    if (root == NULL)
    {
        return 0;
    }
    int result = numNodes(root);
    return result;
}

int AVLTree::numNodes(AVLNode *const &someNode) const
{
    int result = 1;
    if ((someNode->left != NULL))
    {
        result += numNodes(someNode->left);
    }
    if ((someNode->right != NULL))
    {
        result += numNodes(someNode->right);
    }
    return result;
}

// balance makes sure that the subtree with root n maintains the AVL tree
// property, namely that the balance factor of n is either -1, 0, or 1.
void AVLTree::balance(AVLNode *&n)
{
    if (height(n->right) - height(n->left) == 2)
    {
        if (height(n->right->right) - height(n->right->left) < 0)
        {
            n->right = rotateRight(n->right);
        }
        n = rotateLeft(n);
    }

    if (height(n->right) - height(n->left) == -2)
    {
        if (height(n->left->right) - height(n->left->left) > 0)
        {
            n->left = rotateLeft(n->left);
        }
        n = rotateRight(n);
    }
}

// rotateLeft performs a single rotation on node n with its right child.
AVLNode *AVLTree::rotateLeft(AVLNode *&n)
{
    AVLNode *temp = new AVLNode();
    temp = n->right;
    n->right = temp->left;
    temp->left = n;
    n->height = max(height(n->left), height(n->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    return temp;
}

// rotateRight performs a single rotation on node n with its left child.
AVLNode *AVLTree::rotateRight(AVLNode *&n)
{
    AVLNode *temp = new AVLNode();
    temp = n->left;
    n->left = temp->right;
    temp->right = n;
    n->height = max(height(n->left), height(n->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    return temp;
}

// private helper for remove to allow recursion over different nodes.
// Returns an AVLNode* that is assigned to the original node.
AVLNode *AVLTree::remove(AVLNode *&n, const string &x)
{
    if (n == NULL)
    {
        return NULL;
    }

    // first look for x
    if (x == n->value)
    {
        // found
        if (n->left == NULL && n->right == NULL)
        {
            // no children
            delete n;
            n = NULL;
            return NULL;
        }
        else if (n->left == NULL)
        {
            // Single child (left)
            AVLNode *temp = n->right;
            n->right = NULL;
            delete n;
            n = NULL;
            return temp;
        }
        else if (n->right == NULL)
        {
            // Single child (right)
            AVLNode *temp = n->left;
            n->left = NULL;
            delete n;
            n = NULL;
            return temp;
        }
        else
        {
            // two children -- tree may become unbalanced after deleting n
            string sr = min(n->right);
            n->value = sr;
            n->right = remove(n->right, sr);
        }
    }
    else if (x < n->value)
    {
        n->left = remove(n->left, x);
    }
    else
    {
        n->right = remove(n->right, x);
    }

    // Recalculate heights and balance this subtree
    n->height = 1 + max(height(n->left), height(n->right));
    balance(n);

    return n;
}

// min finds the string with the smallest value in a subtree.
string AVLTree::min(AVLNode *node) const
{
    // go to bottom-left node
    if (node->left == NULL)
    {
        return node->value;
    }
    return min(node->left);
}

// height returns the value of the height field in a node.
// If the node is null, it returns -1.
int AVLTree::height(AVLNode *node) const
{
    if (node == NULL)
    {
        return -1;
    }
    return node->height;
}

// max returns the greater of two integers.
int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == NULL)
        return;
    showTrunks(p->prev);
    cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
void AVLTree::printTree(AVLNode *root, Trunk *prev, bool isRight)
{
    if (root == NULL)
        return;

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isRight)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->value << endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->left, trunk, false);

    delete trunk;
}

void AVLTree::printTree()
{
    printTree(root, NULL, false);
}
