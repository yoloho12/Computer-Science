from sys import argv, exit
import csv
import numpy as np


def main():
    if(len(argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    seq = argv[2]
    name = ''
    result = 0

    with open(argv[1], newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            count = 0
            if(len(row) == 4):
                a = int(row['AGATC']) == dna_count('AGATC', seq)
                b = int(row['AATG']) == dna_count('AATG', seq)
                c = int(row['TATC']) == dna_count('TATC', seq)
                if(a and b and c):
                    name = row['name']
            else:
                a = int(row['AGATC']) == dna_count('AGATC', seq)
                b = int(row['AATG']) == dna_count('AATG', seq)
                c = int(row['TATC']) == dna_count('TATC', seq)
                d = int(row['TCTAG']) == dna_count('TCTAG', seq)
                e = int(row['TTTTTTCT']) == dna_count('TTTTTTCT', seq)
                f = int(row['TATC']) == dna_count('TATC', seq)
                g = int(row['GAAA']) == dna_count('GAAA', seq)
                h = int(row['TCTG']) == dna_count('TCTG', seq)
                # print(a,b,c,d,e,f,g,h)
                bool_arr = np.array([a, b, c, d, e, f, g, h], dtype=bool)
                for i in bool_arr:
                    if(i):
                        count = count + 1
                        if(count >= 7):
                            name = row['name']

    if(name != ''):
        print(name)
    else:
        print("No match")


def dna_count(STR, arg):
    with open(arg, "r") as file:
        data = file.readline()
        arr = data.split(STR)
        r = 0
        c = 0
        for i in arr:
            if(i == ''):
                c = c + 1
                if(r < c):
                    r = c
            else:
                c = 0

        # print(r+1)
        return r+1


main()