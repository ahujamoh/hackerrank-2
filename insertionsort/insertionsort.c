#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

/* Head ends here */
void insertionSort(int ar_size, int *  ar) {
    int i,j,v,iter;
    if (ar_size <=1)
        return;
    for (i=1; i<ar_size; i++)
    {
        v=ar[i];
        j=i-1; 
        while(j>=0 && ar[j]>v)
        {
            ar[j+1]=ar[j];
            --j;
        }
        ar[j+1]=v;
        for(iter=0; iter<ar_size; iter++)
            printf("%d ", ar[iter]);
        printf("\n");
    }

}

/* Tail starts here */
int main() {
   
    int _ar_size;
    scanf("%d", &_ar_size);
    int _ar[_ar_size], _ar_i;
    for(_ar_i = 0; _ar_i < _ar_size; _ar_i++) { 
        scanf("%d", &_ar[_ar_i]); 
    }
   
    insertionSort(_ar_size, _ar);
   
    return 0;
}

