from cs50 import get_int
from sys import exit


def main():
    while(1):
        h = get_int("Height : ")
        if(h >= 1 and h <= 8):
            break
    for i in range(h):
        print_space(h - 1 - i)
        print_hash(i+1)
        print()
    exit(0)


def print_hash(h):
    for i in range(h):
        print("#", end="")


def print_space(h):
    for i in range(h):
        print(" ", end="")


main()

