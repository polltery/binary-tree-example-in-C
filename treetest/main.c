#include <stdlib.h>
#include <stdio.h>
#include "bintree.h"


int main()
{
    
    bintree *tree;
    
    tree = mkNode( 5, 5,
                  mkNode( 3, 3,
                         mkNode( 1, 1,
                                NULL,
                                mkNode( 4, 4, NULL, NULL)),
                         NULL),
                  NULL);
    
    printBinTree( tree);
    freeBinTree( tree);
    
    tree = NULL;
    tree = insertKey( 6,1,tree);
    tree = insertKey( 1,1,tree);
    tree = insertKey( 5,1,tree);
    tree = insertKey( 3,1,tree);
    tree = insertKey( 8,1,tree);
    tree = insertKey( 4,1,tree);
    tree = insertKey( 2,1,tree);
    tree = insertKey( 7,1,tree);
    printBinTree( tree);
    
    tree = deleteKey( 5, tree);
    printBinTree( tree);
    
    printf( "Value for key 3: %d\n", findKey( 1, tree));
    printf( "Value for key 5: %d\n", findKey( 5, tree));
    
    freeBinTree( tree);
    
    bintree * treeb;
    treeb = NULL;
    treeb = insertKey(5, 1, treeb);
    printBinTree(treeb);
    treeb = deleteKey(5, treeb);
    printBinTree(treeb);
    return 0;
    
}


