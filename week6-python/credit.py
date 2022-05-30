import sys


def main():
    card: str = input('Number: ')
    if len(card) > 16:
        print('INVALID')
        sys.exit(0)

    luhns_sum = apply_luhn(card)
    if luhns_sum % 10 != 0:
        print('INVALID')
        sys.exit(0)

    identify_card(card)


def apply_luhn(card: str):
    luhns_sum: int = 0
    odd_pos: list = []
    even_pos: list = []
    card = card[::-1]

    for i, digit in enumerate(card, 1):
        try:
            if i % 2 == 0:
                even_pos.append(int(digit))
            else:
                odd_pos.append(int(digit))
        except ValueError:
            print('INVALID')
            sys.exit(0)
    
    for item in even_pos:
        temp = 2 * item
        if temp > 9:
            temp = temp - 9
        luhns_sum += temp

    for item in odd_pos:
        luhns_sum += item      

    return luhns_sum  


def identify_card(card: str):
    if int(card[0]) == 4 and len(card) in [13, 16]:
        print('VISA')
    elif int(card[:2]) in [34, 37] and len(card) == 15:
        print('AMEX')
    elif (int(card[:2]) >= 51 or int(card[:2]) <= 55) and len(card) == 16:
        print('MASTERCARD')
    else:
        print("INVALID")
    sys.exit(0)


main()
