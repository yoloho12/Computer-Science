#include<stdio.h>
#include<cs50.h>
#include<math.h>

int len_of_number(long);
int check_num(long, int);
int check_card(long, int);

int main(void)
{
    long number = get_long("Number : ");
    int length = len_of_number(number);
    if (length == 13 || length == 16 || length == 15)
    {
        if (check_num(number, length) == 0)
        {
            int card = check_card(number, length);
            if (card == 1)
            {
                printf("VISA\n");
                return 0;
            }
            else if (card == 2)
            {
                printf("AMEX\n");
            }
            else if (card == 3)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int len_of_number(long number)
{
    int a = number / (long) pow(10, 12);
    int b = number / (long) pow(10, 14);
    int c = number / (long) pow(10, 15);
    // printf("%i\t %i\t %i\n",a,b,c);
    if (a > 0 && a < 10)
    {
        return 13;
    }
    if (b > 0 && b < 10)
    {
        return 15;
    }
    if (c > 0 && c < 10)
    {
        return 16;
    }
    return 0;
}

int check_num(long num, int len)
{
    int sum = 0;
    
    for (long tmp_value = 0, power = 2; power <= len + 1; power = power + 2)
    {
        tmp_value = num % (long) pow(10, power);
        tmp_value = tmp_value / (long) pow(10, (power - 1));
        tmp_value = tmp_value * 2;

        if (tmp_value > 9)
        {
            sum += (tmp_value % 10) + (tmp_value / 10); 
        }
        else
        {
            sum += tmp_value;
        }
        tmp_value = num % (long) pow(10, power - 1);
        tmp_value = tmp_value / (long) pow(10, (power - 2));

        // printf("\n%li- > tmp_value\n\n ",tmp_value);
        sum += tmp_value;
        // printf("\n%i - > tmp_sum\n ",sum);
    }
     
    //  printf("\n%i   - > sum\n ",sum);
    if ((sum % 10) == 0)
    {
        // printf("SUCCESS!");
        return 0;
    }
    else
    {
        return -1;
    }
    return -1;
}   

int check_card(long num, int len)
{

    int test = num / (long) pow(10, len - 1);
    int suffix_test = num / (long) pow(10, len - 2);
    suffix_test = suffix_test % 10;
    if ((len == 16 || len == 13) && (test) == 4)
    {
        return 1;
    }
    if (len == 15 && test == 3 && (suffix_test == 4 || suffix_test == 7))
    {
        return 2;
    }
    if (len == 16 && test == 5 && (suffix_test > 0 && suffix_test < 6))
    {
        return 3;
    }
    return 0;
}
