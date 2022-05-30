#include <cs50.h>
#include <stdio.h>

void print_brick(int bricks)
{
    for (int i = 1; i <= bricks; i++)
    {
        printf("#");
    }
}

void print_space(int spaces)
{
    for (int i = 1; i <= spaces; i++)
    {
        printf(" ");
    }
}

void print_row(int current_level, int total_height)
{
    print_space(total_height - current_level);
    print_brick(current_level);
    printf("  ");
    print_brick(current_level);
    printf("\n");
}

int main(void)
{
    int height;
    do 
    {
        height = get_int("Height: ");
    }
    while ((height < 1) || (height > 8));

    for (int i = 1; i <= height; i++)
    {
        print_row(i, height);
    }
}