#include <stdlib.h>
#include <stdio.h>

#include "bmp.h"

/* check whether a header is valid
 * assume that header has been read from fptr
 * the position of the indicator of fptr is not certain
 * could be at the beginning of the file, end of the file or 
 * anywhere in the file
 * note that the check is only for this exercise/assignment
 * in general, the format is more complicated
 */

	int
Is_BMP_Header_Valid (BMP_Header * header, FILE * fptr)
{
	// Make sure this is a BMP file
	if (header->type != 0x4d42)
	{
		return FALSE;
	}
	// skip the two unused reserved fields

	// check the offset from beginning of file to image data
	// essentially the size of the BMP header
	// BMP_HEADER_SIZE for this exercise/assignment
	if (header->offset != BMP_HEADER_SIZE)
	{
		return FALSE;
	}

	// check the DIB header size == DIB_HEADER_SIZE
	// For this exercise/assignment
	if (header->DIB_header_size != DIB_HEADER_SIZE)
	{
		return FALSE;
	}

	// Make sure there is only one image plane
	if (header->planes != 1)
	{
		return FALSE;
	}
	// Make sure there is no compression
	if (header->compression != 0)
	{
		return FALSE;
	}

	// skip the test for xresolution, yresolution

	// ncolours and importantcolours should be 0
	if (header->ncolours != 0)
	{
		return FALSE;
	}
	if (header->importantcolours != 0)
	{
		return FALSE;
	}

	// Make sure we are getting 24 bits per pixel
	// or 16 bits per pixel
	// only for this assignment
	if (header->bits != 24 && header->bits != 16)
	{
		return FALSE;
	}

	// fill in extra to check for file size, image size
	// based on bits, width, and height
	if (header->width <= 0)
	{
		return FALSE;
	}
	if (header->height <= 0)
	{
		return FALSE;
	}

	if (header->size <= 0)
	{
		return FALSE;
	}

	if ((header->imagesize = header->size - 54) <= 0  )
	{
		return FALSE;
	}

	if ((header->size = header->imagesize + 54) < 0 )
	{
		return FALSE;
	}

                int wid = header->width;
		int h = header->height;
                int bits = header->bits/8;
		int counter = 0;
		int new = wid;
		if (new % 4 != 0)
		{
			counter = new % 4;
		}

         if(header->width % 2 != 0 && bits == 2){

             int padding = 2;

             if(header->imagesize != (h*(wid*bits + padding)) && bits == 2){

          //  fprintf(stderr,"hello %d * (%d * %d + %d) = %d\n",h, wid, bits, counter, header->imagesize);
           return FALSE;
         }
           }
            //   printf("%d %d %d %d\n",header->imagesize, header->height, header->width, counter); 
       if(header->imagesize != (h*(wid*bits + counter)) && bits == 3){

          //  fprintf(stderr,"hello %d * (%d * %d + %d) = %d\n",h, wid, bits, counter, header->imagesize);
           return FALSE;
         }

      
	




	return TRUE;
}

/* The input argument is the source file pointer. 
 * The function returns an address to a dynamically allocated BMP_Image only 
 * if the file * contains a valid image file 
 * Otherwise, return NULL
 * If the function cannot get the necessary memory to store the image, also 
 * return NULL
 * Any error messages should be printed to stderr
 */
	BMP_Image *
Read_BMP_Image (FILE * fptr)
{

	// go to the beginning of the file
	fseek (fptr, 0, SEEK_SET);
	BMP_Image *bmp_image = NULL;

	//Allocate memory for BMP_Image*;


	//Read the first 54 bytes of the source into the header
	bmp_image = (BMP_Image *) malloc (sizeof (BMP_Image) * 1);
	//printf(" %ld\n",ftell(fptr));
	fread (&(bmp_image->header), sizeof (BMP_Header), 1, fptr);

	if(bmp_image == NULL){free(bmp_image);
		return NULL;}


	// if read successful, check validity of header
	if (bmp_image != NULL)
	{

		int check = Is_BMP_Header_Valid (&(bmp_image->header), fptr);
		if (!check)
		{
			free(bmp_image);
			return NULL;
		}
	}
	// Allocate memory for image data
	// free(bmp_image_header);
	// int tempsize = bmp_image->header.size;
	// printf("File size %d \n",tempsize);

	bmp_image->data = (unsigned char *) malloc (bmp_image->header.imagesize);

	fread ((bmp_image->data), (bmp_image->header.imagesize), 1, fptr);

	//  fprintf(stderr," %d\n",bmp_image->header.bits);
	// read in the image data

	return bmp_image;
}

/* The input arguments are the destination file pointer, BMP_Image *image.
 * The function write the header and image data into the destination file.
 * return TRUE if write is successful
 * FALSE otherwise
 */
	int
Write_BMP_Image (FILE * fptr, BMP_Image * image)
{
	// go to the beginning of the file
	fseek (fptr, 0, SEEK_SET);


	// write header
	fwrite (&(image->header), sizeof (BMP_Header), 1, fptr);
	fwrite ((image->data), (image->header.imagesize), 1, fptr);
	// write image data

	return TRUE;
}

/* The input argument is the BMP_Image pointer. The function frees memory of 
 * the BMP_Image.
 */
	void
Free_BMP_Image (BMP_Image * image)
{

	//free(image->header);
	free(image->data);
	free(image);

}

// Given a BMP_Image, create a new image that is a reflection 
// of the given image
// It could be a horizontal reflection (with the vertical mirror 
// being placed at the center of the image) 
// It could be a vertical reflection (with the horizontal mirror
// being placed at the center of the image)
// It could be a horizontal reflection followed by a vertical
// reflection (or equivalently, a vertical reflection followed by
// horizontal reflection).
// hrefl == 1 implies that a horizontal reflection should take place
// hrefl == 0 implies that a horizontal reflection should not take place
// vrefl == 1 implies that a vertical reflection should take place
// vrefl == 0 implies that a vertical reflection should not take place
	
	

	

	void print_char_in_bits(char number)
	{
		int i;
		unsigned char mask = 1 << (8 - 1);
		for (i = 0; i < 8; i++) {
			// need to form a mask
			// mask = 1;
			// mask <<= (CHAR_SIZE - i - 1);
			int result = mask & number;
			if (result == 0) {
		//		printf("0");
			} else {
		//		printf("1");
			}
			mask >>= 1;
		}
		//printf("\n");  
	}



	BMP_Image *Convert_24_to_16_BMP_Image_with_Dithering(BMP_Image *image)

	{
		int bitsize = image->header.bits / 8;
		// printf("%d\n",bitsize);
		int wid = image->header.width;
		int h = image->header.height;
		int counter = 0;
		int new = wid;
		if (new % 4 != 0)
		{
			counter = new % 4;
		}
		// printf("%d\n",counter);
		int i,j,k;
                int m = 0;
                int count = 0;
		unsigned char  arraynew[image->header.height][image->header.width][bitsize];
 		//short int errorarray[image->header.height][image->header.width][3];
		int ***errorarray = (int***)malloc(h*sizeof(int**));
  //		int i, j;

 		 for (i = 0; i < h; i++) {
  		  // Assign to array[i], not *array[i] (that would dereference an uninitialized pointer)
  		  errorarray[i] = (int**)malloc(wid*sizeof(int*));
   		 for (j = 0; j < wid; j++) {
    		  errorarray[i][j] = (int*)malloc(3*sizeof(int));
    			}
 		 }

                for(i = 0;i<image->header.height;i++)
                for(j = 0;j<image->header.width;j++)
                for(k = 0;k<3;k++)
                    {
                      errorarray[i][j][k] = 0;
                    }


		int checking = -1;
		for(i = 0;i<h;i++)
		{ 
			for(j = 0;j<wid;j++){
				for(k = 0;k<bitsize;k++)
				{
					arraynew[i][j][k] = image->data[count];
					count++;

				}
				
			}       
			count += counter;
		}
		int qerror;
                unsigned char temp1;
               unsigned int sum;
                 //printf("Row Column Bits \n");
                for(i = h-1;i>=0;i--)
                for(j = 0;j<wid;j++){
                for(k = 0;k<bitsize;k++)                                                            
                   {  
                    
                    sum = (unsigned int)arraynew[i][j][k] + (int)(errorarray[i][j][k]/16);
                             if(sum < 0) {sum = 0;}
			if(sum > 255) {sum = 255;}
                  
		     arraynew[i][j][k] = (unsigned char)sum;
                                                             

                     temp1 = ((arraynew[i][j][k]>>3)*255)/31;

                     qerror = arraynew[i][j][k] - temp1;
                     if(j<wid-1){
                     errorarray[i][j+1][k] = errorarray[i][j+1][k] + ((qerror*7)); }
                     if(i>0 && j>=1){
	             errorarray[i-1][j-1][k] = errorarray[i-1][j-1][k] + ((qerror*3));}
                     if(i>0){
                     errorarray[i-1][j][k] = errorarray[i-1][j][k] + ((qerror*5));}
                     if(i>0 && j<wid-1){ 
                     errorarray[i-1][j+1][k] = errorarray[i-1][j+1][k] + ((qerror*1));}
 // printf("%d\n",arraynew[i][j][k]);
                //   }
                   }//printf("\n");
                  }

		for (i = 0; i < h; i++) {
  		  // Assign to array[i], not *array[i] (that would dereference an uninitialized pointer)

   		 for (j = 0; j < wid; j++) {
    		  free(errorarray[i][j]);// = (int*)malloc(3*sizeof(int));
    			}
              		  free(errorarray[i]);// = (int**)malloc(wid*sizeof(int*));
 		 }
                free(errorarray);

              
		BMP_Image *image2 = NULL;
		image2 = (BMP_Image *) malloc (sizeof (BMP_Image) * 1);
		image2->header = image->header;
                int padding = 0;
                if(image2->header.width % 2 != 0){ padding = 2;}
		image2->header.imagesize = (image2->header.height * (image2->header.width * 2 + padding));
		image2->data = (unsigned char *) malloc (image2->header.imagesize);
		unsigned char rednew;
		unsigned char greennew;
		unsigned char bluenew;
		unsigned char firstbyte;
		unsigned char secondbyte;
		unsigned char mask = 0xf8;  //01111100
		count = 0;
		checking = -1;
		for(i = 0;i<h;i++){
			for(j = 0;j<wid;j++){
				for(k = 0;k<bitsize;k++)
				{ 
					if(k == 0){
						rednew = arraynew[i][j][k] & mask;

					}

					else if(k == 1){
						greennew = arraynew[i][j][k] & mask;
					}

					else if(k == 2){
						bluenew = arraynew[i][j][k] & mask;
						bluenew >>= 1;
					}        

				}

				secondbyte  = bluenew | greennew >> 6;
				firstbyte  = greennew <<2 | rednew>>3;
				image2->data[count] = firstbyte; count++;
				image2->data[count] = secondbyte; count++;

			}
                    for(m = 0;m<padding;m++)
			{
				image2->data[count] = 0x00;count++;
			} 
		}
		//printf("count2 value %d\n",count);
		image2->header.bits = 16;
		image2->header.size = image2->header.imagesize + 54;

		Free_BMP_Image (image);
		/*
		   uint16_t type;			// Magic identifier
		   uint32_t size;			// File size in bytes
		   uint16_t reserved1;			// Not used
		   uint16_t reserved2;			// Not used
		   uint32_t offset;			// Offset to image data in bytes from beginning of file (54 bytes)
		   uint32_t DIB_header_size;		// DIB Header size in bytes (40 bytes)
		   int32_t  width;			// Width of the image
		   int32_t  height;			// Height of image
		   uint16_t planes;			// Number of color planes
		   uint16_t bits;			// Bits per pixel
		   uint32_t compression;		// Compression type
		   uint32_t imagesize;			// Image size in bytes
		   int32_t  xresolution;		// Pixels per meter
		   int32_t  yresolution;		// Pixels per meter
		   uint32_t ncolours;			// Number of colors  
		   uint32_t importantcolours;	
		   */
		//printf(" Header values %d %d %d %d %d %d \n",image2->header.type,image2->header.size, image2->header.reserved1, image2->header.reserved2, image2->header.offset, image2->header.DIB_header_size);

		//printf("%d %d %d %d %d %d\n", image2->header.width, image2->header.height, image2->header.planes, image2->header.bits, image2->header.compression, image2->header.imagesize);
		//printf("%d %d %d %d %d\n", image2->header.xresolution, image2->header.yresolution, image2->header.yresolution, image2->header.ncolours, image2->header.importantcolours);



		return image2;

	}

	BMP_Image *Convert_16_to_24_BMP_Image(BMP_Image *image)
	{
		int bitsize = image->header.bits / 8;
		// printf("%d\n",bitsize);
		int wid = image->header.width;
		int h = image->header.height;
		int counter = 0;
		int new = wid;
		if (new % 4 != 0)
		{
			counter = new % 4;
		}
		// printf("%d\n",counter);

		int i,j,k;
		int m = 0;
		int count = 0;
                int padding = 0;
               if(image->header.width % 2 != 0){ padding = 2;}
		char arraynew[image->header.height][image->header.width][bitsize];
		int checking = -1;
		for(i = 0;i<h;i++)
		{ 
			for(j = 0;j<wid;j++){
				for(k = 0;k<bitsize;k++)
				{
					arraynew[i][j][k] = image->data[count];
					count++;
				}
				/* if(checking <= 856800){

				   for(m = 0;m<3;m++){
				//        printf("%d %d %d\n",i,j,m);
				//   print_char_in_bits(arraynew[i][j][m]);        
				}
				checking++;
				}*/
			}       
			count += padding;

		} 
		count = 0;
		BMP_Image *image2 = NULL;
		image2 = (BMP_Image *) malloc (sizeof (BMP_Image) * 1);
		image2->header = image->header;
		image2->header.imagesize = (image2->header.height * (image2->header.width * 3 + counter));

		image2->data = (unsigned char *) malloc (image2->header.imagesize);
		unsigned char rednew;
		unsigned char greennew;
		unsigned char bluenew;
		unsigned char firstbyte;
		unsigned char secondbyte;
		unsigned char mask = 0xf8;  //11111000
		unsigned int blueint;
		unsigned int greenint;
		unsigned int redint;
		count = 0;
		checking = -1;
		for(i = 0;i<h;i++){
			for(j = 0;j<wid;j++){
				for(k = 0;k<bitsize;k++)
				{ 
					if(k == 0){
						firstbyte = arraynew[i][j][k];
					}
					else if(k == 1){
						secondbyte = arraynew[i][j][k];
					}

				}
				bluenew = (secondbyte<<1) & mask;
				greennew = ((secondbyte<<6) | (firstbyte>>2))& mask;
				rednew = firstbyte <<3 & mask;
				blueint = (unsigned int)bluenew>>3;
				greenint = (unsigned int)greennew>>3;
				redint = (unsigned int)rednew>>3;
				//   printf("RED INT %d BLUE IN %d GREEN %d\n",redint, blueint, greenint);
				redint = redint*255/31;
				greenint = greenint*255/31;
				blueint = blueint*255/31;
				bluenew = (unsigned char)blueint;
				greennew = (unsigned char)greenint;
				rednew = (unsigned char)redint;
				//  print_char_in_bits(rednew);         print_char_in_bits(greennew);                print_char_in_bits(bluenew);               
				image2->data[count] = rednew; count++;
				image2->data[count] = greennew; count++;
				image2->data[count] = bluenew; count++;

			}
			//count+=counter;
			for(m = 0;m<counter;m++)
			{
				image2->data[count] = 0x00;count++;
			}
		}
		image2->header = image->header;
		image2->header.bits = 24;
		image2->header.imagesize = (image2->header.height * (image2->header.width * 3 + counter));
		image2->header.size = image2->header.imagesize + 54;
		Free_BMP_Image (image);

		return image2;   
	}

