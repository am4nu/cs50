/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy n infile outfile\n");
        return 1;
    }

    // remember filenames
    double n=atof(argv[1]);
    if (n<0.0 || n>=100.0)
    {
		
		return 1;
	}
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
        // determine new padding for scanlines
       int tempW=bi.biWidth;
     int   tempH=bi.biHeight;
      bi.biWidth=n*tempW;
      bi.biHeight=n*tempH;
       int padding0= (4 - (tempW* sizeof(RGBTRIPLE)) % 4) % 4;
	int padding = (4 - (bi.biWidth* sizeof(RGBTRIPLE)) % 4) % 4;
	bi.biSizeImage=((sizeof(RGBTRIPLE)*bi.biWidth)+padding)*abs(bi.biHeight);
	bf.bfSize=bi.biSizeImage+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);



int N=(int)n;
RGBTRIPLE arL[1000];
    // iterate over infile's scanlines
  
    for (int i = 0, total = abs(tempH)*tempW; i < total; i++)
    {
		
	
        // iterate over pixels
   
   int     j;
            // temporary storage
            RGBTRIPLE triple;
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // write RGB triple to outfile
            for(int m=0;m<N;m++){
			fwrite(&triple, sizeof(RGBTRIPLE), 1,outptr);
			arL[j].rgbtBlue=triple.rgbtBlue;
            arL[j].rgbtRed=triple.rgbtRed;
            arL[j].rgbtGreen=triple.rgbtGreen;
            j++;}

        if((i+1)%(tempW)==0){
				
			
        // skip over padding, if any
        fseek(inptr, padding0, SEEK_CUR);
        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
        for(int count=1;count<N;count++){
        fwrite(arL, sizeof(RGBTRIPLE)*tempW*N, 1,outptr);
            for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
	}
        j=0;
	}
	
}
	

        
        
  //end
	
    


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
