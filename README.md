# AVL Tree Word Search

## Overview
This program implements a word search algorithm using an AVL tree data structure in C++. An AVL tree is a type of self-balancing binary search tree (BST) in which the heights of the left and right subtrees of any node differ by at most one. Therefore, the worst-case time complexity is O(log n), better than orginary BST. 

## Usage
I have included some driver code ```AVLPathTest.cpp``` that utilizes this implementation to do word-searching.

The provided testing program takes input via command line, with the first word being the command ('I' - insert, 'R' - remove, 'L' - look up), and the second word being each tree node value. It prints out the path to the target word and the number of nodes took to find it. It runs indefinitely until error in the input stream, or ^D, or being terminated by ^C.

### Example Compiling and Run
```
make

./a.out
I A
I bee
I caught
I dung
I everywhere
I flying
I greatly
I higher
I in
I mauve
I skies
I than
I we
I had
I ever
I flown.
R bee
R caught
L had
```

The output would be:
```
AVL path: higher flying greatly had 
AVL numNodes: 14
```

There are three test files you can use as input (and their corresponding expected output): 
```testfile1.txt testfile2.txt testfile3.txt```

The driver code can easily be modified to be more graceful, but the current version has all the necessities to test the implementation.
An example of improvement would be reading in a whole file to populate the AVL tree and then asking user for operation.
