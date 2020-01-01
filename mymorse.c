#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *morseEncode(char x)
{
    switch (x)
    {
    case 'a':
        return ".-";
    case 'b':
        return "-...";
    case 'c':
        return "-.-.";
    case 'd':
        return "-..";
    case 'e':
        return ".";
    case 'f':
        return "..-.";
    case 'g':
        return "--.";
    case 'h':
        return "....";
    case 'i':
        return "..";
    case 'j':
        return ".---";
    case 'k':
        return "-.-";
    case 'l':
        return ".-..";
    case 'm':
        return "--";
    case 'n':
        return "-.";
    case 'o':
        return "---";
    case 'p':
        return ".--.";
    case 'q':
        return "--.-";
    case 'r':
        return ".-.";
    case 's':
        return "...";
    case 't':
        return "-";
    case 'u':
        return "..-";
    case 'v':
        return "...-";
    case 'w':
        return ".--";
    case 'x':
        return "-..-";
    case 'y':
        return "-.--";
    case 'z':
        return "--..";

        //numbers
    case '0':
        return "-----";
    case '1':
        return ".----";
    case '2':
        return "..---";
    case '3':
        return "...--";
    case '4':
        return "....- ";
    case '5':
        return .....";
    case '6':
        return "-.... ";
    case '7':
        return "--...";
    case '8':
        return "---.. ";
    case '9':
        return "----.";

        //others
    case ' ':
        return " ";
    case ':':
        return "---... ";
    case '-':
        return "-....- ";
            case '+':
        return "·−·−·";
    }
}

void morseCodePrint(char *s)
{
    char str[50];
    //concats morse code letter by letter
    for (int i = 0; s[i] != '\0'; i++)
        strcat(str, morseEncode(s[i]));
    //end result
    printf("%s", str);
}

//same function with return value
char *morseCode(char *s)
{
    //allocate memory
    char *str = (char *)malloc(sizeof(char) * 3);
    //concats morse code letter by letter
    for (int i = 0; s[i] != '\0'; i++)
        strcat(str, morseEncode(s[i]));
    //end result
    return str;
}

char *strlwr(char *str)
{
    unsigned char *p = (unsigned char *)str;

    while (*p)
    {
        *p = tolower((unsigned char)*p);
        p++;
    }

    return str;
}

int main(int argc, char *argv[])
{
    printf("Morse Code of %s is:\t %s\n", argv[1], morseCode(strlwr(argv[1])));
    //  morseCode(strlwr(argv[1]));
    return 0;
}
