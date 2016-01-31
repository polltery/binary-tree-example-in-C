#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

struct AVLTREE {
    int key;
    int value;
    avltree * left;
    avltree * right;
};

avltree *mkNode( int key, int value, avltree * left, avltree * right)
{
    avltree * tree = malloc(sizeof(avltree));
    tree->key = key;
    tree->value = value;
    tree->left = left;
    tree->right = right;
    return tree;
}

void freeNode( avltree * tree)
{
    if(tree){
        free(tree);
        tree = NULL;
    }
}

void freeAvltree( avltree * tree)
{
    if(tree){
        freeAvltree(tree->left);
        freeAvltree(tree->right);
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
void printAvltreeOff( int off, avltree *tree)
{
    if (tree != NULL) {
        printf( "Node{ key:%d value:%d\n", tree->key, tree->value);
        off += 6;
        indent( off);
        printf( "left: ");
        printAvltreeOff( off+6, tree->left);
        indent( off);
        printf( "right:");
        printAvltreeOff( off+6, tree->right);
        indent( off-2);
        printf( "}\n");
    } else {
        printf( "NULL\n");
    }
}

void printAvltree( avltree *tree)
{
    printAvltreeOff( 0, tree);
}

avltree * mergeAvltrees( avltree * tree1, avltree * tree2)
{
    if(tree1->left == NULL){
        if(tree1->right == NULL){
            return insertKey(tree1->key, tree1->value, tree2);
        }else{
            return mergeAvltrees(tree1->right, insertKey(tree1->key, tree1->value, tree2));
        }
    }else if(tree1->right == NULL){
        return mergeAvltrees(tree1->left, insertKey(tree1->key, tree1->value, tree2));
    }else{
        return mergeAvltrees(mergeAvltrees(tree1->left, tree1->right), insertKey(tree1->key, tree1->value, tree2));
    }
}


avltree *insertKey( int key, int value, avltree * tree)
{
    /*
        There are four possible cases of balancing when inserting a key into an AVL tree.
        1. Left left
        2. left right
        3. Right right
        4. Right right
        First we check if the current tree is NULL, if it is, simply make node and return.
        If not, we look towards the left or right tree (depending on the key)
        But before we start traversing, we check the current tree's left and right nodes.
        If the left node is NULL, we simply go ahead with our traversal, but if it's not null,
        we compare the key with the left node's key and decide what to do, if the key is less than the left tree's key,
        and the right node is empty, we do the left-left case. and If the left tree's key were smaller, we again
        check if the right node is empty or not, if it is, we do the left-right case. And if the right node is not NULL, 
        we simply go ahead with our traversal without balancing.
        The case is similar if the key is bigger than the root key.
     
     */
    if(tree == NULL){
        
        // termination
        return mkNode(key,value,NULL,NULL);
    
    }else if(key < tree->key){
        
        // Going left
        if(tree->left == NULL){
            
            return mkNode(tree->key, tree->value, insertKey(key, value, tree->left), tree->right);
        
        }else if(key < tree->left->key){
            if(tree->right == NULL){
                
                // Do left-left-case
                return insertKey(tree->key, tree->value, insertKey(key, value, tree->left));
            
            }else{
                
                return mkNode(tree->key, tree->value, insertKey(key, value, tree->left), tree->right);
            
            }
        }else{
            if(tree->right == NULL){
                
                // Do left-right-case
                return insertKey(tree->key, tree->value, mkNode(key, value, tree->left, NULL));
            
            }else{
                
                return mkNode(tree->key, tree->value, insertKey(key, value, tree->left), tree->right);
            
            }
        }
    }else{
        
        // Going right
        if(tree->right == NULL){
            
            return mkNode(tree->key, tree->value, tree->left, insertKey(key, value, tree->right));
        
        }else if(key > tree->right->key){
            
            if(tree->left == NULL){
                
                // Do right-right-case
                return insertKey(tree->key, tree->value, insertKey(key, value, tree->right));
            
            }else{
                
                return mkNode(tree->key, tree->value, tree->left, insertKey(key, value, tree->right));
            
            }
        }else{
            
            if(tree->left == NULL){
                
                // Do right-left-case
                return insertKey(tree->key, tree->value, mkNode(key, value, NULL, tree->right));
            
            }else{
                
                return mkNode(tree->key, tree->value, tree->left, insertKey(key, value, tree->right));
            
            }
        }
    }
}


avltree *deleteKey( int key, avltree * tree)
{
    /*
        This function treverses through the tree until we have reached the given key
        Once we reach the given key, we check the tree's left and right nodes...
        If the left and right are null, simply return NULL tree
        If the left node is null and the right is not, make a new node, with right tree's properties and return the node
        If the right node is nul and the left is not, do the same as above, but with left tree's properties
        If none of the nodes are null (this is the tricky part) ...
        merge the resulting merge of this tree's right node into the left node (with it's right node as NULL), WITH the left node's right node.
        This will balance the tree and delete the key.
     */
    
    if(key == tree->key){
        
        if(tree->left == NULL){
            
            if(tree->right == NULL){
                // left and right are null..
                return NULL;
            }else{
                // left is null, right is not
                return mkNode(tree->right->key, tree->right->value, tree->right->left, tree->right->right);
            }
            
        }else{
            
            if(tree->right == NULL){
                // left is not null, right is null
                return mkNode(tree->left->key, tree->left->value, tree->left->left, tree->right->right);
            }else{
                // None of them are null
                return mergeAvltrees(mergeAvltrees(tree->right,mkNode(tree->left->key,tree->left->value,tree->left->left,NULL)),tree->left->right);
            }
        }
    }else{
        
        if(key < tree->key){
            // Go left
            return mkNode(tree->key, tree->value, deleteKey(key, tree->left), tree->right);
        }else{
            // Go right
            return mkNode(tree->key, tree->value, tree->left, deleteKey(key, tree->right));
        }
    }
}

int findKey( int key, avltree * tree)
{
    if(tree->key == key){
        return tree->value;
    }else{
        if(key < tree->key){
            if(tree->left != NULL){
                return findKey(key,tree->left);
            }else{
                return 0;
            }
        }else{
            if(tree->right != NULL){
                return findKey(key,tree->right);
            }else{
                return 0;
            }
        }
    }
}


