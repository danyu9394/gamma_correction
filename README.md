# gamma correction 
  This is the sample code of applying gamma correction to a raw image & generate filter pattern 
  for FPGA ROM in the format of YUV422 16-bit.The image capture is based on monochrome camera. 

##test environment 
- kernel: 4.15.0-34-generic
- distro version: Ubuntu 16.04.5 LTS

## gamma correction raw image
### how to run
```
## clean up the code
make clean 
## compile the code
make
##run the code 
gamma_correction [raw image name] [width] [height]
## e.g. gamma_correction 1m_1.raw 1280 720
```

##gamma_correction_fpga
### how to run
```
## compile the code
gcc gamma.c -lm
## run the code
./a.out
```