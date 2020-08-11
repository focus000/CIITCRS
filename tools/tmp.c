#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    for (int i = 0; i < 256; i++)
    {
        char str[7];
        str[0] = '\0';
        strcat(str, "%ld, ");
        if ((i % 6) == 5)
        {
            strcat(str, "\n");
        }
        printf(str, rand());
    }
}