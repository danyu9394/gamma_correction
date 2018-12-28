#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//  generate the look up table to put inside FPGA ROM
//  specify the input data stream lane # to put in ROM input address depth
//  specify the output data stream lane # to put in ROM output address width	
//  gamma correction data remapping and black level correction

double gamma_val = 1.0/3.5;

#define DEFAULT_DEPTH 1024
#define DEFAULT_WIDTH_LEVEL 1023

#define BLACK_LEVEL_CORRECTION 0


//compile: gcc gamma -lm
int main(int argc, char *argv[])
{
    double x,y;
    int addr_depth;
    int addr_width;
    unsigned int black_level_correction = 0;
    char output_file_name[256];
    FILE *fp1, *fp2;

    addr_depth = DEFAULT_DEPTH;
    addr_width = DEFAULT_WIDTH_LEVEL;

    if (argc > 1) 
    {
        gamma_val = atof(argv[1]);
        gamma_val = 1.0/gamma_val;
    }
    if (argc > 2) 
    {
        addr_depth = atoi(argv[2]);
        addr_depth = pow(2, addr_depth);
    }
    if (argc > 3)
    {   
        addr_width = atoi(argv[3]);
        addr_width = pow(2,addr_width) - 1;    
    }
    if (argc > 4)
    {   
        black_level_correction = abs(atoi(argv[4]));

    }
    printf("usage: gamma_rom [gamma_correction_val] [input data stream lane #]\
    [output data stream lane #] [black level correction]\r\n");
    
    if (argc < 5) 
    {
        printf("error: missing arguments, will use default values\r\n");
        sprintf(output_file_name, "gamma_%i_depth_%i_width_%i_black_%i.mem", 
            2, 8, 8, BLACK_LEVEL_CORRECTION);
    } 
    else 
    {
        printf("gamma_val = %9.6f\r\n", gamma_val);
        printf("addr width level = %d\r\n", addr_width);
        printf("addr depth val = %d\r\n", addr_depth);

        //cancatenate the argument to output file name
        sprintf(output_file_name, "gamma_%s_depth_%s_width_%s_black_%s.mem", 
            argv[1], argv[2], argv[3], argv[4]);
    }
    printf("output file %s\r\n",output_file_name);


    fp1 = fopen(output_file_name,"w"); //for fpga
    fp2 = fopen("plottinng_data.txt","w"); //for plotting
  
    for (int i=0; i< addr_depth; i++)
    {
        x = (double)i /addr_depth;
        y = pow(x, gamma_val);
        y = y * addr_width;
        if (y > black_level_correction) 
            y = y - black_level_correction;
        else 
            y = 0;
        fprintf(fp1, "%2x\r\n", (int)y);
        fprintf(fp2, "%d\r\n", (int)y);
    }

    fclose(fp1);
    fclose(fp2);
}
