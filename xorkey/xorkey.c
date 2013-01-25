/* Enter your code here. Read input from STDIN. Print output to STDOUT */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"
#include "time.h"

#define MAX_N 100000
#define MAX_Q 50000
#define MAX_LEN 10000000
#define MAX_BIT 15

typedef short bool;

typedef struct Indexes
{
    unsigned int index;
    struct Indexes *left;
    struct Indexes *right;
}Indexes;

typedef struct Node
{
    struct Node *left;
    struct Node *right;
    Indexes *index_list;
}Node;

void free_list( Indexes* index)
{
    if (index->left)
        free_list(index->left);
    if (index->right)
        free_list(index->right);
    free(index);
}

void free_index( Node *root )
{
    free_list(root->index_list);
    if (root->left)
        free_index(root->left);
    if (root->right)
        free_index(root->right);
    free(root);
}

Indexes* create_index( )
{
    Indexes *ret = (Indexes *) malloc(sizeof(Indexes));
    ret -> left = NULL;
    ret -> right = NULL;
    ret -> index = (unsigned int) -1;
    return ret;
}

bool intersect_index(Indexes *index_list, unsigned int p, unsigned int q)
{
    while (index_list)
    {
        if (index_list->index <= q && index_list->index >=p)
            return 1;
        else if (index_list->index > p)
            index_list = index_list->left;
        else index_list = index_list ->right;
    }
    return 0;
}

void insert_index(Indexes** index_list, unsigned int index)
{
    Indexes *tmp, *pointer, *parent;
    bool leftoright;
    if (*index_list == NULL)
    {
        *index_list = create_index();
        (*index_list)->index = index;
    }
    else
    {
        pointer = *index_list;
        while (pointer)
        {
            parent=pointer;
            if (index < pointer->index)
            {
                pointer = pointer->left;
                leftoright = 0;
            }
            else if (index > pointer->index)
            {
                pointer = pointer->right;
                leftoright = 1;
            }
            else return;
        }
        tmp = create_index();
        tmp -> index = index;
        if (!leftoright)
            parent->left = tmp;
        else
            parent->right = tmp;
    }
}

Node* create_node( )
{
    Node *ret;
    ret = (Node *) malloc(sizeof(Node));
    ret->left=NULL;
    ret->right=NULL;
    ret->index_list=NULL;
    return ret;
}

Node* build_index(unsigned int *numbers, unsigned int *orders, unsigned int n)
{
    unsigned int i;
    int bit;
    unsigned int bit_mask;
    bool bit_value;
    Node *root, *pointer;
    
    root = create_node();
    
    for (i=0; i<n; i++)
    {
        pointer = root;
        bit_mask = 0x01 << MAX_BIT;
        for (bit=MAX_BIT; bit>=0; bit--)
        {
            bit_value=((numbers[i] & bit_mask) >> bit);
            if (!bit_value)
            {
                if (!pointer->left)
                {
                    pointer->left = create_node();
                }
                insert_index(&pointer->index_list, orders[i]);
                pointer = pointer->left;
            }
            else
            {
                if (!pointer->right)
                {
                    pointer->right=create_node();
                }
                insert_index(&pointer->index_list, orders[i]);
                pointer=pointer->right;
            }
            bit_mask >>=1;
        }
        insert_index(&pointer->index_list, orders[i]);
    }
    return root;
}

unsigned int xorq(Node *root, unsigned int a, unsigned int p, unsigned int q)
{
    unsigned int res = 0, inv_a;
    int bit;
    Node *pointer, *tmp;
    unsigned int bit_mask;
    bool bit_value;
    inv_a = ~a;
    bit_mask = 0x01 << MAX_BIT;
    pointer = root;
    for (bit = MAX_BIT; bit>=0; bit--)
    {
        bit_value = (bit_mask & inv_a) >> bit;
        if (!bit_value)
        {
            if (pointer->left)
            {
                tmp = pointer->left;
                if (intersect_index(tmp->index_list, p, q))
                {
                    pointer=tmp;
                }
                else
                    pointer=pointer->right;
            }
            else
            {
                pointer = pointer->right;
            }
        }
        else
        {
            if (pointer->right)
            {
                tmp = pointer->right;
                if (intersect_index(tmp->index_list, p, q))
                {
                    pointer=tmp;
                }
                else
                    pointer=pointer->left;
            }
            else
            {
                pointer = pointer->left;
            }
        }
        bit_mask >>= 1;
    }
    return pointer->index_list->index;
}

void fisheryates_shuffle(unsigned int *numbers, unsigned int *orders, unsigned int n)
{
    double p;
    unsigned int i,j,r;
    for (i=n-1; i>=1; i--)
    {
        p = (double)rand()/((double)RAND_MAX+1);
        j = (unsigned int)(p*(i+1));
        if (j>i)
            printf("error!\n");
        
        r=numbers[i];
        numbers[i]=numbers[j];
        numbers[j]=r;
        r=orders[i];
        orders[i]=orders[j];
        orders[j]=r;
    }
}

int main (int argc, char** argv)   
{
    unsigned int n_testcase, query_iter, n, p, q, s, i, j, a;
    char *buffer, *token;
    Node *root;
    unsigned int numbers[MAX_N];
    unsigned int original[MAX_N];
    unsigned int orders[MAX_N];
    char seps[]={' ',',','\t'};
    buffer=(char *) malloc(MAX_LEN * sizeof(char));
    srand(time(NULL));
    
    if (gets(buffer))
    {
        sscanf(buffer, "%u", &n_testcase);
        for (query_iter = 0; query_iter < n_testcase; query_iter++)
        {
            if (gets(buffer))
            {
                sscanf(buffer, "%u %u", &n, &s);
            }
            else
            {
                free(buffer);
                return 1;
            }
            if (gets(buffer))
            {
                i=0;
                token = strtok (buffer, seps);
                while (token != NULL)
                {
                    sscanf (token, "%u", &original[i]);
                    numbers[i] = original[i];
                    orders[i]=i;
                    if (original[i++] > 0xEFFF) return 1;
                    token = strtok (NULL, seps);
                }
                if (i!=n) 
                {
                    free(buffer); 
                    return 1;
                }
            }
            else
            {
                free(buffer);
                return 1;
            }
            fisheryates_shuffle(numbers, orders, n);
            root = build_index(numbers, orders, n);
            for (i=0; i<s; i++)
            {
                if (gets(buffer))
                {
                    sscanf(buffer, "%u %u %u", &a, &p, &q);
                    /* if (q<p || q-p > MAX_Q) return 1;
                    if (p <0 || p>n || q<0 || q>n) return 1;*/
                    printf("%u\n", a^original[xorq(root, a, p-1, q-1)]);
                }
                else
                {
                    free_index(root);
                    free(buffer);
                    return 1;
                }
            }
        }
    }
    else
    {
        free_index(root);
        free(buffer);
        return 1;
    }
    free_index(root);
    free(buffer);
    return 0;
}
