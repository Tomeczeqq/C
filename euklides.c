//Writing out the GCD (greatest common divisor) of two given numbers
#include <stdio.h>

int main() 
{
    printf("Enter two positive numbers:\n");
    int a,b;
    scanf("%d %d",&a,&b);
    if(a<=0 || b<=0)
        printf("Incorrect input\n");
    else
    {
        int c;
        while(b!=0)
        {
            c=a%b;
            a=b;
            b=c;
        }
        printf("The greatest common divisor of the two given numbers is %d.\n",a);
    }
    return 0;
}
