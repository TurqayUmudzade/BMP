#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//converts hexadecimal to Little Endian
char *HexToLittleEndian(char hex[])
{
    int hexsize = strlen(hex);
    char *lil = malloc ((sizeof (char) * hexsize)+1);
    

    for (int i = 1; i < hexsize; i = i + 2)
    {
        lil[i - 1] = hex[hexsize - 1 - i];
        lil[i] = hex[hexsize - i];
    }

    return lil;
}

//Converts Hexadecimal to decimal
int hexadecimalToDecimal(char hexVal[])
{
    int len = strlen(hexVal);

    // Initializing base value to 1, i.e 16^0
    int base = 1;

    int dec_val = 0;

    // Extracting characters as digits from last character
    for (int i = len - 1; i >= 0; i--)
    {
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value.
        if (hexVal[i] >= '0' && hexVal[i] <= '9')
        {
            dec_val += (hexVal[i] - 48) * base;

            // incrementing base by power
            base = base * 16;
        }

        // if character lies in 'A'-'F' , converting
        // it to integral 10 - 15 by subtracting 55
        // from ASCII value
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F')
        {
            dec_val += (hexVal[i] - 55) * base;

            // incrementing base by power
            base = base * 16;
        }
    }

    return dec_val;
}


//for 4 bytes the size of file
int HexToLittleEndianToDecimal(char hex[])
{
    return hexadecimalToDecimal(HexToLittleEndian(hex));
}

//function to convert ascii char[] to hex-string (char[])
void string2hexString(unsigned char* input,unsigned char* output, int size)
{
    int i = 0; 
      
    for (int loop = 0; loop < size; loop++)
    {
        sprintf((output + i), "%02X", input[loop]);
        i += 2;
    }
    //insert NULL at the end of the output string
    output[i++] = '\0';
}



unsigned char * stringToHex(unsigned char * string){
	unsigned char * result = (unsigned char *)malloc((strlen(string) / 2 + 1) * sizeof(char));
	unsigned char * new = (unsigned char *)malloc(10 * sizeof(char));
	int n, k = 0;
	for (int i = 0; i < strlen(string); i += 2)
	{
		new[0] = string[i];
		new[1] = string[i + 1];
        n = hexadecimalToDecimal(new);
		result[k] = (unsigned char)n;
		k++;
	}
	result[k] = '\0';
	return result;
}

char * char_to_string(char c){
    char *pChar = malloc(sizeof(char));
    *pChar = c;
    return pChar;
}

int str_to_int(char* str){
    int result = 0, coeff = 1;
    for (int i = 0; i < strlen(str); i++){
        if(i == 0 && str[i] == '-'){
            coeff = -1;
            continue;
        }
        result*=10;
        result+=str[i] - '0';
    }
    return result*coeff;
}

