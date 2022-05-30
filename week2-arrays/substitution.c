#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool check_all_alpha(char *key);
char *toLower(char *s);
char cipher(char *key, char c);

string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26) 
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    if (!check_all_alpha(argv[1]))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = toLower(argv[1]);
    string plaintext = get_string("plaintext: ");
    char new_char;

    printf("ciphertext: ");
    for (int i = 0; plaintext[i]; i++)
    {
        if (isalpha(plaintext[i]))
        {
            new_char = cipher(key, plaintext[i]);
            if (isupper(plaintext[i]))
            {
                printf("%c", toupper(new_char));
            }
            else
            {
                printf("%c", new_char);
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}


bool check_all_alpha(char *key)
{
    for (int i = 0; key[i]; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
    }
    return true;
}


char *toLower(char *s)
{
    for (int i = 0; s[i]; i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

char cipher(char *key, char c)
{
    char *position_ptr = strchr(ALPHABET, tolower(c));
    int position = (position_ptr == NULL ? -1 : position_ptr - ALPHABET);
    return key[position];
}
