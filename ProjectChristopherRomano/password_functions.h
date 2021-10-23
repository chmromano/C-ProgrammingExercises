#include "main.h"

//Function to create a new entry. Returns an ENTRY* array with the new entry appended to all previous entries.
ENTRY *new_entry(ENTRY *entry_array, int *array_len);

//Function to print a specific or all entries.
void print_entries(char *addr, ENTRY *entry_array, int array_len);

//Function to read existing entries from a file. Returns an ENTRY* array with all entries.
ENTRY *read_entries(int *array_len, FILE *file);

//Function to write all entries to a file.
void write_entries(ENTRY *entry_array, int array_len, FILE *file);