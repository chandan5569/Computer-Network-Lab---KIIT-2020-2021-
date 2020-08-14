#include<stdio.h>

void swap(int *a, int *b);

int main()
{

int x,y;

printf("enter the two numbers you want to swap");

scanf("%d%d",&x,&y);

swap(&x,&y);

printf("After swapping the two numbers are \n");

printf("x = %d,y = %d",x,y);

}

void swap(int *a,int *b)
{

int temp;

temp = *a;

*a = *b;

*b=temp;


}