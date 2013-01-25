/* Enter your code here. Read input from STDIN. Print output to STDOUT */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100000

int main (int argc, char** argv)
{
    int n, i, len, total_sim, inc, iter;
    char buffer[MAX_LEN];
    char *pBuffer, *status;
   
    if (!gets(buffer)) return;
    sscanf(buffer, "%d", &n);
    
    for (i=0; i<n; i++)
    {
        if (!gets(buffer)) return;
        len = strlen(buffer);
        total_sim=len;
        for (inc = 1; inc < len; inc++)
        {
            pBuffer=buffer+inc;
            iter=0;
            while (iter < len-inc && pBuffer[iter]==buffer[iter++])
                total_sim+=1;
        }
        printf ("%d\n", total_sim);
    }
    
}
