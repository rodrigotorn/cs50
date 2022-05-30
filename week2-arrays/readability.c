#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char *toLower(char *s);
int *count_text_attributes(char *s);
void print_grade(int grade);

int main(void) 
{
    string text = get_string("Text: ");
    text = toLower(text);

    int *p = count_text_attributes(text);
    int counts[3];
    for (int i = 0; i < 3; i++)
    {
        counts[i] = *(p + i);
    }

    float L = 100 * (float) counts[0] / counts[1];
    float S = 100 * (float) counts[2] / counts[1];
    int grade = round(0.0588 * L - 0.296 * S - 15.8);
    print_grade(grade);
}


char *toLower(char *s)
{
    for (int i = 0; s[i]; i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}


int *count_text_attributes(char *s)
{
    int static counts[3];

    counts[0] = 0; // counts letters
    counts[1] = 1; // counts words
    counts[2] = 0; // counts sentences

    for (int i = 0; s[i]; i++)
    {
        if ((s[i] >= 'a') & (s[i] <= 'z'))
        {
            counts[0] = counts[0] + 1;
        }

        if (s[i] == ' ')
        {
            counts[1] = counts[1] + 1;
        }

        if ((s[i] == '.') | (s[i] == '!') | (s[i] == '?'))
        {
            counts[2] = counts[2] + 1;
        }
    }
    return counts;
}

void print_grade(int grade)
{
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else 
    {
        printf("Grade %i\n", grade);
    }
}
