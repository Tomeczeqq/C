#include <stdio.h>
#include <math.h>
#define TEST 1  // 0 is for automatic testing

//Function declarations (prototypes):
double stack_push(double x);
double stack_pop(void);
int stack_state(void);
double queue_push(int how_many);
int queue_pop(int how_many);
int queue_state(void);
void queue_print(void);
double cbuff_push(int cli_nr);
int cbuff_pop(void);
int cbuff_state(void);
void cbuff_print(void);

int main(void) {
    int to_do,n,ans,client_nr,operation_code;
    double x,f_ans;
    if(TEST)
        printf("Test number = ");
    scanf("%d",&to_do);
    switch(to_do) {
        case 1:
            if(TEST)          //0 provides the stack state and terminates the sequence of operations
                printf("Sequence of operations (on one line, separated by spaces):\n");
            do {
                scanf("%lf",&x);
                if(x>0) {
                    f_ans=stack_push(x);
                    if(f_ans==INFINITY)
                        printf("%f ",INFINITY);
                }
                else {
                    if(x<0)
                        printf("%.2f ",stack_pop());
                    else
                        printf("\n%d\n",stack_state());
                }
            } while(x!=0.0);
            break;
        case 2:                 //Queue of consecutive natural numbers > 0 (arriving in groups) - implementation in an array with offsets
            if(TEST)            // 0 provides the queue status and ends the queue simulation
                printf("To/from queue (on one line, separated by spaces):\n");
            do {
                scanf("%d",&n);
                if(n>0) {
                    f_ans=queue_push(n);
                    if(f_ans==INFINITY)
                        printf("%f ",INFINITY);
                }
                else {
                    if(n<0) {
                        ans=queue_pop(-n);
                        if(ans<0)
                            printf("-1 ");
                    }
                    else {
                        printf("\n%d\n",queue_state());
                        queue_print();
                    }
                }
            } while(n!=0);
            break;
        case 3:              //Queue of consecutive natural numbers > 0 (arriving one at a time) - implementation in a cyclic buffer
            if(TEST)         // 0 provides the queue status and ends the queue simulation
                printf("To/from queue (on one line, separated by spaces):\n");
            client_nr=0;
            do {
                scanf("%d",&operation_code);
                if(operation_code>0) {
                    f_ans=cbuff_push(client_nr++);
                    if(f_ans==INFINITY)
                        printf("%f ",INFINITY);
                }
                else {
                    if(operation_code<0)
                        printf("%d ",cbuff_pop());
                    else {
                        printf("\n%d\n",cbuff_state());
                        cbuff_print();
                    }
                }
            } while(operation_code!=0);
            break;
        default:
            if(TEST)
                printf("NOTHING TO DO!\n");
    }
    return 0;
}

//Definitions of functions and variables with file scope:
//Stack
#define STACK_SIZE  10
double stack[STACK_SIZE];
int top=0;   //explicit zeroing is not necessary

double stack_push(double x) {
    if(top<STACK_SIZE)
    {
        stack[top]=x;
        top++;
        return 0;
    }
    else
        return INFINITY;
}

double stack_pop(void) {
    if(top>0)
    {
        double r=stack[top-1];
        top--;
        return r;
    }
    else 
        return NAN;
}

int stack_state(void) {
    return top;
}

//Sliding queue in the table
#define QUEUE_SIZE  10
int queue[QUEUE_SIZE];
int in=0, curr_nr=1;  //in - number of customers waiting in line
                      //curr_nr - current customer number: 1st customer gets number = 1

double queue_push(int how_many) {
    int i=9-in;
    while(i>=0 && how_many>0)
    {
        queue[i]=curr_nr;
        in++;
        curr_nr++;
        i--;
        how_many--;
    }
    if(how_many!=0)
    {
        curr_nr+=how_many;
        return INFINITY;
    }
    return 0.0;
}

int queue_pop(int how_many) {
    if(how_many>in)
    {
        for(int i=9;i>=0;i--)
            queue[i]=0;
        in=0;
        return -1;
    }
    else
    {
        in-=how_many;
        int o=9-how_many;
        for(int i=o;i>=0;i--)
        {
            queue[i+how_many]=queue[i];
            queue[i]=0;
        }
        return in;
    }
}

int queue_state(void) {
    return in;
}

void queue_print(void) {
    for(int i=9;i>=0 && queue[i]!=0;i--)
        printf("%i ",queue[i]);
}

//Queue in the cyclic buffer
#define CBUFF_SIZE  10
int cbuff[CBUFF_SIZE];
int len=0;   //len - number of customers waiting in line

double cbuff_push(int cli_nr) {
    if(len==10)
        return INFINITY;
    else
    {
        cbuff[len]=cli_nr;
        len++;
        return 0.0;
    }
}

int cbuff_pop(void) {
    if(len==0)
        return -1;
    else
    {
        int num=cbuff[0];
        for(int i=0;i<len;i++)
            cbuff[i]=cbuff[i+1];
        len--;
        return num;
    }
}

int cbuff_state(void) {
    return len;
}

void cbuff_print(void) {
    for(int i=0;i<len;i++)
        printf("%i ",cbuff[i]);
}