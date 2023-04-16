#ifndef AVL_H
#define AVL_H

#include <string>
#include "AVLNode.h"

using namespace std;

// You do not need to know how Trunk works.
struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

class AVLTree
{
public:
    AVLTree();
    ~AVLTree();

    // insert finds a position for x in the tree and places it there, rebalancing
    // as necessary.
    void insert(const string &x);
    // remove finds x's position in the tree and removes it, rebalancing as
    // necessary.
    void remove(const string &x);

    void printTree();
    string pathTo(const string &x) const;
    bool find(const string &x) const;
    int numNodes() const;

private:
    // Declare a root node
    AVLNode *root;

    // balance makes sure that the subtree with root n maintains the AVL tree
    // property, namely that the balance factor of n is either -1, 0, or 1.
    void balance(AVLNode *&n);

    // rotateLeft performs a single rotation on node n with its right child.
    AVLNode *rotateLeft(AVLNode *&n);
    // rotateRight performs a single rotation on node n with its left child.
    AVLNode *rotateRight(AVLNode *&n);

    AVLNode *remove(AVLNode *&n, const string &x);

    // finds the string with the smallest value in a subtree.
    string min(AVLNode *node) const;

    // returns the value of the height field in a node. If the node is
    // null, it returns -1
    int height(AVLNode *node) const;
    
    void printTree(AVLNode *root, Trunk *prev, bool isRight);
    string pathTo(AVLNode *const &someNode, const string &x) const;
    bool find(AVLNode *const &someNode, const string &someString) const;
    int numNodes(AVLNode *const &someNode) const;
    void insert(AVLNode *&i, const string &s);
};

// returns the greater of two integers.
int max(int a, int b);

#endif
