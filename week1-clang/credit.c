#include <cs50.h>
#include <stdio.h>

int *split_digits(long int num)
{
    int static digits[16];
    int i = 0;

    while (num != 0)
    {
        digits[i] = num % 10;
        num /= 10;
        i++;
    }
    return digits;
}


int count_digits(long int num)
{
    int i = 0;
    do
    {
        num /= 10;
        ++i;
    }
    while (num != 0);
    return i;
}


int identify_card(int sum, int first_digit, int second_digit, int digit_cnt)
{
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        int initial_digits = 10 * first_digit + second_digit;
        if ((first_digit == 4) & (digit_cnt == 13 | digit_cnt == 16))
        {
            printf("VISA\n");
        }
        else if ((initial_digits == 34 | initial_digits == 37) & (digit_cnt == 15))
        {
            printf("AMEX\n");
        }
        else if ((initial_digits >= 51 & initial_digits <= 55) & (digit_cnt == 16))
        {
            printf("MASTERCARD\n");
        }
        else 
        {
            printf("INVALID\n");
        }
    }
    return -1;
}


int main(void)
{
    long card = 0;
    do
    {
        card = get_long("Number: ");
    }
    while (card == 0);

    int digit_cnt = count_digits(card);
    int original_digits[digit_cnt], digits[digit_cnt];
    int *p = split_digits(card);
    int sum = 0;

    for (int i = 0; i < digit_cnt; i++)
    {
        original_digits[i] = *(p + i);
        digits[i] = *(p + i);
        if (i % 2 != 0)
        {
            digits[i] = digits[i] * 2;
            if (digits[i] > 9)
            {
                // if the number has 2 digits, consider the sum of the digits
                digits[i] = digits[i] - 9;
            }
        }
        sum = sum + digits[i];
    }

    identify_card(
        sum,
        original_digits[digit_cnt - 1],
        original_digits[digit_cnt - 2],
        digit_cnt);
    return 0;
}
