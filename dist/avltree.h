typedef struct AVLTREE avltree;

extern avltree *mkNode( int key, int value, avltree *left, avltree *right);

extern void freeNode( avltree *tree);

extern void freeAvltree( avltree *tree);

extern void printAvltree( avltree *tree);

extern avltree *mergeAvltrees( avltree *tree1, avltree *tree2);

extern avltree *insertKey( int key, int value, avltree *tree);

extern avltree *deleteKey( int key, avltree *tree);

extern int findKey( int key, avltree *tree);
