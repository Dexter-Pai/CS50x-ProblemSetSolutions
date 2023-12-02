import csv
import sys


with open('2018m.csv', 'r') as file:
    reader = csv.DictReader(file)
    teams = {}
    for row in reader:
        if row['team'] in teams:
            teams[row['team']] += 1
        elif not row['team'] in teams:
            teams[row['team']] = 1

print(teams)
count = 0
for keys in sorted(teams.keys(), reverse=True):
    if count < 3:
        print(keys)
        count += 1

# print(teams['Uruguay'])