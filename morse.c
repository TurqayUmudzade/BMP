#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Takes a char and converts it to morse code
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
    case 'J':
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
    case 'O':
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
    case 'T':
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
        return ".-..";
    case '1':
        return "--";
    case '2':
        return "-.";
    case '3':
        return "---";
    case '4':
        return ".--.";
    case '5':
        return "--.-";
    case '6':
        return ".-.";
    case '7':
        return "...";
    case '8':
        return "-";
    case '9':
        return "..-";

    //Others,mostly for date formats
    case ' ':
        return " ";
    case ':':
        return "---... ";
    case '-':
        return "-....- ";
    case '+':
        return ".-.-.";
    case '/':
        return "-..-.";

    //default
    default:
        printf("Error:Unknown Character\n");
    }
}

//prints mouse code
void morseCodePrint(char *s)
{
    char str[50];
    //concats morse code letter by letter
    for (int i = 0; s[i] != '\0'; i++)
        strcat(str, morseEncode(s[i]));
    //end result
    printf("%s", str);
}

//gets date from linux terminal command date
char *getDate()
{
    char *res = (char *)malloc(100 * sizeof(char));
    FILE *fp = popen("date", "r");
    fgets(res, 100, fp);
    res[strlen(res) - 1] = '\0';
    pclose(fp);
    return res;
}

//same as morseCodePrint but returns a string instead of void
char *morseCode(char *s)
{
    //allocate memory
    char *str = (char *)calloc(1,sizeof(char) * strlen(s)+100);
    //concats morse code letter by letter
    for (int i = 0; s[i] != '\0'; i++)
        strcat(str, morseEncode(s[i]));
    //end result
    return str;
}

//changes a string to all lower letters since morseEncode function is for lower letters
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


// int main(int argc, char *argv[])
// {
//     char str[50];
//     strcpy (str, argv[1]);
//     char date[100];
    
//     strcpy (date,getDate());
//     printf("Morse Code of %s is:\t %s\n", str, morseCode(strlwr(argv[1])));
//     printf("Morse Code of %s is:\t %s\n", date, morseCode(strlwr(getDate())));
//     return 0;
// }