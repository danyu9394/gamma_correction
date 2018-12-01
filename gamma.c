#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//	gamma correction data remapping
//	input 12-bit raw data, output 8-bit data put in YUV422 Y(8bit)
//	2^12=4096, 2^8 = 256


//compile: gcc gamma -lm
int main()
{
    double x,y;
    double gamma = 1/2.2;// gamma value [1,2.2] usually
    FILE *fp1, *fp2;

    fp1 = fopen("gamma_rom_2_2_hex.mem","w"); //for fpga
    fp2 = fopen("gamma_rom_2_2_dec.mem","w"); //for plotting
  
    for (int i=0; i<4096; i++)
    {
        x = (double)i / 4096;
        y = pow(x, gamma);
        y = y * 255;
        fprintf(fp1, "%2x\r\n", (int)y);
        fprintf(fp2, "%d\r\n", (int)y);
    }

    fclose(fp1);
    fclose(fp2);
}
