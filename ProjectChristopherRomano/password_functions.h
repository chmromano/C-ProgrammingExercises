#include "main.h"

ENTRY *new_entry(ENTRY *entry_array, int *array_len);

char *decrypt(char *pwd, int pwd_len, char *master);

void print_entries(char *addr, ENTRY *entry_array, int array_len);

ENTRY *read_entries(int *array_len, FILE *file);

void write_entries(ENTRY *entry_array, int array_len, FILE *file);