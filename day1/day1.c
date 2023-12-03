
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *digits[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int is_written_digit(const char *buf)
{
    for (int i = 0; i < 9; ++i)
    {
        if (strncmp(digits[i], buf, strlen(digits[i])) == 0)
        {
            return i + 1;
        }
    }
    return -1;
}

int main(void)
{
    FILE *f = fopen("sample.txt", "r");
    if (!f)
    {
        return EXIT_FAILURE;
    }

    char line[256];
    int sum = 0;
    while (fgets(line, sizeof(line), f))
    {
        int num = 0;
        for (int i = 0; i < strlen(line); ++i)
        {
            int n;
            if (isdigit(line[i]))
            {
                num = (line[i] - '0') * 10;
                break;
            }
            else if ((n = is_written_digit(line + i)) != -1)
            {
                num = n * 10;
                break;
            }
        }
        int last_digit = 0;
        for (int i = 0; i < strlen(line); ++i)
        {
            int n;
            if (isdigit(line[i]))
            {
                last_digit = line[i] - '0';
            }
            else if ((n = is_written_digit(line + i)) != -1)
            {
                last_digit = n;
            }
        }
        num += last_digit;
        sum += num;
    }
    printf("%d\n", sum);
    fclose(f);
    return EXIT_SUCCESS;
}