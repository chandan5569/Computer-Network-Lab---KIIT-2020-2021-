#include<stdio.h>

struct  info
{
  
  int roll;

  char name[100];

  float cgpa;


};

void display(struct info *m2);               /*function prototyping */


int main()
{

struct  info m1;

printf("enter the roll number of the member \n");

scanf("%d",&m1.roll);

printf("enter the name of the member \n");

scanf("%s",&m1.name);

printf("enter the cgpa of the member \n");

scanf("%f",&m1.cgpa);

display(&m1);

}

void display(struct info *m2)

{

printf("Roll number of the member is %d \n",m2->roll);

printf("Name of the member is %s \n",m2->name);

printf("CGPA of the member is %f \n",m2->cgpa);



}