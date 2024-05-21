import math
from cs50 import get_string
from sys import exit


def main():
    num = "a"
    while(num.isdigit() == False):
        num = get_string("Number : ")

    nlen = len(num)

    if(check_number(num)):
        if((nlen == 16 or nlen == 13) and num[0] == "4"):
            print("VISA")
            exit(0)
        elif(nlen == 15 and num[0] == "3" and (num[1] == "4" or num[1] == "7")):
            print("AMEX")
            exit(0)
        elif(nlen == 16 and num[0] == "5" and (num[1] == "1" or num[1] == "2" or num[1] == "3" or num[1] == "4" or num[1] == "5")):
            print("MASTERCARD")
            exit(0)
        else:
            print("INVALID!")
        exit(0)
    else:
        print("INVALID!")
        exit(0)
    exit(0)


def check_number(n):
    tmp = 0
    t = 1

    s = ''.join(reversed(n))
    for i in range(len(s)):

        b = int(s[i])
        if(t % 2 == 1):
            tmp += b
        else:
            a = 2 * b
            if(a >= 10):
                tmp += math.floor(a/10) + a % 10
            else:
                tmp += a
        t = t + 1

    if((tmp % 10) == 0):
        return True

    return False


main()