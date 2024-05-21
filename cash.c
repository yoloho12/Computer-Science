#include<stdio.h>
#include<cs50.h>
#include<math.h>

int determiner(int);

int main(void)
{
    int cent = 0;
    while (cent <= 0)
    {
        cent = round(get_float("Cash Owed : ") * 100);
    }

    int count = 0;

    while (cent != 0)
    {
        int divider = determiner(cent);
        count += cent / divider;
        cent = cent % divider;
    }
    printf("%i\n", count);
}        

int determiner(int cent)
{
    if ((cent / 25) != 0)
    {
        return 25;
    }
    if ((cent / 10) != 0)
    {
        return 10;
    }
    if ((cent / 5) != 0)
    {
        return 5;
    }
    if ((cent / 1) != 0)
    {
        return 1;
    }
    return 0;
}
