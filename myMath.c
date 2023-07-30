#include "myMath.h"

int fib(int n)
{
    if(n<=1) return n;
    int a=0,b=1,c;
    for(int i=2;i<=n;i++)
    {
        c=a+b;
        a=b;
        b=c;
    }

        return b;
}
void isPrime(int n)
{
    if(n<=1)
    {
        printf("not prime\n");
        return 0;
    }
        for(int i=2;i<=sqrt(n);i++)
    {
        if(n%2==0) {
        printf("not prime\n");
        return 0;
        }
    }
    printf("is prime\n");
}

