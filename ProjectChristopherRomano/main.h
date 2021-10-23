#ifndef PROJECTCHRISTOPHERROMANO_MAIN_H
#define PROJECTCHRISTOPHERROMANO_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define PRINT_ALL (char *) "*\0"
#define READ_BIN "rb"
#define WRITE_BIN "wb"
#define NO_CHAR 'N'

typedef struct entry_ {
    int addr_len;
    char *addr;
    int pwd_len;
    char *pwd;
} ENTRY;

typedef enum {
    NO_OPTION, OPEN_EXISTING, CREATE_NEW, QUIT
} OPTION;

#define DEBUG

#ifdef DEBUG
#define DEBUG_STRING(x) printf("%s\n", x)
#else
#define DEBUG_STRING(x)
#endif

#endif