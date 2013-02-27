/* Given a binary search tree and the value of a node, find the in-order successor of the specified node. */

/*                 9 */
/*               /   \ */
/*             5      14 */
/*           /      /    \ */
/*         2       12    17 */
/*                   \ */
/*                   13 */

/* INPUT: */
/* 1) a binary search tree */
/* 2) value of a given node (integer) */

/* OUTPUT: */
/* reference of the in-order successor node */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
}Node;

void insert(Node **root, int key)
{
    Node *node = *root;
    Node *parent = NULL;
    while (node)
    {
        parent = node;
        if (key < node->key)
            node = node->left;
        else if (key > node->key)
            node = node->right;
        else
            return;
    }
    node = (Node *) malloc(sizeof(Node));
    if (!parent) *root= node;
    else if (parent->key < key) parent->right = node;
    else parent->left = node;
    node -> key = key;
    node ->left = NULL;
    node -> right = NULL;
    node ->parent = parent;
}

Node* find_in_order_successor(Node *root, int key)
{
    Node *node = root;
    Node *prev = node;
    Node *rec = NULL;
    while (node)
    {
        if (node->key > key)
        {
            prev = node;
            rec = node;
            node = node->left;
        }
        else if (node->key < key)
        {
            prev = node;
            node = node->right;
        }
        else
        {           
            if (node->right)
            {
                node = node->right;
                while (node->left)
                {
                    node = node->left;
                }
                return node;
            }
            else
            {
                return rec;
                /*while(prev!=NULL && node==prev->right)
                {
                    node=node->parent;
                    prev=node->parent;
                }
                if (prev == NULL)
                    return NULL;
                else return prev;*/
            }
        }
    }
    return NULL; 
}

void free_tree(Node *root)
{
    if (root)
    {
        if (root->left) free_tree(root->left);
        if (root->right) free_tree(root->right);
        free(root);
    }
    return;
}

int main(int argc, char **argv)
{
    Node *root=NULL;
    Node *res=NULL;
    int key = atoi(argv[1]);
    insert(&root, 9);
    insert(&root, 5);
    insert(&root, 2);
    insert(&root, 14);
    insert(&root, 12);
    insert(&root, 13);
    insert(&root, 17);
    res = find_in_order_successor(root, key);
    if (res)
        printf("%d\n", res->key);
    return 0;
}
