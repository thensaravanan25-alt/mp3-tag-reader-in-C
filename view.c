#include<stdio.h>
#include <string.h>
#include "view.h"
#include "type.h"

status check_operation_type(char *argv[])
{
    char ch[10] = "-v";

     char ch2[10]= "-e";

    if(strcmp(argv[1] , ch) == 0)
    {
        return e_view;
    }
     
    else if ( strcmp(argv[1] , ch2) ==0)
    {
        return e_edit;
    }
    else
    {
        return e_unsupported;
    }
}

status read_and_validate_for_view_and_edit(char *argv[] , V_TAG  *v_tag)
{
    char *p;

    char ch[20] =".mp3";

    if ( p = strstr(argv[2] , ch))
    {
        if (strcmp(ch , p ) == 0)
        {
              v_tag->mp3_file_name = argv[2];

              printf("\n The filename is %s" , v_tag->mp3_file_name);

              return SUCCESS;
        }
        else
        {
            printf("\n-------------------");
            printf("\n Invalid extension");
            printf("\n-------------------\n");

            return FAILURE;
        }
    }
    else
    {
        printf("\n----------------------");
        printf("\n Invalid extension");
        printf("\n------------------------\n");

        return FAILURE;

    }
}

status mp3_view (char *argv[])
{
    // OPEN THE MP3 FILE

    FILE *fptr;

    fptr = fopen(argv[2] , "r");

    if ( fptr== NULL)
    {
        printf("\n FILE CAN'T OPEN");

        return 0;
    }
    else
    {

        // FETCH THE HEADER 3 BYTES

        if (header_3bytes(argv, fptr) == SUCCESS)
        {
            printf("\n Header read successfully");

            if (skip_bytes_by_fseek(fptr) == SUCCESS)
            {
                printf("\n 7 bytes skipped successfully");

                int i ;
                
                  for ( i =0;i < 6; i++)
                {

                if (read_4bytes_tag_id(fptr) == SUCCESS)

                {
                   // printf("\n  Bytes read  and printed successfully\n");                   
                }
            }
            }
        } 

       // return SUCCESS;
    }

}

status header_3bytes (char *argv[] , FILE *fptr)
{
     char buffer[4];

        fread ( buffer , 3, 1 , fptr);

        buffer[4] = '\0';

          printf("\n The buffer is %s " , buffer);

        if (strcmp(buffer , "ID3") ==0)
        {
            printf("\n ID3 compared successfully ");

            return SUCCESS;
        }
        else
        {
            printf("\n ID3 is not found\n ");

            return FAILURE;
        }
}

// SKIP THE NEXT 7 BYTES

status skip_bytes_by_fseek(FILE *fptr)
{
    fseek(fptr , 7 , SEEK_CUR); 

    return SUCCESS;
}

status read_4bytes_tag_id( FILE *fptr )
{

    char tag[5];

    int size;
    
    fread(tag , 4 , 1 , fptr);

    tag[5] = '\0';

    printf("\n-------------------------------------------------------");

    printf("\n %s -----> " , tag);                   

    fread(&size , sizeof(int) , 1 , fptr);    // taking the size from fptr and store in size varaible

     // conert the big endian to little endian
   
      char *p = (char*) &size;

      // swap 1st and 4th

      char temp = p[0];
      p[0]= p[3];
      p[3]= temp;

      // swap 2and 3

      temp = p[2];
      p[2] = p[3];
      p[3]= temp;

     // printf("\n The size is %d\n" , size);

       // skip the 3 bytes 

    fseek (fptr , 3, SEEK_CUR);

    // read the contents in the file 

    int i;
   static int j = 0;
	
    char ch;

   // printf("\nThe contents are : ");

    for ( i = 0 ; i < size - 1 ; i++)
    {

      fread(&ch, sizeof(char) , 1, fptr);

      printf("%c" , ch);
    fflush(stdout);
    }
   /* j++;
    if ( j == 2 )
    {
    while(1);
    }*/ 
  //  printf("\n-----------------------------------------------------");

   return SUCCESS;
}

