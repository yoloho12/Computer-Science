#include <cs50.h>
#include <stdio.h>

void print_space(int);
void print_hash(int);

int get_height(void);
int main(void)
{
  
    int h = 0;
   
    while ((h < 1) || (h > 8))
    {
        h = get_int("Height :");
    }
   
    int s = h - 1;

    for (int i = 1; i < (h + 1) ; i++)
    {
        print_space(s);
        print_hash(i); 
        s--;
        printf("  ");
        print_hash(i);
        printf("\n");
    }
}

void print_space(int s)
{
    for (int i = 0; i < s ; i++)
    {
        printf(" ");
    }
}

void print_hash(int hash)
{
    for (int i = 0 ; i < hash ; i++) 
    {
        printf("#");
    }   
}

