//Calculating the square root using Newton's method
#include <stdio.h>
#include <math.h>

int main() 
{
    printf("Enter two positive numbers:\n");
    double a,eps;
    scanf("%lf %lf",&a,&eps);
    if(a!=fabs(a) || eps!=fabs(eps))
        printf("Incorrect input\n");
    else
    {
        double x=1,y=a;
        while(fabs(x-y)>=eps)
        {
            x=(x+y)/2;
            y=a/x;
        }
        double res=(x+y)/2;
        printf("%lf\n",res);
    }
    return 0;
}