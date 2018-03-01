#include<stdio.h>
#include<cs50.h>
#include<math.h>
#define  lld long long int
int main()
{
int var=0,count=0;
float f=0;


printf("Hola\n");

f=get_float();
while(f<0.00999){
    
    printf("retry:");scanf("%f",&f);
    
}



var=round(f*100); 
if(var>=25)
{	count=count+var/25;
	var=var%25;
}
if(var>=10){
	
count=count+var/10;
var=var%10;
}
if(var>=5){
count=count+var/5;
var=var%5;
}
if(var>0){count=count+var; var=0;}
printf("%d\n",count);
return 0;
}
