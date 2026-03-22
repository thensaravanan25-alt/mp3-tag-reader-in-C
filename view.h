#ifndef VIEW_H
#define VIEW_H

#include "type.h"

typedef struct VTAG
{
     char *mp3_file_name;
     FILE *fptr_mp3_file;

}V_TAG;

status check_operation_type(char *argv[]);

status read_and_validate_for_view_and_edit(char *argv[], V_TAG * v_tag);

status mp3_view(char *argv[] );

status header_3bytes(char *argv[] , FILE *fptr);

status skip_bytes_by_fseek(FILE *fptr);

status read_4bytes_tag_id(FILE *fptr );

//status read_and_print_content(FILE *fptr , int size);

#endif