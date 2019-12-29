#include <stdio.h>

int main() {

    // read n
    int n;
    printf("Input n\n");
    scanf("%d",&n);
    // read a string of n-1 numbers & calculate their xor
    printf("Input n-1 numbers in the interval [1,n]\n");
    int xorInput = 0;
    for(int i=0; i<n-1; i++) {
        int nr;
        scanf("%d", &nr);
        xorInput = xorInput ^ nr;
    }

    // calculate xorN - xor of the numbers from 1 to n
    int xorN = 0;
    for(int i=1;i<=n;i++) {
        xorN = xorN ^ i;
    }

    // find missing number by xor
    int missingNumber = xorInput ^ xorN;

    // print missing number
    printf("Missing number is %d\n", missingNumber);

    return 0;
}