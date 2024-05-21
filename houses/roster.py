# TODO
import cs50
import csv
from sys import argv, exit

if(len(argv) != 2):
    print("./Usage roster.py FamilyName")
    exit(1)

house = argv[1]

db = cs50.SQL("sqlite:///students.db")
data = db.execute("SELECT first, middle, last , birth FROM students WHERE house=? ORDER BY last,first", house)

for row in data:
    if(row['middle'] == "NULL"):
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")

exit(0)