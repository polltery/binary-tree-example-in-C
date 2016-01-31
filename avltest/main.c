#include <stdlib.h>
#include <stdio.h>
#include "avltree.h"


int main(){
    
    printf(" ---- AVL TREES ---- \n");
    
    avltree *atree;
    
    atree = NULL;
    
    atree = insertKey( 6,1, atree);
    printAvltree( atree);
    atree = insertKey( 1,1, atree);
    printAvltree( atree);
    atree = insertKey( 5,1, atree);
    printAvltree( atree);
    atree = insertKey( 3,1, atree);
    printAvltree( atree);

    avltree * btree;
    
    btree = NULL;
    
    btree = insertKey( 8,1, btree);
    printAvltree( btree);
    btree = insertKey( 4,1, btree);
    printAvltree( atree);
    btree = insertKey( 2,1, btree);
    printAvltree( btree);
    btree = insertKey( 7,1, btree);
    printAvltree( btree);
    
    btree = mergeAvltrees(btree, atree);
    printAvltree(btree);
    
    atree = deleteKey(5, btree);
    printAvltree(atree);
    
    return 0;
}
