
void maxheapify(int *A, int n, int i)
{
    int tmp, chosen, l, r;
    while ((i+1)*2 <= n)
    {
        l=(i+1)*2-1;
        r=(i+1)*2;
        tmp = A[l];
        chosen = 0;
        if (r < n && tmp < A[r])
        {
            chosen = 1;
            tmp=A[r];
        }
        if (A[i] < tmp)
        {
            if (chosen==1)
                A[r]=A[i];
            else
                A[l]=A[i];
            A[i]=tmp;
            if (chosen==1)
                i=r;
            else
                i=l;
        }
        else
        {
            return;
        }        
    }
}

void buildheap(int *A, int n)
{
    int i=(n)/2-1;
    while (i>=0)
    {
        maxheapify(A,n,i);
        i--;
    }
}

void heapsort(int *A, int n)
{
    int i=0,tmp;
    buildheap(A,n);
    for (i=n-1; i>0; i--)
    {
        tmp=A[i];
        A[i]=A[0];
        A[0]=tmp;
        maxheapify(A,i,0);
    }
}
