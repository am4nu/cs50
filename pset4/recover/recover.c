#include<cs50.h>
#include<stdio.h>
#include<stdlib.h>
int check(unsigned char* buffer)
{
	if( buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff &&  (buffer[3]&0xf0)==0xe0)
	return 1;
	else return 0;
}

int main(int argc, char *argv[])
{
int countImage=0;
int flagfound=0;
char filename[8];

 if (argc != 2){
        fprintf(stderr, "Type the name of sdcard dump file");
        return 1;
    }
 FILE *sdCardptr = fopen(argv[1], "r");// file is opened the pointer has *file has the address
    if (sdCardptr == NULL)
    {
        fprintf(stderr, "Can't open file %s, Either it doesn't exist or it has different name",argv[1]);
        return 2;
    }
FILE* imgFile=NULL;
unsigned char buffer[512];
 while (fread(buffer,512,1,sdCardptr)==1)
{
if(flagfound==0){
	if(check(buffer)){
		flagfound=1;
		sprintf(filename,"%03d.jpg",countImage);
		imgFile=fopen(filename,"a");
		 fwrite(buffer,512,1,imgFile);
		 countImage++;
		 }
	if(!check(buffer))continue;
	}
else if(flagfound==1){
		if(!check(buffer))
			fwrite(buffer,512,1,imgFile);
	if(check(buffer)){
		fclose(imgFile); 
		sprintf(filename,"%03d.jpg",countImage);
		imgFile=fopen(filename,"a");
		fwrite(buffer,512,1,imgFile);
		countImage++;  //open new one and close the old one
		}
	}	
}
fclose(imgFile);
fclose(sdCardptr);
return 0;
}

