#include <stdio.h>
#define N 100
#define TEST 1    // 0 is for automatic testing

//Returns n evenly spaced samples, calculated over the interval [start, stop].
//0 <= n <= N
//for n = 0 return empty array
//for n = 1 return one-element array, with array[0] = start
void linspace(double array[], double start, double stop, int n) {
    if(n==1)
        array[0]=start;        
    else
    {
        array[0]=start;
        double ext=(stop-start)/(n-1);
        for(int i=1;i<n;i++)
            array[i]=array[i-1]+ext;
    }
}

//Multiply each element of v by the value of scalar
void multiply_by_scalar(double v[], int n, double scalar) {
    for(int i=0;i<n;i++)
        v[i]*=scalar;
}

//Add to each element v1[i] value of v2[i]
void add(double v1[], const double v2[], int n) {
    for(int i=0;i<n;i++)
        v1[i]+=v2[i];
}

//Calculate and return the dot product of v1 and v2
double dot_product(const double v1[], const double v2[], int n) {
    double result=0;
    for(int i=0;i<n;i++)
        result+=v1[i]*v2[i];
    return result;
}

//Generates the sequence of n samples by incrementing the start value using the step size (|step| > 1.e-5).
//0 <= n <= N
//for n = 0 return empty array
//for n = 1 return one-element array, with array[0] = start
void range(double array[], double start, double step, int n) {
    array[0]=start;
    if(n>1)
        for(int i=1;i<n;i++)
            array[i]=array[i-1]+step;
}

//Read double vector of size n
void read_vector(double v[], int n) {
	for(int i=0;i<n;i++)
		scanf("%lf",v+i);
}

//Print double vector of size n (with 2 figures after the decimal point)
void print_vector(const double v[], int n) {
	for(int i=0;i<n;i++)
		printf("%.2f ",v[i]);
	printf("\n");
}

int main(void) {
	int to_do,len;
	double start,stop,step,scalar;
	double vector_1[N],vector_2[N];
    if(TEST)
        printf("Enter test number [1, 5]: ");
	scanf("%d",&to_do);
	switch(to_do) {
		case 1:
		    if(TEST)
                printf("LINSPACE: Enter numbers: n, start, stop ");
			scanf("%d %lf %lf",&len,&start,&stop);
	        if(len<0 || len>N) {
                printf("n<0 or n > 100\n");
                break;
            }
			linspace(vector_1,start,stop,len);
			print_vector(vector_1,len);
			break;
		case 2:
		    if(TEST)
                printf("ADD: Enter lengths of vectors: ");
			scanf("%d",&len);
	        if(len<0 || len>N) {
                printf("n<0 or n > 100\n");
                break;
            }
			if(TEST)
                printf("Enter elements of the first vector: ");
			read_vector(vector_1,len);
			if(TEST)
                printf("Enter elements of the second vector: ");
			read_vector(vector_2,len);
			add(vector_1,vector_2,len);
			print_vector(vector_1,len);
			break;
		case 3:
		    if(TEST)
                printf("DOT PRODUCT: Enter lengths of vectors: ");
			scanf("%d",&len);
	        if(len<0 || len>N) {
                printf("n<0 or n > 100\n");
                break;
            }
		    if(TEST)
                printf("Enter elements of the first vector: ");
			read_vector(vector_1,len);
			if(TEST)
                printf("Enter elements of the second vector: ");
			read_vector(vector_2,len);
			printf("%.2f\n",dot_product(vector_1,vector_2,len));
			break;
		case 4:
		    if(TEST)
                printf("MULTIPLY BY SCALAR: Enter vector length and scalar value: ");
			scanf("%d %lf",&len,&scalar);
	        if(len<0 || len>N) {
                printf("n<0 or n > 100\n");
                break;
            }
			printf("Enter elements of the vector: ");
			read_vector(vector_1,len);
			multiply_by_scalar(vector_1,len,scalar);
			print_vector(vector_1,len);
			break;
		case 5:
		    if(TEST)
                printf("RANGE: Enter numbers: n, start, step: ");
			scanf("%d %lf %lf",&len,&start,&step);
	        if(len<0 || len>N) {
                printf("n<0 or n > 100\n");
                break;
            }
			range(vector_1,start,step,len);
			print_vector(vector_1,len);
			break;
		default:
         	printf("Out-of-range test number [1, 5] %d",to_do);
			break;
	}
	return 0;
}