#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#include "bmp.c"

BMPImage *read_image(const char *filename, char **error);
void write_image(const char *filename, BMPImage *image, char **error);
FILE *_open_file(const char *filename, const char *mode);
void _handle_error(char **error, FILE *fp, BMPImage *image);
void _clean_up(FILE *fp, BMPImage *image, char **error);
int * seperate(const char * s);

int main(int argc, char const *argv[]){
    char *error = NULL;
    char * text = (char*)malloc(50*sizeof(char));
    char * date = (char*)malloc(50*sizeof(char));
    char * color= (char*)malloc(50*sizeof(char)); strcpy(color,"FFFFFE"); //Default value of color
    char * out_file=(char*)malloc(10*sizeof(char));
    char * str_x_pos= (char*)malloc(500*sizeof(char));
    char * str_y_pos= (char*)malloc(500*sizeof(char));
    int x_pos = 0;
    int y_pos = 0;


    for(int i=2;i<argc;i++){
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
                // printf("date is NULL\n");
                strcpy(date,getDate());
                printf("date is %s\n",date);
            }
        }else if(!strcmp(argv[i],"-color")){
            if(argv[i+1][0]!='-'){
                strcpy(color,argv[i+1]);
                // color = argv[i+1];
                printf("color is %s\n",color);
            }else{
                printf("color is FFFFFE\n");
                strcpy(color,"FFFFFE");
            }
        }else if(!strcmp(argv[i],"-pos")){
            if(argv[i+1][0]!='-'){
                strcpy(str_x_pos,argv[i+1]);
                strcpy(str_y_pos,argv[i+2]);
                // printf("STR x_pos:  %s\n",str_x_pos);
                x_pos = str_to_int(str_x_pos);
                y_pos = str_to_int(str_y_pos);
                // int * a = (int *)calloc(100,sizeof(int));
                // a = seperate(argv[i+1]);
                // x_pos = a[0]; y_pos = a[1];
                printf("pos is %d %d\n",x_pos,y_pos);
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
    strcat(text," ");
    strcat(text,date);

    
    BMPImage *image = read_image(argv[1], &error);
    
    unsigned char * result = (unsigned char* )malloc((/*921654*/image->header.image_size_bytes + 1) * sizeof(char));
    result = watermark(image->data, image->header, color, x_pos, y_pos, text);
    BMPImage *image2 = malloc(sizeof(*image2));
    image2->data=result;
    image2->header = image->header;
    write_image(out_file, image2, &error);


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


int * seperate(const char * s){
    char * str_x= (char*)calloc(500,sizeof(char));
    char * str_y= (char*)calloc(500,sizeof(char));
    for(int i=0;i<strlen(s);i++){
        if(s[i]==','){
            // strcpy(str_x[i],"\0");
            break;
        }else{
            str_x[i]=s[i];
        }
    }
    int t=0;
    for(int j=0;j<strlen(s);j++){
        if(s[j]==','){
            t=1;
        }else if(t>0){
            str_y[t-1]=s[j];
            t++;
        }
    }
    // printf("Y  %s\n",str_y);
    int * a;
    a[0] = str_to_int(str_x);
    a[1] = str_to_int(str_y);
    return a;
}