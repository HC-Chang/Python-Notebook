/*******************************************************************************
 * Search Engine
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define String_Size 100
// T    (1<= T <= 15)
// N    (1<= N <= 104)
// Q    (1<= N <= 104)

// NOTE Sample Input
// 2

// 3 6

// apple lettuce limes avocado
// onion cranberries apple limes
// escarole corn28corn apple lettuce limes avocado

// limes avocado
// apple lettuce
// limes
// apple
// app
// apple limes

// 3 3

// apple iphone se 2
// iphone 11 max pro
// iphone 11 pro max

// apple iphone
// max pro
// Iphone

char* arr1[]=  {"2"};
char* arr2[]=  {"3","6"};
char* arr3[]=  {"apple lettuce limes avocado"};
char* arr4[]=  {"onion cranberries apple limes"};
char* arr5[]=  {"escarole corn28corn apple lettuce limes avocado"};
char* arr6[]=  {"limes avocado"};
char* arr7[]=  {"apple lettuce"};
char* arr8[]=  {"limes"};
char* arr9[]=  {"apple"};
char* arr10[]=  {"app"};
char* arr11[]=  {"apple limes"};
char* arr12[]=  {"3","3"};
char* arr13[]=  {"apple iphone se 2"};
char* arr14[]=  {"iphone 11 max pro"};
char* arr15[]=  {"iphone 11 pro max"};
char* arr16[]=  {"apple iphone"};
char* arr17[]=  {"max pro"};
char* arr18[]=  {"Iphone"};

char** arr [] = { (char**)&arr1, (char**)&arr2, (char**)&arr3, (char**)&arr4, (char**)&arr5,
                            (char**)&arr6, (char**)&arr7, (char**)&arr8, (char**)&arr9, (char**)&arr10,
                            (char**)&arr11, (char**)&arr12, (char**)&arr13, (char**)&arr14, (char**)&arr15,
                            (char**)&arr16, (char**)&arr17, (char**)&arr18};

/*******************************************************************************
 * Type Structure
 ******************************************************************************/
typedef struct
{
    int n;
    int q;
    char ** data;
    char ** key;
}Serach_Engine_Type;

typedef enum
{
    FALSE,
    TRUE
}Ture_False_Type;
/*******************************************************************************
 * Function
 ******************************************************************************/
int Length_String(char* s)
{
    int length = 0;
    while(*s != '\0')
    {
        length += 1;
        s+=1;
        if (length >105)
        {
            return 0;
        }
    }

    return length;
}

void Copy_String(char * s1, int count , char* source)
{
    if (s1 == NULL)
    {
        s1 = calloc(count+1,sizeof(char));
    }   

    for(int i = 0;i<count;i++)
    {
        s1[i] = source[i];
    }
    // s1[count] = '\0';
}

void Print_Char_Array(char* s , int count)
{
    for(int i = 0;i<count;i++)
    {
        printf("%c",s[i]);
    }
    printf("\r\n");
    
}

int Map_String(char*s1, char* s2)
{
    int TF = FALSE;
    int len1 = Length_String(s1);
    int len2 = Length_String(s2);

    char* key ;
    char* data;
    char* temp_data;
    int len_count = 0;

    if (len2 >len1)
    {
        key = calloc(len1,sizeof(char));
        for(int i = 0;i<len1;i++)
        {
            key[i] = s1[i];
        }
        // key[len1] = '\0';

        data = calloc(len2,sizeof(char));
        for(int i = 0;i<len2;i++)
        {
            data[i] = s2[i];
        }
        // data[len2] = '\0';

        len_count = len2-len1+1;
    }
    else
    {
        key = calloc(len2,sizeof(char));
        for(int i = 0;i<len2;i++)
        {
            key[i] = s2[i];
        }
        // key[len2] = '\0';

        data = calloc(len1,sizeof(char));
        for(int i = 0;i<len1;i++)
        {
            data[i] = s1[i];
        }
        // data[len1] = '\0';
        
        len_count = len1-len2+1;
    }

    int l_key = Length_String(key);
    int l_data = Length_String(data);
    temp_data = calloc(l_key+1,sizeof(char));

    int t_count = 0;
    for(int i = 0;i<len_count;i++)
    {
        // printf("key_data:\t");
        // Print_Char_Array(key,l_key);

            // NOTE  Remember to Compare ' ' & '\0'
            Copy_String(temp_data, l_key+1,data+i);
            
            // printf("temp_data:\t");
            // Print_Char_Array(temp_data,l_key);
            // printf("\r\n");
            
            // NOTE String Higher Lower Case -> All to Lower Case
            for(int j= 0;j<l_key;j++)
            {
                temp_data[j] = tolower(temp_data[j]);
                key[j] = tolower(key[j]);
                if (temp_data[j] == key[j])
                {
                    t_count ++;
                }
            }
            if(temp_data[l_key] == ' ' || temp_data[l_key]=='\0')
            {
                t_count++;
            }


            if (t_count == l_key+1)
            {  
                free(key);
                free(data);
                free(temp_data);
                return TRUE;
            }

            t_count = 0;
            
            // printf("-----\r\n");
            
        }

    free(key);
    free(data);
    free(temp_data);
    return TF;
}

void Search_Answer (Serach_Engine_Type*s)
{
    int n = s->n;
    int q = s->q;
    // printf("n: %i\r\n",n);
    // printf("q: %i\r\n",q);
    
    int count =0;
    int l_data = 0;
    int l_key = 0;
    char * temp_string;
    for(int i = 0;i<q;i++)
    {
        temp_string = s->key[i];
        l_key = Length_String(temp_string);
        // printf("l_key: %i\r\n",l_key);
        // printf("%s\r\n",temp_string);
        
        count = 0;
        int match = FALSE;
        for(int j = 0;j<n;j++)
        {
            match = FALSE;
            match = Map_String(s->key[i],s->data[j]);
            if(match == TRUE)
            {
                count ++;
                // continue;
            }
        }
        
        printf("%i\r\n",count);
        

    }
    
}

/*******************************************************************************
 * Main
 ******************************************************************************/

int main(int argc, char *argv[])
{
    //  Check Input Data

int length = 0;
    for(int i = 0;i<18;i++)
    {
    //     // Print arr 
        // printf("%i - %s\r\n",i, arr[i][0]);
        // length = Length_String(arr[i][0]);
        // printf("%i - Length: %i\r\n",i, length);
        
    }

    int  T =atoi(arr[0][0]);
    printf("T: %i\r\n",T);

    Serach_Engine_Type *se = calloc(T,sizeof(Serach_Engine_Type));
    
    // Read Input Data
    int index = 0;
    int n =0;
    int q=0;
    for(int i = 0;i<T;i++)
    {
        se[i].n = atoi(arr[index + 1][0]);
        se[i].q = atoi(arr[index + 1][1]);
        // printf("n: %i\r\n",se[0].n);
        // printf("q: %i\r\n",se[0].q);

        n = se[i].n;
        se[i].data = (arr[index+2]);
        // for(int j = 0;j<n;j++)
        // {
            // printf("data: %s\r\n",se[i].data[j]);
        // }
        
        q = se[i].q;
        se[i].key = (arr[index+2+n]);
        // for(int j = 0;j<q;j++)
        // {
        //     printf("key: %s\r\n",se[i].key[j]);
        // }
        
        index = index + n+ q+1;
        // printf("\r\n");
        
    }

    // Search Engine Start
    for(int i = 0;i<T;i++)
    {
        Search_Answer(se+i);
        printf("\r\n");
        
    }
    
    

    
    free(se);
    return 0;
}