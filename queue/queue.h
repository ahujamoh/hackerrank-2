typedef struct queue
{
    int *buffer;
    int front;
    int end;
    int size;
    int length;
}queue;

void initqueue(queue *q, int size)
{
    q->length=0;
    q->buffer=(int *)malloc(size*sizeof(int));
    q->front = 0;
    q->end = 0;
    q->size=size;
}

void queueempty(queue *q)
{
    return (q->length <= 0);
}

void destroyqueue(queue *q)
{
    free(q->buffer);
}

void expandqueue(queue *q)
{
    int *oldbuffer = q->buffer;
    int i=0;
    q->buffer=(int *)malloc(2*q->size*sizeof(int));
    for (i=0; i<q->length; i++)
    {
        q->buffer[i]=oldbuffer[(q->front+i)%q->size];
    }
    q->size=q->size*2;
    free(oldbuffer);
    q->front = 0;
    q->end=q->length;
}

int enqueue(queue *q, int x)
{
    q->length=q->length+1;
    if (q->length > q->size)
    {
        q->length=q->length-1;
        expandqueue(q);
        q->length=q->length+1;
    }
    q->buffer[q->end]=x;
    if (q->end == q->size-1)
    {
        q->end=0;
    }
    else
    {
        ++(q->end);
    }
}

int dequeue(queue *q)
{
    int x;
    if (q->length==0)
    {
        x=0;
    }
    else 
    {
        x=q->buffer[q->front];
        if (q->front == q->size-1)
            q->front = 0;
        else
            q->front = q->front + 1;
        --(q->length);
    }
    return x;
}

void printqueue(queue *q)
{
    int i;
    for (i=0; i<q->length; i++)
    {
        printf("%d ", q->buffer[(q->front+i)%q->size]);
    }
    printf("\n");
}
