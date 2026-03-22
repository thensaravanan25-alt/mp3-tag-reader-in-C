#include<stdio.h>
#include <string.h>
#include "edit.h"
#include "type.h"


status copy_file_to_duplicate(char *argv[])
{
    // HERE fptr = ORIGINAL.MP3

    // fp = DUPLICATE.MP3

    FILE *fptr;

    fptr = fopen(argv[4] , "r");

    if (fptr == NULL)
    {
        printf("\n ERROR file can't open");
    }
    else
    {
        FILE *fp;

        fp = fopen("duplicate.mp3" , "w");

        if (fp == NULL)
        {
            printf("\n File didn't open for writing");
        }
        else
        {
            printf("\n File opened for writing successfully\n ");

            // NOW COPY EVERYTHING TO THIS FILE 

            // first 10 bytes of header read and qrite here from original.mp3

            char buffer[10];

            fread(buffer , 10 , 1 , fptr);            

            fwrite(buffer, 10 , 1, fp);

             if ( strcmp (argv[2] , "-t") ==0)
            {
                char str[10] = "TIT2";

                printf("\n To change the title ");

               mp3_tag_edit_function(fptr, fp , str, argv);
            }

            else if ( strcmp ( argv[2] , "-a")==0)
            {
                   char str[10] = "TPE1";
             
                printf("\n To change the artist name");

                mp3_tag_edit_function (fptr , fp, str, argv);
            }

            else if ( strcmp(argv[2] , "-A")==0)
            {
                char str[10] = "TALB";
                
                printf("\n To change the Album name  ");

                mp3_tag_edit_function(fptr,fp , str, argv);
            }

            else if ( strcmp(argv[2] , "-y")==0)
            {
              char str[10] = "TYER";
               
                printf("\n To change the Year  ");

                mp3_tag_edit_function(fptr, fp , str, argv);
            }

            else if ( strcmp(argv[2] ,"-m")==0)
            {
              char str[10] = "TCON";

                printf("\n To change the Content ");

                mp3_tag_edit_function(fptr, fp , str, argv);
            }
            else if ( strcmp(argv[2] ,"-c")==0)
            {
               char str[10] = "COMM";

                printf("\n To change the Comment  ");

                mp3_tag_edit_function(fptr,fp , str , argv);
            }
            
        }
    }
    return SUCCESS;
}

status mp3_tag_edit_function(FILE *fptr , FILE *fp , char *str , char *argv[])
{
  
    for(int i =0; i < 6; i++)
    {
    // FIRST STEP READ THE TAG 

    char tag[5]; 

    fread(tag , 4  , 1, fptr); // this always coming TIT2 

    tag[5]= '\0';

    printf("\n This is the tag i read = %s" , tag);  /// alwaysssss TIT2 COMING

    printf("\n This is the tag from header = %s" , str);

    if ( strcmp ( tag , str) == 0)
    {
        printf("\n Same tag");


         // write the tag to duplicate.mp3

        fwrite ( tag , 4, 1, fp);         // TIT2

         // read and  the size 

         int size;

        fread ( &size , sizeof(int) , 1, fptr);

        char *p = (char*) &size;

      // swap 1st and 4th

      char temp = p[0];
      p[0]= p[3];
      p[3]= temp;

      // swap 2and 3
      temp = p[1];
      p[1] = p[2];
      p[2]= temp;

      printf("\n The old size is -> %d" , size);

      // get size of new content and store it in a varaiable 

      int new_size = strlen(argv[3]);
      int big_endian = new_size;

     // work with this varaiable 

     // convert to big endian here we used the bitwise to convert // note swap doesn't worked here
      new_size++;

         big_endian =  ((new_size & 0x000000FF) << 24) |
          ((new_size & 0x0000FF00) << 8)  |
          ((new_size & 0x00FF0000) >> 8)  |
          ((new_size & 0xFF000000) >> 24);

       fwrite(&big_endian, 4, 1, fp);
      new_size--;

      printf("\n the new size is -> %d" , big_endian);

      // read and write the flag

       char flag[3];

       fread(flag , 3, 1 , fptr);

       fwrite(flag , 3, 1 , fp);

      // write it to duplicate.mp3 

       fwrite(argv[3], sizeof(char)  ,new_size, fp);
	size = size - 1;      
       fseek(fptr , size , SEEK_CUR);
       
        char ch1 ;

    while ( fread(&ch1 , 1,1,  fptr)>0)
    {
        fwrite(&ch1 , 1,1 , fp);
    }
       break;
       // read and writing the remaining characters 
       
    }
    else
    {
        printf("\n different tag");
        // write the tag to duplicate.mp3

        fwrite ( tag , 4, 1, fp); 

        // read and write the size    

        int size;

        fread ( &size , sizeof(int) , 1, fptr);

        fwrite ( &size , sizeof (int) , 1 ,fp); // big endian

        // read and write the flag and null

         char flag[3]; 

         fread ( flag , 3 ,1 , fptr);

         fwrite ( flag,  3 , 1, fp);
         
         // convert the size to little endian

         char *p = (char*) &size;

      // swap 1st and 4th

      char temp = p[0];
      p[0]= p[3];
      p[3]= temp;

      // swap 2and 3

      temp = p[1];
      p[1] = p[2];
      p[2]= temp;

      int i;
     
       char ch;

            for ( i = 0 ; i < size-1  ; i++)
               {
                 fread(&ch, sizeof(char)  , 1, fptr);

                 fwrite(&ch , 1 , 1, fp);

               }     
    }
  }

  remove ("sample.mp3");

  rename ("duplicate.mp3" , "sample.mp3");
}
