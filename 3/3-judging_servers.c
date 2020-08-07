/*******************************************************************************
 * Judging Servers
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// Sample Input
// T            1 <= T <= 50

// S            1 <= S <= 1000
// N            1 <= N <= S
// Pi           0 ≤ Pi ≤ 109

// 2

// 3 2
// 15 14 15

// 5 3
// 1000 560 30 85 100 900

// Sample output
// Case 1: 14
// Case 2: 115

int* arr1[]=  {2};
int* arr2[]=  {3,2};
int* arr3[]=  {15, 14, 15};
int* arr4[]=  {5, 3};
int* arr5[]=  {1000, 560, 30, 85, 100, 900};


int** arr [] = { (int**)&arr1, (int**)&arr2, (int**)&arr3, (int**)&arr4, (int**)&arr5};

/*******************************************************************************
 * Type Structure
 ******************************************************************************/
typedef struct
{
    int S;
    int N;
    int* Prices;

}_Judging_Server_Type;


/*******************************************************************************
 * Function
 ******************************************************************************/
void Print_Judging_Server(_Judging_Server_Type* j_s)
{
    printf("S: %i\r\n", j_s->S);
    printf("N: %i\r\n", j_s->N);
    printf("Price:\r\n");
    for(int i = 0;i<j_s->S;i++)
    {
        printf("%i - %i\r\n",i,j_s->Prices[i]);
    }
    
    
}

void Get_Server_Price(_Judging_Server_Type* j_s)
{
    int server_price = 0;
    int count = j_s->N-1;
    int s = j_s->S;

    int *temp_val ;
    for(int i = 0;i<s;i++)
    {
        temp_val = j_s->Prices[i];
        for(int j = i;j<s;j++)
        {    
            if ( temp_val > j_s->Prices[j])
            {
                j_s->Prices[i] = j_s->Prices[j];
                j_s->Prices[j] = temp_val;
                temp_val = j_s->Prices[i];
            }
        }
    }
    
    for(int i = 0;i<count;i++)
    {
        server_price +=j_s->Prices[i];
    }
    
    printf("%i\r\n",server_price);
    
}

/*******************************************************************************
 * Main
 ******************************************************************************/
int main(int argc, char *argv[])
{
    int T = arr[0][0];
    _Judging_Server_Type* j_s = calloc(T,sizeof(_Judging_Server_Type));

    for(int i = 0;i<T;i++)
    {
        j_s[i].S = arr[i*2+1][0];
        j_s[i].N = arr[i*2+1][1];

        int s = j_s[i].S;
        j_s[i].Prices = calloc(s,sizeof(int));
        for(int j = 0;j<s;j++)
        {
            j_s[i].Prices[j] = arr[i*2+2][j];
        }
    }
    
    for(int i = 0;i<T;i++)
    {
        Get_Server_Price(j_s+i);
    }
    


    for(int i = 0;i<T;i++)
    {
        free(j_s[i].Prices);
    }
    
    free(j_s);
    return 0;
}