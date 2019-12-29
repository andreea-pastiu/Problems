/*Write a recursive and a non-recursive function to calculate the values of the Hermite polynomials
H(x), defined as follows:*/
#include <stdio.h>
typedef struct c {
    int x, no;
}coefficients;
coefficients coeff0, coeff1;

void initCoefficient(coefficients *c, int x, int no)
{
    c->x = x;
    c->no = no;
}
coefficients generateHermiteR(unsigned int n)
{
    if(n == 0)
        return coeff0;
    else if(n == 1)
        return coeff1;
    else
    {
        coefficients coeffn, coeffaux1, coeffaux2;
        coeffaux1 = generateHermiteR(n - 1);
        coeffaux2 = generateHermiteR(n - 2);
        coeffn.x = 2 * n * coeffaux1.x - 2 * (n - 1) * coeffaux2.x;
        coeffn.no = 2 * n * coeffaux1.no - 2 * (n - 1) * coeffaux2.no;
        return coeffn;
    }
}
coefficients generateHermite(unsigned int n)
{
    coefficients coeff2;
        for (int i = 2; i <= n; i++) {
            coeff2.x = 2 * i * coeff1.x - 2 * (i - 1) * coeff0.x;
            coeff2.no = 2 * i * coeff1.no - 2 * (i - 1) * coeff0.no;
            coeff0.x = coeff1.x;
            coeff0.no = coeff1.no;
            coeff1.x = coeff2.x;
            coeff1.no = coeff2.no;
        }
    return coeff2;
}
void printHermite(unsigned int n, coefficients coeff)
{
    printf("H%d(x) = %d*x%d", n, coeff.x, coeff.no);
}
int main() {
    unsigned int n;
    initCoefficient(&coeff0, 0, 1);
    initCoefficient(&coeff1, 2, 0);
    printf("Give n:");
    scanf("%d", &n);
    if(n == 0)
        printf("H0(x) = 1");
    else if(n == 1)
        printf("H1(x) = 2*x");
    else
    {
        printf("This is how I do it recursively:\n");
        printHermite(n, generateHermiteR(n));
        printf("\nThis is how I do it non-recursively:\n");
        printHermite(n, generateHermite(n));
    }
    return 0;
}