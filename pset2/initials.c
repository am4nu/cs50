#include<cs50.h>
#include<stdio.h>
#define buffer 1000


void toupp(string x,int i)
{
   
    int j=0;
    while(j<=i)
    {
        if(x[j]>=97&&x[j]<=122)//Checking for lower case char
          x[j]=x[j]-32;//converting to uppercase
          j++; 
        
    }
}
int main()
{
    string str,str2;
    int i=0,j=0;
    str2=malloc(buffer);
    
    str=GetString();
    
    while(str[i]!='\0')
    {
      if(i==0) 
      { 
      str2[j]=str[i];
      j++;
     // if(str2[j]>=97&&str2[j]<=122)//Checking for lower case char
      //str2[j]=str2[j]-32;j++;//converting to uppercase
      
      }
      
      if(str[i]==' ')
      {
          str2[j]=str[i+1];
          j++;
         // if(str2[j]>=97&&str2[j]<=122)//Checking for lower case char
          //str2[j]=str2[j]-32;j++;//converting to uppercase
          
      }
        i++;
        
    }
    toupp(str2,j);
    puts(str2);
    return 0;
}