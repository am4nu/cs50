/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       //#include<stdio.h>
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int a[], int n)
{  // int i;
    int mid;
    int left=0;
    int right=n;
   while(left<=right) {
       // printf("i am here\n");
        mid=(left+right)/2;
     if(value==a[mid])
    {
        
        return true;
    }
    
    else if(value>a[mid]){
        left=mid+1;
    }
    else if(value<a[mid]){
       
        right=mid-1;
    }
  
    }
    return false;
}


/**
 * Sorts array of n values.
 */
void sort(int a[], int n)
{
    
int i,j,temp;
for(j=0;j<n;j++)
for(i=j+1;i<n;i++)
if(a[j]>a[i])
{
temp=a[j];
a[j]=a[i];
a[i]=temp;
}

    return;
}
