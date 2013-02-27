typedef struct stack{
    int *buffer;
    int size;
    int top;
}stack;


void initstack(stack *s, int size)
{
    s->buffer=(int *)malloc(size*sizeof(int));
    s->size=size;
    s->top=0;
}

void destroystack(stack *s, int size)
{
    free(s->buffer);
}

int stackempty(stack *s)
{
    return (s->top <= 0);
}

int stackpop(stack *s)
{
    if (s->top <=0)
    {
        return 0;
    }
    else
    {
        return s->buffer[(--s->top)];
    }
}

void expandstack(stack *s)
{
    int i=0;
    int *oldbuffer=s->buffer;
    s->buffer=(int *)malloc(s->size*2*sizeof(int));
    for (i=0; i<s->top; i++)
    {
        s->buffer[i]=oldbuffer[i];
    }
    s->size=s->size*2;
    free(oldbuffer);
}

void stackpush(stack *s, int x)
{
    if (s->top >= s->size)
    {
        expandstack(s);
    }
    s->buffer[s->top++]=x;
}

void printstack(stack *s)
{
    int i=0;
    for (i=0; i<s->top; i++)
        printf("%d ", s->buffer[i]);
    printf("\n");
}
