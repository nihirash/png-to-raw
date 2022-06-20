/**
 * Png to raw rgb converter(big-endian)
 * 
 * Used lodepng by Lode Vandevenne
 * 
 * My parts of code are unlicensed - do what you like with this part of code
 **/
#include "lodepng.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    RGB888,
    RGBA8888,
    RGB565,
    RGBA555
} Mode;

void store565(FILE* f, char R, char G, char B, unsigned char A) {
    unsigned char r = (R >> 3) & 0x1f;
    unsigned char g = (G >> 2) & 0x3f;
    unsigned char b = (B >> 3) & 0x1f;
    unsigned word = (r)  | (g << 5) | (b << 11);
    fputc((word >> 8 & 0xff), f);
    fputc((word & 0xff), f);
}


void store555(FILE* f, char R, char G, char B, unsigned char A) {
    unsigned char r = (R >> 3) & 0x1f;
    unsigned char g = (G >> 3) & 0x1f;
    unsigned char b = (B >> 3) & 0x1f;
    unsigned char a = (A > 127) ? 0 : 1;
    unsigned word = a << 15 | (r)  | (g << 5) | (b << 10);
    fputc((word >> 8 & 0xff), f);
    fputc((word & 0xff), f);
}

void store888(FILE* f, char R, char G, char B, unsigned char A) {
    fputc(B, f);
    fputc(G, f);
    fputc(R, f);
}

void storeA888(FILE *f, char R, char G, char B, unsigned char A) {
    fputc(A, f);
    fputc(B, f);
    fputc(G, f);
    fputc(R, f);
}

void convert_png(char *filename, char *output_filename, Mode mode) {
    unsigned error;
    unsigned char *image ;
    unsigned width, height;
    unsigned char* png = 0;
    size_t pngsize;
    
    error = lodepng_load_file(&png, &pngsize, filename);
    if(!error) error = lodepng_decode32(&image, &width, &height, png, pngsize);
    if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

    if(!error) {
        printf("Image width: %u height: %u\n", width, height);

        FILE* f = fopen(output_filename, "wb");
        if (f) {
            for (size_t offset=0;offset<(width*height);offset++) {
                unsigned char B = image[offset*4];
                unsigned char G = image[offset*4 + 1];
                unsigned char R = image[offset*4 + 2];
                unsigned char A = image[offset*4 + 3];

                switch(mode) {
                    case RGB565:
                        store565(f, R, G, B, A);
                        break;
                    case RGBA555:
                        store555(f, R, G, B, A);
                        break;
                    case RGB888:
                        store888(f, R, G, B, A);
                        break;
                    case RGBA8888:
                        storeA888(f, R, G, B, A);
                        break;
                    default:
                }

            }
        fclose (f);
        } else {
            printf("ERROR! Can't create file!\n");
        }
    }

    free(png);

    free(image);
}

int main(int argc, char **args) {
    printf("PNG to SAGA raw chunks converter by Nihirash\n");
    printf("v.1.0 21 Jun 2022\n");
    if (argc < 4) {
        printf("usage: %s MODE input.png output.raw\n", args[0]);
        printf(" Where MODE is:\n");
        printf("  * 888 - RGB888\n  * A888 - ARGB888\n  * 565 - RGB565\n  * 555 - RGBA555\n");
        
        return 1;
    } 
    
    Mode m = RGBA8888;
         if (strcmp("888",  args[1])==0) m = RGB888;
    else if (strcmp("A888", args[1])==0) m = RGBA8888;
    else if (strcmp("565",  args[1])==0) m = RGB565;
    else if (strcmp("555",  args[1])==0) m = RGBA555;
    else {
        printf("Wrong mode selected!\n");
        
        return 1;
    }
    
    convert_png(args[2], args[3], m);

    return 0;
}