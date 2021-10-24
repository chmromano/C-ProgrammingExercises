#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

//Some needed constants.
#define PRINT_ALL (char *) "*\0"
#define READ_BIN "rb"
#define WRITE_BIN "wb"
#define NO_CHAR 'N'

//Avoiding conflicts.
#ifndef PROJECTCHRISTOPHERROMANO_MAIN_H
#define PROJECTCHRISTOPHERROMANO_MAIN_H

//Struct to store entries.
typedef struct entry_ {
    int addr_len;
    char *addr;
    int pwd_len;
    char *pwd;
} ENTRY;

//Typedef makes choices in main easier to track.
typedef enum {
    NO_OPTION, OPERATE, QUIT
} OPTION;

#endif