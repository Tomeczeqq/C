#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 100
#define TEST 1  // 0 is for automatic testing

//Draws one integer from the interval [a,b] using the rand() function and the % operator
//If a>b then it returns INT_MIN
//If b-a>RAND_MAX then it returns INT_MAX
//If a==b then it returns a (without calling the rand function)
//Else returns a number from the interval [a,b]
int rand_from_interval(int a, int b) {
    if(a>b)
        return INT_MIN;
    else if(b-a>RAND_MAX)
        return INT_MAX;
    else if(a==b)
        return a;
    else
        return a+(rand()%(b-a+1));
}

//A random permutation of the elements of the set of numbers {0, 1, 2,..., n-1}
//(with an equidistant distribution) is stored in an array of tables
//0 < n <= 100, if not then the elements of the array tab have unbounded values
void rand_permutation(int n, int tab[]) {
    for(int i=0;i<n;i++)
        tab[i]=i;
    for(int i=0;i<n-1;i++)
    {
        int k=rand_from_interval(i,n-1);
        int temp=tab[i];
        tab[i]=tab[k];
        tab[k]=temp;
    }
}

//Babel method of sorting n elements of tab array in order from smallest to largest value
//Returns the number of the iteration of the outer loop (counted from 1), after which the array was ordered
int bubble_sort(int n,int tab[]) {
    int result=1;
    for(int i=0;i<n-1;i++)
    {
        int f=0;
        for(int j=0;j<n-1-i;j++)
        {
            if(tab[j]>tab[j+1])
            {
                int temp=tab[j];
                tab[j]=tab[j+1];
                tab[j+1]=temp;
                f=1;
            }
        }
        if(f==0)
        {
            result=i;
            break;
        }        
    }
    return result;
}

int main(void) {
    int test_nr,seed,a,b,n;
    int tab[N];
    if(TEST)
        printf("Enter test number i seed = ");
    scanf("%d %d",&test_nr,&seed);
    srand(seed);    //generator seed setting (for post-termination of results)
    switch(test_nr) {
        case 1:
                if(TEST)
                    printf("a b = ");
                scanf("%d %d",&a,&b);
                for(int i=0;i<3;i++)
                    printf("%d ",rand_from_interval(a,b));
                break;
        case 2:
                if(TEST)
                    printf("n = ");
                scanf("%d",&n);
                rand_permutation(n,tab);
                for(int i=0;i<n;i++)
                    printf("%d ",tab[i]);
                printf("\n");
                break;
        case 3:
                if(TEST)
                    printf("n = ");
                scanf("%d",&n);
                rand_permutation(n,tab);
                printf("%d\n",bubble_sort(n,tab));
                break;
        default:
                if(TEST)
                    printf("NOTHING TO DO!\n");
    }
    return 0;
}