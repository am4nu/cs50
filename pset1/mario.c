#include<stdio.h>
#include<cs50.h>
#include<math.h>
#define  lld long long int
int main()

{ 	
	int on=0,n;
	int space,i;
	int curspace;
	

	
	
	do{
	printf("height: ");
	n=get_int();
	}while(n<0 || n>23);

	
	
	
	space=n-1;
	curspace=space;
	for(i=1;i<=n*(n+2);i++)
	{
	
		if(curspace==0)
			on=1;
		else on=0;
		
		if(on==0)
		   {
			printf(" ");
			curspace--;
			}
		
		else if(i%(n+2)==0)
		{
			printf("\n");on=0;
			space--;
			curspace=space;
		}
		else 
		printf("#");
	}
	return 0;
}
