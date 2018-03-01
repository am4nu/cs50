#include<stdio.h>
#include<cs50.h>

int main()

{

 int var=-1;
printf("Enter number of minutes:\n");
var=GetInt();
if(var==1)
printf("%d minute equals %d bottle",var,var*12);
else
printf("%d minutes equals %d bottles",var,var*12);

return 0;




}
