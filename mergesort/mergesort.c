#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

void merge(int *a, int p, int q, int *b)
{
    int n1, n2, r, n, i, j, k;
    if (p >= q)
        return;
    n=q-p;
    r=p+n/2;
    n1 = r-p+1;
    n2 = q-r;

    merge(a, p, r, b);
    merge(a, r+1, q, b);
    for (i=0; i<n1; i++)
        b[i]=a[p+i];
    b[n1]=INT_MAX;
    for (j=0; j<n2; j++)
        b[n1+j+1]=a[p+n1+j];
    b[n1+n2+1]=INT_MAX;
    i=0;
    j=0;
    k=0;
    n=q-p+1;
    for (k=0; k<n; k++)
    {
        if (b[i] <= b[n1+j+1])
        {
            a[p+k]=b[i];
            ++i;
        }
        else
        {
            a[p+k]=b[n1+j+1];
            ++j;
        }
    }
    return;
}

int main (int argc, char **argv)
{

    int n,i;
    int *ar;
    int *buffer;

    scanf("%d", &n);
    if (n<=0)
        return 0;
    ar=(int *) malloc(n*sizeof(int));
    buffer = (int *) malloc(n*sizeof(int));
    for (i=0; i<n; i++)
    {
        scanf("%d", &ar[i]);
    }

    merge(ar, 0, n-1, buffer);
    for (i=0; i<n; i++)
    {
        printf("%d ", ar[i]);
    }
    printf("\n");
    return 0;
}
