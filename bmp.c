#include <stdio.h>
#include <string.h>  // for strlen, strcopy
#include <stdlib.h>  // for malloc
#include <math.h>
#include "bmp.h"
#include "morse.c"
#include "convertions.c"

// Correct values for the header
#define MAGIC_VALUE         0x4D42 
#define NUM_PLANE           1
#define COMPRESSION         0
#define NUM_COLORS          0
#define IMPORTANT_COLORS    0
#define BITS_PER_PIXEL      32
#define BITS_PER_BYTE       8

BMPImage *read_bmp(FILE *fp, char **error);
bool write_bmp(FILE *fp, BMPImage *image, char **error);
bool check_bmp_header(BMPHeader *bmp_header, FILE *fp);
void free_bmp(BMPImage *image);
long _get_file_size(FILE *fp);
int _get_image_size_bytes(BMPHeader *bmp_header);
int _get_image_row_size_bytes(BMPHeader *bmp_header);
int _get_bytes_per_pixel(BMPHeader  *bmp_header);
int _get_padding(BMPHeader *bmp_header);
int _get_position_x_row(int x, BMPHeader *bmp_header);
bool _check(bool condition, char **error, const char *error_message);
char *_string_duplicate(const char *string);

/*
 * Read a BMP image from an already open file.
 * 
 * - Postcondition: it is the caller's responsibility to free the memory
 *   for the error message and the returned image.
 * 
 * - Return: the image as a BMPImage on the heap.
 */
BMPImage *read_bmp(FILE *fp, char **error)
{    
    BMPImage *image = malloc(sizeof(*image));
    if (!_check(image != NULL, error, "Not enough memory"))
    {
        return NULL;
    }
    // Read header
    rewind(fp);
    int num_read = fread(&image->header, sizeof(image->header), 1, fp);
    if(!_check(num_read == 1, error, "Cannot read header"))
    {
        printf("SALAM1\n");
        return NULL;
    }
    // Check header
    bool is_valid_header = check_bmp_header(&image->header, fp);
    
    image->data = malloc(sizeof(*image->data) * image->header.image_size_bytes);
    if (!_check(image->data != NULL, error, "Not enough memory"))
    {
        printf("SALAM3\n");
        return NULL;
    }
    // Read image data
    num_read = fread(image->data, image->header.image_size_bytes, 1, fp);
    if (!_check(num_read == 1, error, "Cannot read image"))
    {
        printf("SALAM4\n");
        return NULL;
    }
    
    return image;
}

/*
 * Write an image to an already open file.
 * 
 * - Postcondition: it is the caller's responsibility to free the memory
 *   for the error message.
 * - Return: true if and only if the operation succeeded.
 */
bool write_bmp(FILE *fp, BMPImage *image, char **error)
{
    // Write header
    rewind(fp);
    int num_read = fwrite(&image->header, sizeof(image->header), 1, fp);
    if (!_check(num_read == 1, error, "Cannot write image"))
    {
        return false;
    }
    // Write image data
    num_read = fwrite(image->data, image->header.image_size_bytes, 1, fp);
    if (!_check(num_read == 1, error, "Cannot write image"))
    {
        return false;
    }

    return true;
}

/*
 * Test if the BMPHeader is consistent with itself and the already open image file.
 * 
 * Return: true if and only if the given BMPHeader is valid.
 */
bool check_bmp_header(BMPHeader* bmp_header, FILE* fp)
{
    /*
    A header is valid if:
    1. its magic number is 0x4d42,
    2. image data begins immediately after the header data (header->offset == BMP HEADER SIZE),
    3. the DIB header is the correct size (DIB_HEADER_SIZE),
    4. there is only one image plane,
    5. there is no compression (header->compression == 0),
    6. num_colors and  important_colors are both 0,
    7. the image has 24 bits per pixel,
    8. the size and image_size_bytes fields are correct in relation to the bits,
       width, and height fields and in relation to the file size.
    */
    return
        bmp_header->type == MAGIC_VALUE
        && bmp_header->offset == BMP_HEADER_SIZE
        && bmp_header->dib_header_size == DIB_HEADER_SIZE
        && bmp_header->num_planes == NUM_PLANE
        && bmp_header->compression == COMPRESSION
        && bmp_header->num_colors == NUM_COLORS && bmp_header->important_colors == IMPORTANT_COLORS
        && bmp_header->bits_per_pixel == BITS_PER_PIXEL
        && bmp_header->size == _get_file_size(fp) && bmp_header->image_size_bytes == _get_image_size_bytes(bmp_header);
}

/*
 * Free all memory referred to by the given BMPImage.
 */
void free_bmp(BMPImage *image)
{
    free(image->data);
    free(image);
}




/* 
 * Return the size of the file.
 */
long _get_file_size(FILE *fp)
{   
    // Get current file position
    long current_position = ftell(fp);
    if (current_position == -1)
    {
        return -1;
    }
    // Set file position to the end
    if (fseek(fp, 0, SEEK_END) != 0)
    {
        return -2;
    }
    // Get current file position (now at the end)
    long file_size = ftell(fp);
    if (file_size == -1)
    {
        return -3;
    }
    // Restore previous file position
    if (fseek(fp, current_position, SEEK_SET) != 0)
    {
        return -4;
    }

    return file_size;
}

/* 
 * Return the size of the image in bytes.
 */
int _get_image_size_bytes(BMPHeader *bmp_header)
{
    return _get_image_row_size_bytes(bmp_header) * bmp_header->height_px;
}

/* 
 * Return the size of an image row in bytes.
 *  
 * - Precondition: the header must have the width of the image in pixels.
 */
int _get_image_row_size_bytes(BMPHeader *bmp_header)
{
    int bytes_per_row_without_padding = bmp_header->width_px * _get_bytes_per_pixel(bmp_header);
    return bytes_per_row_without_padding + _get_padding(bmp_header);
}

/*
 * Return size of padding in bytes.
 */ 
int _get_padding(BMPHeader *bmp_header)
{
    return (4 - (bmp_header->width_px * _get_bytes_per_pixel(bmp_header)) % 4) % 4;
}

/* 
 * Return the number of bytes per pixel.
 *  
 * Precondition:
 *     - the header must have the number of bits per pixel.
 */
int _get_bytes_per_pixel(BMPHeader  *bmp_header)
{
    return bmp_header->bits_per_pixel / BITS_PER_BYTE;
}

/*
 * Return the position of the pixel x from the beginning of a row.
 */ 
int _get_position_x_row(int x, BMPHeader *bmp_header)
{
    return x * _get_bytes_per_pixel(bmp_header);
}

/*
 * Check condition and set error message.
 */
bool _check(bool condition, char **error, const char *error_message)
{
    bool is_valid = true;
    if(!condition)
    {
        is_valid = false;
        if (*error == NULL)  // to avoid memory leaks
        {
            *error = _string_duplicate(error_message);
        }
    }    
    return is_valid;
}

/*
 * Make a copy of a string on the heap.
 * 
 * - Postcondition: the caller is responsible to free
 *   the memory for the string.
 */ 
char *_string_duplicate(const char *string)
{
    char *copy = malloc(sizeof(*copy) * (strlen(string) + 1));
    if (copy == NULL)
    {
        return "Not enough memory for error message";
    }
    strcpy(copy, string);

    return copy;
}


unsigned char * write_morse(unsigned char * morse, int padding, unsigned char *new_reg, unsigned char * color_convert){
int new_index = 0;
	for (; *morse != '\0'; morse++)
	{
		switch (*morse)
		{
			case '.':
			new_index = new_index + padding * 2;
				for (int i = 0; i < 6; ++i){
					new_reg[new_index + i]= color_convert[i];
				}
                //6 + padding * 2 skips a background pixel
				new_index = new_index + (6 + padding) * 2;
				break;
			case '-':
				for (int i = 0; i < 3; ++i)
				{
					new_index += padding * 2;
					for (int j = 0; j < 6; ++j)
					{
						new_reg[new_index + j] = color_convert[j];
					}
					new_index += 6;
				}
				new_index += 6 + (padding * 2); 
				break;
			case ' ':
                //Skip 2 more pixels
				new_index += (6 + (padding * 2)) * 2;
				break;
			case '\n':
                //Skip 5 more pixels
				new_index += (6 + (padding * 2)) * 4;
				break;
			default: break;
		}
	}

    return new_reg;
}



unsigned char * watermark(unsigned char * image, BMPHeader header, unsigned char * color, int x_pos, int y_pos, char * text)
{
	int padding,width,index;
    unsigned char * color_convert;
    unsigned char * morse = (unsigned char *)malloc(15 * strlen(text) * sizeof(char));
	
    int _number_byte = header.bits_per_pixel / 8;

    //If the number of pixels is not multiple of 4, there is padding with the values 0
	if( _number_byte != 4) 	padding = 0; 
	else    padding = 1; //else padding is 1

    if(((header.width_px * _number_byte) % 4) != 0) width = header.width_px * _number_byte + (4 - (header.width_px * _number_byte) % 4);
	else width = header.width_px * _number_byte;

    //Convert color to little endian
    color_convert = HexToLittleEndian(color); 

    //Get index of pixel on x_pos, y_pos
    index = (header.height_px - y_pos - 1) * width + x_pos * _number_byte + header.dib_header_size; 
    
	//Convert to morse code
	morse = morseCode(strlwr(text)); 

	int size =  15 * strlen(morse); 

    //Store values of image that will change
	unsigned char * new = (unsigned char *)malloc(size * sizeof(char));
	for (int i = 0; i < size; ++i){
		new[i] = image[index + i]; //fills new with the values of the image
	}

    //Create new_reg to store string value of new
	unsigned char * new_reg = (unsigned char *)malloc(2 * size * sizeof(char));     
	string2hexString(new, new_reg, size); 

    new_reg = write_morse(morse, padding, new_reg, color_convert);

    //Convert value of new_reg to hexadecimal string and store it in new 
	new = stringToHex(new_reg); 

    //Change current pixels with modified pixels
	for (int i = 0; i < size; ++i){
		image[index + i] = new[i];
	}
	return image;
}
