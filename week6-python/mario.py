import sys
from cs50 import get_int


MAX_HEIGHT: int = 8


def main():
    while True:
        height: int = get_int('Height: ')
        if height > 0 and height <= MAX_HEIGHT:
            break

    print_bricks(height)
    sys.exit(0)


def print_bricks(height: int):
    for i in list(range(1, height + 1)):
        print(' ' * (height - i), end='')
        print('#' * i, end='  ')
        print('#' * i)


main()