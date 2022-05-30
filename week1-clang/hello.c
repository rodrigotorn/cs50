#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Gets the person's name and says hello
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}
