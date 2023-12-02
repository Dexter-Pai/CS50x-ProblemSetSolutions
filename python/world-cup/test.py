import csv
import sys
import random


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    fields = []
    teams = []
    with open('2018m.csv', 'r') as file:

        csvR = csv.DictReader(file)
        # fields = next(csvR)

        for row in csvR:
            teams.append(row)
    # for row in teams:
        # print(', '.join(teams), end="\n\n")

    # print(format(255,"b"))
    # print(fields)
    for row in teams:
        row['rating'] = int(row['rating'])
        print(row['rating'])
    print(teams)



main()