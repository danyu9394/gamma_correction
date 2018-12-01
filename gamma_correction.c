/****************************************************************************
  This sample is released as public domain.  It is distributed in the hope it
  will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
  This is the sample code of applying gamma correction to a raw image in the 
  format of YUV422 16-bit.The image capture is based on monochrome camera. 

  Author: Danyu Li
  Date: 11/30/18 
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/****************************************************************************
**                     Global data * function declaration
*****************************************************************************/
//default testing resolution and raw image
#define IMAGE_WIDTH 1280 
#define IMAGE_HEIGHT 720
#define FILE_NAME_IN "1mm_1.raw"
#define FILE_NAME_OUT "gamma_corrected.raw"

//TODO:adjust gamma correction value to fit need
double gamma_val = 1/2.2;

void gamma_correction_filter(unsigned short *img_in, unsigned short *img_out,
                                int image_height, int image_width);
/*****************************************************************************
**                           Function definition
*****************************************************************************/
void gamma_correction_filter(unsigned short *img_in, unsigned short *img_out,
                                int image_height, int image_width)
{
    unsigned short tmp;
    unsigned char illuminance;
    double illuminance_tmp, illumiance_gamma;

    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            tmp = img_in[i*image_width + j];
            illuminance = (tmp) & 0xff;
            illuminance_tmp = (double)illuminance/256;
            illumiance_gamma = pow(illuminance_tmp, gamma_val);
            illumiance_gamma = illumiance_gamma * 256;
            illuminance = (unsigned char)illumiance_gamma; 
            tmp = ((0x80 <<8)|illuminance);
            img_out[i*image_width+j] = tmp; 
            
        }
    }


}

int main(int argc, char *argv[])
{
    int image_width;
    int image_height;
    char file_in[30] = FILE_NAME_IN;
    char file_out[30] = FILE_NAME_OUT;
    FILE *fp, *fp_out;
    unsigned short *img;
    unsigned short *img_out;
    int ret;

    image_height = IMAGE_HEIGHT;
    image_width = IMAGE_WIDTH;

    //parse options to change resolution
    if (argc > 1)
        strcpy(file_in, argv[1]);
    if (argc > 2)
        image_width = atoi(argv[2]);
    if (argc > 3)
        image_height = atoi(argv[3]);
        
    printf("usage: gamma_correction [image file name] \
        [image width] [image height]\r\n");
    

    //image file in
    fp = fopen(file_in, "rb");
    if (fp == NULL) 
    {
        printf("File not exist\r\n");
        exit(1);
    }

    img = (unsigned short *)malloc(image_width*image_height* \
                sizeof(unsigned short));
    img_out = (unsigned short *)calloc(image_width*image_height,
                sizeof(unsigned short));

    if (img == NULL) 
    {
        printf("malloc error for size = %ld\r\n", 
            image_height*image_width*sizeof(unsigned short));
        exit(2);
    }

    if (img_out == NULL) 
    {
        printf("malloc error for size = %ld\r\n", 
            image_height*image_width*sizeof(unsigned short));
        exit(2);
    }

    ret = fread(img, sizeof(unsigned short), image_width * image_height, fp);
    if (ret != image_width * image_height)
    {
        printf("file resolution not matched as defined\r\n");

    }
    fclose(fp);

    fp_out = fopen(file_out, "wb");
    if (fp_out == NULL) 
    {
        printf("new image file open error\r\n");
        exit(1);
    }

    gamma_correction_filter(img, img_out, image_height, image_width);

    fwrite(img_out, sizeof(unsigned short), image_height*image_width, fp_out);

    fclose(fp_out);

    free(img);
    free(img_out);
    
    return 0;
}

