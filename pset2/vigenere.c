#include<cs50.h>
#include<string.h>
#include<stdio.h>
#include<math.h>

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
        return 1;
    }
    
    int i=0,j=0,tmp,keylen,err=0;
  
    string str,str2,key;
    key=malloc(strlen(command[1])+1);
    strcpy(key,command[1]);
    keylen=strlen(key);
   
    
    //puts(key);
    while(key[i]!='\0')
    {
        
        if(key[i]>=97&&key[i]<=122)
        key[i]=key[i]-97;
        else if(key[i]>=65&&key[i]<=90)
        key[i]=key[i]-65;
        else err=1;
        i++;
        
    }
    if(err==1){
    printf("error in key word");
    return 1;
    }
  //printf("%d %d %d",key[0],key[1],key[2]);
   
    str=GetString();
    str2=malloc(strlen(str)+2);
    i=0;
    j=0;
    while(str[i]!='\0')
    {
        
        if(str[i]>=97&&str[i]<=122)
        {
            
        tmp=str[i]-97;
        tmp=tmp+key[j];
        tmp=tmp%26;
       tmp=tmp+97;
       str2[i]=tmp;
       j++;
        
        }
     else  if(str[i]>=65&&str[i]<=90)
       {  
        
        tmp=str[i]-65;
        tmp=tmp+key[j];
        tmp=tmp%26;
        tmp=tmp+65;
       str2[i]=tmp;
       j++;
        
        }
      else str2[i]=str[i];
      
      
     i++;
    
    j=j%keylen;
    
    
    }
            
puts(str2);
    
    return 0;
}