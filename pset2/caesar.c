#include<cs50.h>
#include<string.h>
#include<stdio.h>
#include<math.h>
int useratoi(string x)
{
    int key,i,j;
    for(j=0,i=strlen(x)-1;i>=0;i--,j++)
  key=key + pow(10,j)*(x[i]-48);
  
  return key;
}
int main(int y,string command[])

{
    if(y<2)
    {
    printf("no arguments\n");
     return 1;
    }
    if(y>2)
    {
        printf("error\n");
        return 2;
    }
    
    int key,i=0,tmp;
    string instr,str,str2;
    instr=malloc(strlen(command[1])+1);
    strcpy(instr,command[1]);
    key=useratoi(instr);//a user defined function to parse into int
    printf("plaintext: ");
    str=get_string();
    str2=malloc(strlen(str)+1);
    
    while(str[i]!='\0')
    {
       
        if(str[i]>=97&&str[i]<=122)
        
        {
            
       
        tmp=str[i]-97;
        tmp=tmp+key;
        tmp=tmp%26;
       tmp=tmp+97;
       str2[i]=tmp;
        
        }
     else  if(str[i]>=65&&str[i]<=90)
       {  
        
        tmp=str[i]-65;
        tmp=tmp+key;
        tmp=tmp%26;
        tmp=tmp+65;
       str2[i]=tmp;
        
        }
      else str2[i]=str[i];
      
      
     i++;
    
    }
 printf("ciphertext: %s\n",str2);          

    
    return 0;
}