#include<stdio.h>
#include<string.h>
#include<cs50.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>


bool isAllDigit(string argv);
bool checkSymbol(char val);

int main(int argc, string argv[])
{
    //First Check
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./caesar key");
        return 1;
    }

    //Second Check
    int key = 0;
    if (isAllDigit(argv[1]))
    {
        key = atoi(argv[1]);
        // printf(" value after converted!  -> %i\n",key);
        if (key > (pow(2, 23) - 26) && key < 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    string upperArray = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lowerArray = "abcdefghijklmnopqrstuvwxyz";
    string plaintext = get_string(" Plain Text :");
 
    printf("ciphertext: ");

    for (int i = 0, len = strlen(plaintext) ; i < len; i++)
    {
        int p = 0;
        if (isupper(plaintext[i]))
        {
            p = (int)(plaintext[i]) - 65;
            int index = (p + key) % 26;
            printf("%c", upperArray[index]);
        }
        if (islower(plaintext[i]))
        {
            p = (int)(plaintext[i]) - 97;
            int index = (p + key) % 26;
            printf("%c", lowerArray[index]);
        }
        if (isspace(plaintext[i]))
        {
            printf(" ");
        }
        if (checkSymbol(plaintext[i]))
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;

}

bool isAllDigit(string argv)
{
    int count = 0;
    for (int i = 0, len = strlen(argv) ; i < len ; i++)
    {
        if (!isdigit(argv[i]))
        {
            count += 1;
        }
    }
    if (count > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool checkSymbol(char val)
{
    if (val < 65 || val > 90)
    {
        if (val < 97 || val > 122)
        {
            if (val != 32)
            {
                return true;
            }
        }
    }
    else
    {
        return false;
    }
    return false;
}