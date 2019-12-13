#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int LilEndianHexadecimalToDecimal(char hex[])
{
    int hexsize = strlen(hex);
    char lil[hexsize];

    for (int i = 1; i < hexsize; i = i + 2)
    {
        lil[i - 1] = hex[hexsize - 1 - i];
        lil[i] = hex[hexsize - i];
    }

    int len = strlen(lil);

    // Initializing base value to 1, i.e 16^0
    int base = 1;

    int dec_val = 0;

    // Extracting characters as digits from last character
    for (int i = len - 1; i >= 0; i--)
    {
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value.
        if (lil[i] >= '0' && lil[i] <= '9')
        {
            dec_val += (lil[i] - 48) * base;

            // incrementing base by power
            base = base * 16;
        }

        // if character lies in 'A'-'F' , converting
        // it to integral 10 - 15 by subtracting 55
        // from ASCII value
        else if (lil[i] >= 'A' && lil[i] <= 'F')
        {
            dec_val += (lil[i] - 55) * base;

            // incrementing base by power
            base = base * 16;
        }
    }

    return dec_val;
}

int main(int argc, char *argv[])
{
    printf("%d\n",LilEndianHexadecimalToDecimal(argv[1]));
    return 0;
}
