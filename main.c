#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "bmp.h"

int main(int argc, char* argv[])
{BMP_Image *check;
  if(argc != 3){ return EXIT_FAILURE;}

  else{ 
   FILE *fptr; fptr = fopen(argv[1],"r"); 
  
  if(fptr == NULL) {return EXIT_FAILURE;} 
   
  else{ 
    fseek(fptr,0,SEEK_END); 
        if(ftell(fptr) == 0) 
           	{fclose(fptr);return EXIT_FAILURE;}
    fseek(fptr,0,SEEK_SET); 
    check = Read_BMP_Image(fptr);  
    fclose(fptr);  

   if(check == NULL) 
   { return EXIT_FAILURE; }
    
    if(check->header.bits == 24){ 
        check = Convert_24_to_16_BMP_Image_with_Dithering(check);}
    else if (check->header.bits == 16){
     check = Convert_16_to_24_BMP_Image(check);}

    else {Free_BMP_Image(check); return EXIT_FAILURE;}

     FILE *dptr = fopen(argv[2],"w"); 
     Write_BMP_Image(dptr, check); 
     Free_BMP_Image(check);
     fclose(dptr);
}


}


return EXIT_SUCCESS;
}
