#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"


struct BINTREE {
    int key;
    int value;
    bintree * left;
    bintree * right;
};

bintree *mkNode( int key, int value, bintree * left, bintree * right)
{
    
    //create a pointer to node and allocate memory for node
    bintree * tree = malloc(sizeof(bintree));
    
    
    /* Initializing node fields */
    
    tree->key = key;
    tree->value = value;
    tree->left = left;
    tree->right = right;
    
    return tree;
}

void freeNode( bintree * tree)
{

    /* free the node */
    if(tree){
        free(tree);
        tree = NULL;
    }
    
}

void freeBinTree( bintree * tree)
{
    
    /* free the entire tree */
    if(tree){
        freeBinTree(tree->left);
        freeBinTree(tree->right);
        free(tree);
        tree = NULL;
    }
    
}

static
void indent( int off)
{
    int i;
    
    for( i=0; i<off; i++) {
        printf( " ");
    }
}

static
void printBinTreeOff( int off, bintree *tree)
{
    if (tree != NULL) {
        printf( "Node{ key:%d value:%d\n", tree->key, tree->value);
        off += 6;
        indent( off);
        printf( "left: ");
        printBinTreeOff( off+6, tree->left);
        indent( off);
        printf( "right:");
        printBinTreeOff( off+6, tree->right);
        indent( off-2);
        printf( "}\n");
    } else {
        printf( "NULL\n");
    }
}

void printBinTree( bintree *tree)
{
    printBinTreeOff( 0, tree);
}

bintree * mergeBinTrees( bintree * tree1, bintree * tree2)
{
    
    /*  We take all the keys of tree1 and insert it into the tree2 (aka the other tree), i.e. tree1 merges into tree2
        therefore, when merging, please set your tree1 and tree2 carefully, depending on which tree you want to merge into
        How it works?
        If the left and right nodes are null for tree1, simply insert the tree1's key into tree2 and return the tree
        However, that's not the case usually, so what we do is..
        Add the tree1's key into tree2 and merge the left and right branch of tree1, to sort them.
        More comment's are given below..
     */
    
    if(tree1->left == NULL){
        
        if(tree1->right == NULL){
            
            /* Both the nodes are NULL so insert this key in the other tree and return */
            return insertKey(tree1->key, tree1->value, tree2);
            
        }else{
            
            /*  Right tree is not null, and left tree is null
                so insert this key in the other tree and continue merging by going to the right branch
             */
            
            return mergeBinTrees(tree1->right, insertKey(tree1->key, tree1->value, tree2));
        
        }
    
    }else if(tree1->right == NULL){
        
        /*  Left tree is not null, but right tree is null
            so insert this key in the other tree and continue merging by going to the left branch
         */
        
        return mergeBinTrees(tree1->left, insertKey(tree1->key, tree1->value, tree2));
    
    }else{
    
        /*  Both left and right nodes are occupied
            so lets merge left node with the right node until it's sorted 
            and merge the result of that tree with the other tree. 
            Also insert the key in the other tree so it is not left out.
         */
        
        return mergeBinTrees(mergeBinTrees(tree1->left, tree1->right), insertKey(tree1->key, tree1->value, tree2));
    }

}


bintree *insertKey( int key, int value, bintree * tree)
{
    /*  We check if the current tree will allow us to make a node, so if it is NULL, make the node and return
        If the tree is not null, we traverse depending on the value of the key, if the key is small, go left and if the key is bigger than the tree->key, go right.
        Once we find a NULL node, we make the node, and return the tree.
        Note: if a similar key is found, we simply return the tree as it is.
     */
    
    if(tree == NULL){
        return mkNode(key,value,NULL,NULL);
    }else if(key < tree->key){
        return mkNode(tree->key,tree->value,insertKey(key,value,tree->left),tree->right);
    }else if(key != tree->key){
        return mkNode(tree->key,tree->value,tree->left,insertKey(key,value,tree->right));
    }else{
        return mkNode(key,value,tree->left,tree->right);
    }
}


bintree *deleteKey( int key, bintree * tree)
{
    /*
        Delete key traverses through the tree until it reaches the given key
        once we find the given key, we check the left and right nodes of this tree
        If both left and right nodes are present, we merge the left node with the right node and return the tree.
        If only right node is null, we pull the left node and make it the current node.
        If only left node is null, we do the same thing as above, pull the right node, and make it the current node.
        If both the nodes are null, simply return NULL tree.
     */
    
    if(tree->key != key){
        if(key < tree->key){
            return mkNode(tree->key, tree->value, deleteKey(key, tree->left), tree->right);
        }else{
            return mkNode(tree->key, tree->value, tree->left, deleteKey(key, tree->right));
        }
    }else if(tree->left != NULL){
        if(tree->right != NULL){
            // Both nodes are occupied so lets sort the tree and return it
            //freeNode(tree);
            return mergeBinTrees(tree->left,tree->right);
        }else{
            // right node is null, so let left node act as this node
            return mkNode(tree->left->key, tree->left->value, tree->left->left, tree->left->right);
        }
    }else{
        if(tree->right != NULL){
            return mkNode(tree->right->key, tree->right->value, tree->right->left, tree->right->right);
        }else{
            //freeNode(tree);
            return NULL;
        }
    }
}

int findKey( int key, bintree * tree)
{
    /*
        Find key checks if the current tree has the required key or not, if it does then it returns it's value.
        If it doesn't then it traverses further based on the tree's properties.
     */
    
    // If this node has the key
    if(tree->key == key){
        return tree->value;
    }else{
        // If small, go left
        if(key < tree->key){
            // Check if left tree exists
            if(tree->left != NULL){
                // Continue recursion
                return findKey(key,tree->left);
            }else{
                return 0;
            }
        }else{
            if(tree->right != NULL){  
                // Check if right tree exists
                return findKey(key,tree->right);
            }else{
                return 0;
            }
        }
    }
}


