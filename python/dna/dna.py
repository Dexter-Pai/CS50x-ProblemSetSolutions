import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py FILENAME SEQUENCE/*.txt")

    # TODO: Read database file into a variable
    database = []
    with open(sys.argv[1], 'r') as file:
        f = csv.DictReader(file)
        for lines in f:
            database.append(lines)
        # print(database)
        i = 0
        for i in database:
            for k, v in i.items():
                if i[k].isdigit():
                    i[k] = int(v)
        # print(database)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as dnaf:
        dna = dnaf.read()
    # print(dna)

    # TODO: Find longest match of each STR in DNA sequence
    match = []
    for key in database[0].keys():
        if not (key == 'name'):
            k = key
            # print(k)
            match.append(longest_match(dna, k))
    '''
    #FOR FUTURE REFERENCE
    print(match)
    for i in database:
        for key in i.keys():
            k = key
            if not k == 'name':
                match.append(longest_match(dna, k))
    print(match)
            # match.append(longest_match(dna, i[key]))
    '''

    # TODO: Check database for matching profiles
    match_found = False
    if len(match) == 3:
        for i in database:
            if (i['AGATC'] == match[0]) and (i['AATG'] == match[1]) and (i['TATC'] == match[2]):
                print(i['name'])
                match_found = True
        if match_found == False:
            print("No match")
    else:

        for i in database:
            if (i['AGATC'] == match[0]) and (i['TTTTTTCT'] == match[1]) and (i['AATG'] == match[2]) and (i['TCTAG'] == match[3]) and (i['GATA'] == match[4]) and (i['TATC'] == match[5]) and (i['GAAA'] == match[6]) and (i['TCTG'] == match[7]):
                print(i['name'])
                match_found = True
        if match_found == False:
            print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
