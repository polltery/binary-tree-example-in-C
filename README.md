# C Binary Tree & AVL Tree Library
A Binary tree and AVL tree type data structure library that can hold key-value pairs. 
In the given code, Each node is a binary tree on it's own.

*The Dist Folder* contains the latest stable release, download the dist folder only if you don't want the Xcode Project. 

## Compilation

```shell
gcc -o your-program.c bintree.c bintree.h
```

You could also import the project in Xcode.

## Usage:

Include the header files
```C
#include "bintree.h"          // If you are using avltree then use avltree.h instead of bintree.h
```

Create a binary tree object
```C
bintree *myTree;
```

You can create your own tree by two methods

Method 1 (Manually):
```c
myTree = mkNode( 4, 5, mkNode(3, 3, NULL, NULL), NULL);
```

Method 2 (Automatically):
```c
myTree = insertKey( 4, 5, myTree);
myTree = insertKey( 3, 3, myTree);
```

**Note** that the tree only accetps integer based key-value pairs.

## Functions available

**mkNode**: Returns a binary tree with given key, values and nodes. Returns bintree.
```c
// Syntax
mkNode(int key, int value, bintree *left, bintree *right);

// Example
myTree = mkNode( int key, int value, bintree leftNode, bintree rightNode);
```

**freeNode**: Frees a node and the memory associated with the node. The left and right node are still in the memory, check freeBinTree(). Returns nothing.
**freeBinTree**: Frees an entire binary tree and the memory associated with it. Returns nothing.
```c
// Syntax
freeNode(bintree *myTree);

// Example
freeNode(myTree->left);     // This will free the left node.
freeNode(myTree);           // This will free the root node.
freeBinTree(myTreee);       // Free the entire tree along with left and right nodes.
```

**printBinTree**: Print's a binary tree. Returns a nothing, but prints the tree while traversing it.
```c
// Syntax
printBinTree(bintree *myTree);

//Example
printBinTree(myTree);     // This will simply print the tree on your console.
```

**mergeBinTrees**: This will merge the first binary tree into the second binary tree. Returns a bintree.
```c
// Syntax
mergeBinTrees(bintree *treeA, bintree *treeB);

// Example
myTree = insertKey(5,1,myTree);
myTree = insertKey(3,1,myTree);
myNewTree = insertKey(7,1,myNewTree);
myNewTree = insertKey(2,1,myNewTree);
myTree = mergeBinTrees(myNewTree, myTree);       // This will insert myNewTree into myTree and return it.
```

**insertKey**: This function simply insertes a key into a tree. Returns a bintree.

**deleteKey**: This function simply deletes a key from a tree. Returns a bintree.
```c
// Syntax
insertKey( int key, int value, bintree *node);
deleteKey( int key, bintree *node);

// Example
myTree = insertKey( 10, 1, myTree);   // This will insert a key into myTree
myTree = deleteKey(10, myTree);     // This will remove the key that was inserted in the above line
```

**findKey**: Finds a key, and returns it's value, if the key is not there, the tree will return 0. Returns int.
```c
// Syntax
findKey( int key, bintree *node);

// Example (assuming our tree has a key of 10 with value 1)
printf( "Value for key 10: %d\n", findKey( 10, tree));    // This will print "1"
```

If you have a suggestion then add it to the issue tracker, or improve the code and then please send me a pull request.

**Note**:*This code was written as a part of the coursework at Heriot Watt University (Dubai Campus)*
