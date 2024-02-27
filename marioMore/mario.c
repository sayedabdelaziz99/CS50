#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int Height;
    do
    {
        Height = get_int("Height :");
    }
    while (Height < 1 || Height > 8);
    for (int i = 0; i < Height; i++)
    {
        for (int j = Height - 1; j > i; j--)
        {
            printf(" ");
        }
        for (int k = 0; k <= i; k++)
        {
            printf("#");
            if (k == i)
            {
                printf("  ");
                for (int l = 0; l <= i; l++)
                {
                    printf("#");
                }
                printf("\n");
            }
        }
    }
}
