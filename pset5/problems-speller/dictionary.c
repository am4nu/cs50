/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include "dictionary.h"


typedef struct node {

char word[LENGTH+1];
struct node* next;
}node;
char buffer[LENGTH+1];
node* ptr,*head,*temp=NULL;
unsigned int si=0;
/**
 * Returns true if word is in dictionary else false.
 */

void printL(void)
{

}
bool cmpI (const char *s1,const char *s2)
{
    int i=0;
    for(i=0; s2[i]!='\0'; i++)
    {
        if( (s1[i])!=tolower(s2[i]) )
            return true;           
    }
    if(s1[i]=='\0')return false;
    else return true;
}
bool check(const char *word)
{
	temp=head;
while(temp!=NULL)
    {
   if (!cmpI(temp->word,word))
   return true;
    temp=temp->next;
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
int i=0;
 FILE *filePtr=fopen(dictionary,"r");
 char temp='\0';
 while (temp!=EOF)
    {
	temp=fgetc(filePtr);
	
	 if(temp=='\n') {
		buffer[i]='\0';
		node* temp=malloc(sizeof(node));
		strcpy(temp->word,buffer);
		if(head==NULL)
			{
			 head=temp;ptr=temp;
			}
		else  { ptr->next=temp;
				   ptr=ptr->next;
			       ptr->next=NULL;
			}
		i=0;
		si++;
		
	}
	else{ 
		buffer[i]=temp; 
		i++;}

    }
    fclose(filePtr);
    return true;

}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
unsigned int i=si;
    return i;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
 
    node* current = head;
    node* next;
 
  for(unsigned int count=0;count<si;count++)
   {
       next = current->next;
       free(current);
       current = next;
   }
   
   return true;
}
