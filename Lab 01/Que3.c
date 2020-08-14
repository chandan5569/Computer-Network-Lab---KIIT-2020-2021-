
#include <stdio.h>
  
int main()
{
    unsigned int x=0x11223344;

    int a,b,c,d; 
     
     
    a=(x&0xFF);            /*Masking of the last two digit that is 44 into x using the And opearation with 0xFF. F=1111, F=1111 and 0x is the hexadecimal representation */

    b=((x>>8)&0xFF); 

    c=((x>>16)&0xFF); 


    d=((x>>24)&0xFF); 
 
    printf("a= %02X\n",a);
    printf("b= %02X\n",b);
    printf("c= %02X\n",c);
    printf("d= %02X\n",d);
  
    return 0;
}
