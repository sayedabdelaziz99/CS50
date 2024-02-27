#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long Number = get_long("Number: ");
    long rNumber = Number;
    long rNumber2 = Number;
    long length = 0;
    for (int i = 0; i < 50 ; i++)
    {
        long rem = rNumber % 10;
        if (rem >= 0 && rNumber > 0)
        {
            rNumber = rNumber / 10;
            length = length + 1;
        }
        else
        {
            if (length > 16 || length < 12)
            {
                printf("%li \n", length);
                return 0;
            }
            else
             {
                int fprod = 0;
                int sprod = 0;
                for (int j = 1; j < length+1 ; j++)
                {
                    long num = rNumber2 % 10;
                    int count = j % 2;
                    if (count != 0)
                    {
                        fprod = fprod + num;
                        num = rNumber2 / 10;
                    }
                    else
                    {
                        int f = 0;
                        int s = 0;
                        int a = num * 2;
                        if (a > 9)
                        {
                            f = a / 10;
                            s = a % 10;
                        }
                        sprod = sprod + f + s;
                        num = rNumber2 / 10;
                    }
                        int sum = (fprod + sprod) % 10;
                        if (j == (length - 1) && sum > 0)
                        {
                            printf("%li \n", length);
                            return 0;
                        }
                        else
                        {
                            int power = length - 2;
                            int first2 = Number / pow(10,power);
                        }
                }
            }
        }
    }
}
