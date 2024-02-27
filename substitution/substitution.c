#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int chk_vld(int count, string key);
int chk_dub(int count, string key);

int main(int argc, string argv[])
{
    string KEY = argv[1];
    if (chk_vld(argc, KEY) == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (chk_vld(argc, KEY) == 2)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (chk_vld(argc, KEY) == 3)
    {
        printf("key must only contain alphabetic characters\n");
        return 1;
    }
    else if (chk_dub(argc, KEY) == 1)
    {
        printf("key must not contain repeated characters\n");
        return 1;
    }
    else
    {
        string txt = get_string("Plain text : ");
        int txt_length = strlen(txt);
        int length = strlen(KEY);
        printf("ciphertext: ");
        for (int i = 0; i < txt_length; i++)
        {
            if (isalpha(txt[i]))
            {
                if (isupper(txt[i]))
                {
                    int placment1 = txt[i] - 65;
                    printf("%c", toupper(KEY[placment1]));
                }
                else if (islower(txt[i]))
                {
                    int placment2 = txt[i] - 97;
                    printf("%c", tolower(KEY[placment2]));
                }
            }
            else
            {
                printf("%c", txt[i]);
            }
        }
        printf("\n");
    }
}

int chk_vld(int count, string key)
{
    int a = 0;
    if (count != 2)
    {
        a = 1;
    }
    else if (strlen(key) < 26 && count == 2)
    {
        a = 2;
    }
    else if (strlen(key) == 26 && count == 2)
    {
        for (int i = 0; i < 26; i++)
        {
            if (isalpha(key[i]) == 0)
            {
                i = 26;
                a = 3;
            }
        }
    }
    return a;
}

int chk_dub(int count, string key)
{
    int b = 0;
    int length1 = strlen(key);
    if (count == 2 && length1 == 26)
    {
        for (int i = 0; i < length1; i++)
        {
            char current = tolower(key[i]);
            for (int j = 0; j < length1; j++)
            {
                if (i == j)
                {
                    j++;
                }
                if (current == tolower(key[j]))
                {
                    b = 1;
                }
            }
        }
    }
    return b;
}
