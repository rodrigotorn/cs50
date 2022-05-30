import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print('Usage: python dna.py data.csv sequence.txt')
        sys.exit(1)

    # Read database file into a variable
    database_file = sys.argv[1]
    database: list[dict[dict]] = read_database(database_file)
    
    subseq_cnt: dict = {}
    for key in database[0]['subseq_cnt'].keys():
        subseq_cnt[key] = 0

    # Read DNA sequence file into a variable
    sequence_file = sys.argv[2]
    sequence: str = read_sequence(sequence_file)

    # Find longest match of each STR in DNA sequence
    for key in subseq_cnt.keys():
        subseq_cnt[key] = longest_match(sequence, key)

    # Check database for matching profiles
    match: str = 'No match'
    for item in database:
        if item['subseq_cnt'] == subseq_cnt:
            match = item['name']
            break

    print(match)
    return


def read_database(file_name: str):
    database = []
    subsequences = []
    with open(file_name, 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            person_dict = {}
            person_dict['name'] = row.pop('name')
            person_dict['subseq_cnt'] = \
                {key: int(value) for key, value in row.items()}
            database.append(person_dict)
    
    return database


def read_sequence(file_name: str):
    with open(file_name, 'r') as file:
        sequence: str = file.read().rstrip()
    return sequence


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
