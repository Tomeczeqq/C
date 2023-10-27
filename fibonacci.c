//Writing out the first n numbers of the Fibonacci sequence
#include <stdio.h>

void Fibonacci(int n)
{
    int a=0,b=1;
    for(int i=0;i<n;i++)
    {
        printf("%d ",a);
        int c=a;
        a=b;
        b=a+c;
    }
    printf("\n");
}

int main() 
{
    printf("Give the positive number of expressions of the Fibonacci sequence to be written out:\n");
    int n;
    scanf("%d",&n);
    if(n<=0)
        printf("The number given is not positive\n");
    else
        Fibonacci(n);
    return 0;
}
