from cs50 import get_float
from sys import exit
from math import floor


def main():
    cent = 0
    while(cent <= 0):
        cent = round((get_float("Cash Owed :")) * 100)

    count = 0
    while(cent != 0):
        divider = determiner(cent)
        count += floor(cent/divider)
        cent = cent % divider

    print(count)
    exit(0)


def determiner(cent):
    if((cent / 25) >= 1):
        return 25
    elif(cent / 10 >= 1):
        return 10
    elif(cent / 5 >= 1):
        return 5
    else:
        return 1


main()
