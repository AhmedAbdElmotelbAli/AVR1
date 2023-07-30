#ifndef MYMATH_H_INCLUDED
#define MYMATH_H_INCLUDED

#include <stdio.h>
#include<math.h>
#define pI 3.14
#define power(x,y)  pow(x,y)
#define sqrt(r)  (int) sqrt(r)
#define squareArea(r)   r*r
#define rectArea(l,r) l*r
#define cirArea(r) pI*r*r
#define rad2deg(r) r*(180.0/pI)
#define deg2rad(r) r*(pI/180.0)
#define exp(r) exp(r)
#define ceil(r) ceil(r)
#define floor(r) floor(r)
#define round(r) round(r)
int fib(int n);
void isPrime(int n);


#endif // MYMATH_H_INCLUDED
