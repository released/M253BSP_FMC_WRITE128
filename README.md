# M253BSP_FMC_WRITE128
 M253BSP_FMC_WRITE128


update @ 2023/07/06

1. FMC_Write128 need to refer to BSP sample code ( write data in 0x8000 ) 

https://github.com/OpenNuvoton/M253BSP/tree/master/SampleCode/StdDriver/FMC_MultiWordProgram

2. under TRM , when use FMC_Write128 function , need to put FMC file in RAM 

![image](https://github.com/released/M253BSP_FMC_WRITE128/blob/main/TRM_multi_word_programming.jpg)	

3. need to copy scatter file from BSP project 

![image](https://github.com/released/M253BSP_FMC_WRITE128/blob/main/scatter_file.jpg)	

4. modify KEIL option > linker as below 

![image](https://github.com/released/M253BSP_FMC_WRITE128/blob/main/keil_option_linker.jpg)	

5. modif KEIL option > C/CPP(AC6) as below

![image](https://github.com/released/M253BSP_FMC_WRITE128/blob/main/keil_option_c_cpp_ac6.jpg)	

6. use ICP tool , to check APROM data in 0x8000


