#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>
#include<math.h>

int count_l(string, int);
int count_w(string, int);
int count_s(string, int);


int main(void)
{
    string p = get_string("Text : ");
    int len = strlen(p);
    // printf("LETTER COUNTS : %i\n", count_l(p,len));
    // printf("Word count : %i\n",count_w(p,len));
    // printf("Sentence count : %i \n",count_s(p,len));
    float L = (float)count_l(p, len) * 100 / count_w(p, len);
    float S = (float)count_s(p, len) * 100 / count_w(p, len);
    // printf("L -> %f ", L);
    // printf("L -> %f ", S);
    
    int i = round((0.0588 * L - 0.296 * S) - 15.8);
    if (i > 15)
    {
        printf("Grade 16+\n");
    }
    else if (i < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", i);
    }
    // printf("Raw Calculation of index value : %i \n",i);
    
    return 0;
}

int count_l(string p, int len)
{
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (isalpha(p[i]))
        {
            count++;
        }
    }
    return count;
}

int count_w(string p, int len)
{
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        
        if (isspace(p[i]))
        {
            count++;
        }
    }
    count++;
    return count;
}

int count_s(string p, int len)
{
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (p[i] == '.' || p[i] == '?' || p[i] == '!')
        {
            count++;
        }
    }    
    return count;
}
