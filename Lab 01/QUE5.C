

#include<stdio.h>

void printing(unsigned char *val,int n){
    int k;
    for(k=0;k<n;k++){
        printf("%.2x  ",val[k]);
    }
    if(val[0]=44){
        printf("\nLittle Endian");
    }
    else
        printf("\nBig Endian");
    
    printf("\n");
    printf("\nLittle Endian\n");
    for(k=0;k<n;k++){
        printf("%.2x  ",val[k]);
    }
    printf("\nBig Endian\n");
    for(k=n-1;k>-1;k--){
        printf("%.2x  ",val[k]);
    }
}

int main()
{
    int i=12578329;
    printing((unsigned char*)&i,sizeof(i));  
    return(0);
} 

