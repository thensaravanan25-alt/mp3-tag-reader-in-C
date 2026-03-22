#include<stdio.h>
#include<string.h>
#include "type.h"
#include "view.h"
#include "edit.h"

int main(int argc , char *argv[])
{
    int i;

   V_TAG v_tag;   // variable name


   // PRINTING THE ERROR MESSAGE 
    if (argv[1] == NULL)
    {
        printf("\n---------------------------------------------------------------------------------------------");
        printf("\n INVALID ARGUMENTS : ERROR ");
        printf("\n \n ./a.out -----SOME ARGUMENTS NEEDED------ ");
        printf("\n\n USAGE : ");
        printf("\n To view the file please pass : ./a.out -v <file name >");
        printf("\n To edit the file please pass : ./a.out -e -t/-a/-A/-m/-y/-c <changing text> <file name>");
        printf("\n To get help pass             : ./a.out --help ");
        printf("\n----------------------------------------------------------------------------------------------\n");
        return 0;

    }

    // IF WE NEED HELP USE THIS LOGIC 

    char var[50] = "--help";

    if (strcmp(argv[1] , var)==0)
    {
        printf("\n----------------------------------------------------");
        printf("\n         HELP MENU               ");
        printf("\n----------------------------------------------------");
        printf("\n 1. -v -> To view the file contents ");
        printf("\n 2. -e -> To edit the file contents ");
        printf("\n\t 2.1 -t -> To change the  song title ");
        printf("\n\t 2.2 -a -> To edit the artist name");
        printf("\n\t 2.3 -A -> To edit the album name ");
        printf("\n\t 2.4 -y -> To edit the song year");
        printf("\n\t 2.5 -c -> To edt the song comment");
        printf("\n\t 2.6 -m -> To edit the song content");
        printf("\n----------------------------------------------------\n");
        return 0;
    }

    // TO VIEW USE THIS LOGIC TO VIEW THE AUDIO FILE DETAILS

    if (check_operation_type(argv) == e_view)
    
    {
        if ( argv[2] == NULL)
        {
            printf("\n----------------------------------------------------");
            printf("\nTo view please pass file name : ./a.out -v <sample.mp3>");
            printf("\n--------------------------------------------------\n");

            return FAILURE;
        }

         if (read_and_validate_for_view_and_edit(argv , &v_tag) ==SUCCESS)
           {
                  printf("\n EXtension read successfully");

                  // CALL THE VIEW MP3 FUCNTION TO SE THE DETAILS 

                 if( mp3_view(argv)== SUCCESS)
                 {
                    printf("\n--------------------------------------------------------");
                    printf("\n view function completed  successfully\n ");

                    // FETCH THE FIRST 3 BYTES OF HEADER THAT "ID3 " FETCH

                  
                 }
           }
    }

    // THIS IS EDIT FUNCTION

     if (check_operation_type(argv) == e_edit)
    
    {
        if ( argv[2] == NULL )
        {
            printf("\n----------------------------------------------------------------------------------------");
            printf("\nTo edit please pass file name : ./a.out -e -t/-a/-A/-m/-y/-c <changing text> <file name> ");
            printf("\n----------------------------------------------------------------------------------------\n");

            return FAILURE;
        }

        if ( copy_file_to_duplicate(argv) == SUCCESS)
        {
            printf("\n Inside the edit function");

            

        }

         
    }

}
