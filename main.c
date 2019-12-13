#include <stdio.h>
#include <stdlib.h>  // for EXIT_SUCCESS and EXIT_FAILURE
#include<string.h>
#include "bmp.c"

BMPImage *read_image(const char *filename, char **error);
void write_image(const char *filename, BMPImage *image, char **error);
FILE *_open_file(const char *filename, const char *mode);
void _handle_error(char **error, FILE *fp, BMPImage *image);
void _clean_up(FILE *fp, BMPImage *image, char **error);


int main(int argc, char const *argv[]){
    char *error = NULL;
    char * text = (char*)malloc(50*sizeof(char));
    char * date = (char*)malloc(50*sizeof(char));
    char * color= (char*)malloc(50*sizeof(char));
    char * out_file=(char*)malloc(10*sizeof(char));
    int x_pos;
    int y_pos;


    for(int i=1;i<argc;i++){
        if(!strcmp(argv[i],"-text")){
            if(argv[i+1][0]!='-'){
                strcpy(text,argv[i+1]);
                printf("text is %s\n",text);
            }else{
                printf("text is NULL\n");
            }
        }else if(!strcmp(argv[i],"-date")){
            if(argv[i+1][0]!='-'){
                strcpy(date,argv[i+1]);
                printf("date is %s\n",date);
            }
            else{
                printf("date is NULL\n");
            }
        }else if(!strcmp(argv[i],"-color")){
            if(argv[i+1][0]!='-'){
                strcpy(color,argv[i+1]);
                // color = argv[i+1];
                printf("color is %s\n",color);
            }else{
                printf("color is NULL\n");
            }
        }else if(!strcmp(argv[i],"-pos")){
            if(argv[i+1][0]!='-'){
                printf("pos is %s %s\n",argv[i+1],argv[i+2]);
            }else{
                printf("pos is 0,0\n");
            }
        }else if(!strcmp(argv[i],"-o")){
            if(argv[i+1][0]!='-'){
                strcpy(out_file,argv[i+1]);
                printf("output file is %s\n",out_file);
            }else{
                printf("output is stdout\n");
            }
        }
    }

    // FILE *input_ptr = _open_file("sign.bmp", "rb");
    // BMPImage *image = read_bmp(input_ptr, &error);
    
    BMPImage *image = read_image("sign.bmp", &error);
    write_image("copy.bmp", image, &error);
    printf("%d,%d\n",image->header.width_px,image->header.height_px);
    // BMPImage *crop_image = crop_bmp(image, 100, 100, 576, 324, &error);
    // write_image("crop1.bmp", crop_image, &error);

    // bool is_valid = check_bmp_header(&crop_image->header, fopen("sign.bmp", "rb"));

    _clean_up(NULL, image, &error);
    // _clean_up(NULL, crop_image, &error);

    // printf("%c\n",argv[1][1]);
















    return EXIT_SUCCESS;
}

BMPImage *read_image(const char *filename, char **error)
{
    FILE *input_ptr = _open_file(filename, "rb");

    BMPImage *image = read_bmp(input_ptr, error);
    if (*error != NULL)
    {
        _handle_error(error, input_ptr, image);
    }
    fclose(input_ptr);

    return image;
}

void write_image(const char *filename, BMPImage *image, char **error)
{
    FILE *output_ptr = _open_file(filename, "wb");

    if (!write_bmp(output_ptr, image, error))
    {
        _handle_error(error, output_ptr, image);
    }    
    fclose(output_ptr);
}

/*
 * Open file. In case of error, print message and exit.
 */
FILE *_open_file(const char *filename, const char *mode)
{
    FILE *fp = fopen(filename, mode);
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open file %s", filename);

        exit(EXIT_FAILURE);
    } 

    return fp;
}

/*
 * Print error message and clean up resources.
 */
void _handle_error(char **error, FILE *fp, BMPImage *image)
{
    fprintf(stderr, "ERROR: %s\n", *error);
    _clean_up(fp, image, error);

    exit(EXIT_FAILURE);
}

/*
 * Close file and release memory.
 */
void _clean_up(FILE *fp, BMPImage *image, char **error)
{
    if (fp != NULL)
    {
        fclose(fp);
    }    
    free_bmp(image);
    free(*error);
}

char * char_to_string(char c){
    char *pChar = malloc(sizeof(char));
    *pChar = c;
    return pChar;
}