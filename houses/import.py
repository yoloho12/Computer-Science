import cs50
import csv
from sys import argv, exit

if(len(argv) != 2):
    print("./Usage import.py characters.csv")
    exit(1)

if not(argv[1].endswith(".csv")):
    print("Need a *.csv file")
    exit(1)

open("students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")
db.execute("CREATE TABLE students (id INT, first TEXT, middle TEXT, last TEXT, house TEXT, birth INT)")
i = 1
with open(argv[1]) as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        house = row['house']
        birth = row['birth']
        n = row['name'].split(" ")
        namelen = len(n)

        if(namelen == 2):
            db.execute("INSERT INTO students (id, first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?, ?)",
                       i, n[0], "NULL", n[1], house, birth)

        if(namelen == 3):
            db.execute("INSERT INTO students (id, first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?, ?)",
                       i, n[0], n[1], n[2], house, birth)
        i = i + 1
exit(0)