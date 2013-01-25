/* Enter your code here. Read input from STDIN. Print output to STDOUT */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef short bool;

int main(int argc, char** argv)
{
    unsigned long long n, count_primes, iter_n, divisor, i, count, check;
    char sn[20];
    unsigned long long primes[100000];
    unsigned long long prime_decomposition[100000];
    bool is_prime;

    /* clock_t start, end; */
    /* double elapsed; */

    /* memset(primes, 0, 10000 * sizeof(unsigned long long)); */
    /* memset(prime_decomposition, 0, 10000 * sizeof(unsigned long long)); */
    gets(sn);
    sscanf(sn, "%Lu", &n);
    if (n <=0 || n>1000000) return 1;
    primes[0]=1;
    primes[1]=2;
    count_primes=2;
    prime_decomposition[1]=0;

    /* start = clock(); */
    check = primes[1];
    while (divisor = n/check)
    {
        prime_decomposition[1]+=divisor;
        check = check * primes[1];
    }

    for (iter_n=3; iter_n <= n; iter_n ++)
    {
        is_prime = 1;
        check=iter_n;
        for (i=1; i < count_primes; i++)
        {
            if ( check % primes[i] == 0)
            {
                is_prime = 0;
                break;
            }
            if (primes[i] * primes[i] > check)
                break;
        }
        if (is_prime)
        {
            prime_decomposition[count_primes]=0;
            primes[count_primes++]=iter_n;
            check = iter_n;
            while (divisor = n/check)
            {
                prime_decomposition[count_primes-1]+=divisor;
                check = check * iter_n;
            }
        }
    }

    for (iter_n=1; iter_n < count_primes; iter_n++)
        prime_decomposition[iter_n] *=2;
    count = 1;
    for (i=1; i < count_primes; i++)
    {
        count *= (prime_decomposition[i]+1)%1000007;
        count = count % 1000007;
    }
    printf("%Lu\n", count);

    /* end = clock(); */
    /* elapsed = ((double) (end - start)) / CLOCKS_PER_SEC; */
    /* printf("Time used: %lf s\n", elapsed); */

    return 0;
}
