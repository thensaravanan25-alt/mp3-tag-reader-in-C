#ifndef EDIT_H

#define EDIT_H

#include "type.h"

status copy_file_to_duplicate(char *argv[]);

status mp3_tag_edit_function(FILE *fptr, FILE *fp, char *str , char *argv[]);

#endif