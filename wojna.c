#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NUMBER_OF_CARDS 52

//Random function between [a,b] - auxiliary for rand_permutation
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

//Card shuffling
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

//Player A's queue in the cyclic buffer
#define KA_SIZE NUMBER_OF_CARDS
int ka[KA_SIZE];
int lena=0;    //lena - the number of cards of player A

void ka_push(int cli_nr) {
    ka[lena]=cli_nr;
    lena++;
}

int ka_pop(void) {
    if(lena==0)
        return -1;
    else
    {
        int num=ka[0];
        for(int i=0;i<lena;i++)
            ka[i]=ka[i+1];
        lena--;
        return num;
    }
}

int ka_state(void) {
    return lena;
}

void ka_print(void) {
    for(int i=0;i<lena;i++)
        printf("%i ",ka[i]);
    printf("\n");
}

//Player B's queue in the cyclic buffer
#define KB_SIZE NUMBER_OF_CARDS
int kb[KB_SIZE];
int lenb=0;    //lenb - the number of cards of player B

void kb_push(int cli_nr) {
    kb[lenb]=cli_nr;
    lenb++;
}

int kb_pop(void) {
    if(lenb==0)
        return -1;
    else
    {
        int num=kb[0];
        for(int i=0;i<lenb;i++)
            kb[i]=kb[i+1];
        lenb--;
        return num;
    }
}

int kb_state(void) {
    return lenb;
}

void kb_print(void) {
    for(int i=0;i<lenb;i++)
        printf("%i ",kb[i]);
    printf("\n");
}

//Player A's queue of cards awaiting the outcome of the war
#define WA_SIZE NUMBER_OF_CARDS
int wa[WA_SIZE];
int lenwa=0;   //lenwa - number of cards of player A waiting for the result of the war

void wa_push(int cli_nr) {
    wa[lenwa]=cli_nr;
    lenwa++;
}

int wa_pop(void) {
    if(lenwa==0)
        return -1;
    else
    {
        int num=wa[0];
        for(int i=0;i<lenwa;i++)
            wa[i]=wa[i+1];
        lenwa--;
        return num;
    }
}

int wa_state(void) {
    return lenwa;
}

void wa_print(void) {
    for(int i=0;i<lenwa;i++)
        printf("%i ",wa[i]);
    printf("\n");
}

//Player B's queue of cards awaiting the outcome of the war
#define WB_SIZE NUMBER_OF_CARDS
int wb[WB_SIZE];
int lenwb=0;   //lenwb - number of cards of player B waiting for the result of the war

void wb_push(int cli_nr) {
    wb[lenwb]=cli_nr;
    lenwb++;
}

int wb_pop(void) {
    if(lenwb==0)
        return -1;
    else
    {
        int num=wb[0];
        for(int i=0;i<lenwb;i++)
            wb[i]=wb[i+1];
        lenwb--;
        return num;
    }
}

int wb_state(void) {
    return lenwb;
}

void wb_print(void) {
    for(int i=0;i<lenwb;i++)
        printf("%i ",wb[i]);
    printf("\n");
}

int main(void) {
    int seed;
    scanf("%i ",&seed);
    srand(seed);
    int n=NUMBER_OF_CARDS,tab[n];
    for(int i=0;i<n;i++)
        tab[i]=i;
    rand_permutation(n,tab);        
    //Distribution of cards to players
    for(int i=0;i<n/2;i++)
    {
        ka_push(tab[i]);
        kb_push(tab[n/2+i]);
    }
    int version,conflicts,number=0;
    scanf("%i %i",&version,&conflicts);
    //This is a simplified version - instead of war it goes to the end of the line
    if(version==1) {
        while(conflicts>0) {
            int a=ka_pop(),b=kb_pop();
            //Player A has the stronger card
            if(a/4>b/4) {
                ka_push(a);
                ka_push(b);
            }
            //Player B has the stronger card
            else if(a/4<b/4) {
                kb_push(b);
                kb_push(a);
            }
            //War by simplified rules
            else {
                ka_push(a);
                kb_push(b);
            }
            conflicts--;
            number++;
            if(ka_state()==0 || kb_state()==0)
                break;
        }
        //Player A has no cards
        if(ka_state()==0) {
            printf("3\n");
            kb_print();
        }
        //Player B has no cards
        else if(kb_state()==0) {
            printf("2 %i\n",number);
            //ka_print();
        }
        //The number of conflicts is over
        else
            printf("0 %i %i\n",ka_state(),kb_state());
    }
    //This is the standard version - along with the element of war
    else {
        while(conflicts > 0) {
            int a=ka_pop(),b=kb_pop();
            wa_push(a);
            wb_push(b);
            //Player A has the stronger card
            if(a/4>b/4) {
                while(wa_state()>0)
                    ka_push(wa_pop());
                while(wb_state()>0)
                    ka_push(wb_pop());
            }
            //Player B has the stronger card
            else if(a/4<b/4) {
                while(wb_state()>0)
                    kb_push(wb_pop());
                while(wa_state()>0)
                    kb_push(wa_pop());
            }
            //War according to standard rules
            else {
                wa_push(ka_pop());
                wb_push(kb_pop());
            }
            conflicts--;
            number++;
            //At least one player no longer has cards
            if(ka_state()==0 || kb_state()==0)
                break;
        }
        //War is inconclusive due to lack of cards during the war
        if(wa_state()>0 || wb_state()>0)
            printf("1 %i %i\n",ka_state()+wa_state(),kb_state()+wb_state());
        //Player A has no cards
        else if(ka_state()==0) {
            printf("3\n");
            kb_print();
        }
        //Player B has no cards
        else if(kb_state()==0) {
            printf("2 %i\n", number);
            //ka_print();
        }
        //The number of conflicts is over
        else
            printf("0 %i %i\n",ka_state(),kb_state());
    }
    return 0;
}