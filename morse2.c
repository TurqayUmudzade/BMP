#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* morseEncode(char x)
{
    // refer to the Morse table
  
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
    // for space
    case 'z':
        return "--..";
    }
}

void morseCode(char* s)
{
    //int lenght=strlen(s);
   // char* s =(char*) malloc(lenght+1);

    for (int i = 0; s[i]!='\0'; i++)
        printf("%s",morseEncode(s[i]));
}


int main()
{
    int lenght=strlen("Hello");
    char* s =(char*) calloc(lenght+1,10);
    char *word = (char *)malloc(20*sizeof(char));
    //word = (char *)malloc(20*sizeof(char));
    //char s[lenght+1];
     word = "Hello";
    
   morseCode(word);
    

    return 0;
}