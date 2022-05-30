import sys
from cs50 import get_string


def main():
    text: str = get_string('Text: ').lower()
    attributes: dict = count_text_attributes(text)
    index: int = calc_index(attributes)
    print_result(index)
    sys.exit(0)


def count_text_attributes(text: str):
    attributes = {
        'letters': 0,
        'words': 1,
        'sentences': 0,
    }
    for t in text:
        if t >= 'a' and t <= 'z':
            attributes['letters'] += 1
        elif t == ' ':
            attributes['words'] += 1
        elif t in ['.', '!', '?']:
            attributes['sentences'] += 1
    return attributes


def calc_index(attributes: dict):
    L: float = 100 * attributes['letters'] / attributes['words']
    S: float = 100 * attributes['sentences'] / attributes['words']
    index: int = int(round(0.0588 * L - 0.296 * S - 15.8))
    return index


def print_result(index: int):
    if index >= 16:
        print('Grade 16+')
    elif index < 1:
        print('Before Grade 1')
    else:
        print(f'Grade {index}')


main()