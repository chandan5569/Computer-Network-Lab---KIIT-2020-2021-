
#include<stdio.h>

struct pkt{
    unsigned char ch1;
    unsigned char ch2[2];
    unsigned char ch3;
};


int main(){
    

    unsigned int value=0x11223344;

    int a,b,c,d;

     a=(value&0xFF); 
    b=((value>>8)&0xFF); 
    c=((value>>16)&0xFF); 
    d=((value>>24)&0xFF);

    struct pkt ob1;
    
    ob1.ch1=a;
    ob1.ch2[0]=b;
    ob1.ch2[1]=c;
    ob1.ch3=d;

    printf("char1= %.2x",ob1.ch1);
    printf("\nchar2[0]= %.2x",ob1.ch2[0]);
    printf("\nchar2[1]= %.2x",ob1.ch2[1]);
    printf("\nchar3= %.2x",ob1.ch3);


    int val=((int)(ob1.ch3<<24)+(int)(ob1.ch2[1]<<16)+(int)(ob1.ch2[0]<<8)+(int)(ob1.ch1));
    printf("\n%d",val);


    return 0;
}

