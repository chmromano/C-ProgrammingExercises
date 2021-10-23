#include "main.h"
#include "helper_functions.h"
#include "strings.h"

bool delete_entry(char *addr, ENTRY *entry_array) {

}

char *crypt(const char *pwd, int pwd_len, char *master) {
    int master_index = 0;
    int pwd_index = 0;

    char *decrypted_pwd;
    decrypted_pwd = malloc(sizeof(char) * pwd_len);
    mem_check(decrypted_pwd);

    while (pwd_index < pwd_len) {

        decrypted_pwd[pwd_index] = (char) (pwd[pwd_index] ^ master[master_index]);

        pwd_index++;
        master_index++;
        if (master_index == (int) strlen(master)) master_index = 0;
    }

    return decrypted_pwd;
}

ENTRY *new_entry(ENTRY *entry_array, int *array_len) {
    entry_array = realloc(entry_array, sizeof(ENTRY) * (*array_len + 1));
    mem_check(entry_array);

    printf("Enter website address: ");
    (entry_array + *array_len)->addr = input_string();
    (entry_array + *array_len)->addr_len = (int) strlen((entry_array + *array_len)->addr) + 1;

    printf("Enter password: ");
    char *pwd_buffer;
    pwd_buffer = input_string();

    DEBUG_STRING(pwd_buffer);

    printf("Enter master password: ");
    char *master_buffer;
    master_buffer = input_string();

    (entry_array + *array_len)->pwd_len = (int) strlen(pwd_buffer) + 1;
    (entry_array + *array_len)->pwd = crypt(pwd_buffer, (entry_array + *array_len)->pwd_len, master_buffer);

    DEBUG_STRING((entry_array + *array_len)->pwd);
    free(master_buffer);
    free(pwd_buffer);

    *array_len = *array_len + 1;

    return entry_array;
}

ENTRY *read_entries(int *array_len, FILE *file) {
    ENTRY entry_buffer;
    ENTRY *entry_array;
    entry_array = NULL;

    fread(array_len, sizeof(int), 1, file);

    printf("%d\n", *array_len);

    int i;
    for (i = 0; i < *array_len; i++) {
        fread(&entry_buffer, sizeof(ENTRY), 1, file);
        entry_array = realloc(entry_array, sizeof(ENTRY) * (i + 1));
        mem_check(entry_array);

        (entry_array + i)->addr_len = entry_buffer.addr_len;
        (entry_array + i)->pwd_len = entry_buffer.pwd_len;

        (entry_array + i)->addr = malloc(sizeof(char) * (entry_array + i)->addr_len);
        mem_check((entry_array + i)->addr);
        fread((entry_array + i)->addr, sizeof(char), (entry_array + i)->addr_len, file);

        (entry_array + i)->pwd = malloc(sizeof(char) * (entry_array + i)->pwd_len);
        mem_check((entry_array + i)->pwd);
        fread((entry_array + i)->pwd, sizeof(char), (entry_array + i)->pwd_len, file);
        DEBUG_STRING((entry_array + i)->pwd);
    }

    return entry_array;
}

void print_entries(char *addr, ENTRY *entry_array, int array_len) {

    if (array_len == 0) {
        NO_PWD_MSG;
    } else {
        int longest_index = strlen(NMR);
        int longest_addr = strlen(ADDR);
        int longest_pwd = strlen(PWD);

        int index = 0;

        for (int i = 0; i < array_len; i++) {
            if (strcmp(PRINT_ALL, addr) == 0 || strcmp((entry_array + i)->addr, addr) == 0) index++;
            if ((entry_array + i)->addr_len > longest_addr) longest_addr = (entry_array + i)->addr_len;
            if ((entry_array + i)->pwd_len > longest_pwd) longest_pwd = (entry_array + i)->pwd_len;
        }

        int digits = 0;
        int temp_index = index;
        while (temp_index != 0) {
            temp_index = temp_index / 10;
            digits++;
        }
        if (digits > longest_index) longest_index = digits;

        printf("Enter master password: ");
        char *master_buffer;
        master_buffer = input_string();

        printf("%-*s | %-*s | %-*s\n", longest_index, NMR, longest_addr, ADDR, longest_pwd, PWD);

        index = 0;
        for (int i = 0; i < array_len; i++) {
            if (strcmp(PRINT_ALL, addr) == 0 || strcmp((entry_array + i)->addr, addr) == 0) {
                index++;
                char *decrypted_pwd;
                decrypted_pwd = NULL;
                decrypted_pwd = crypt((entry_array + i)->pwd, (entry_array + i)->pwd_len, master_buffer);
                printf("%*d | %*s | %*s\n", longest_index, index, longest_addr, (entry_array + i)->addr, longest_pwd, decrypted_pwd);
                free(decrypted_pwd);
            }
        }

        free(master_buffer);
    }
}

void write_entries(ENTRY *entry_array, int array_len, FILE *file) {

    printf("%d\n", array_len);

    fwrite(&array_len, sizeof(int), 1, file);

    for (int i = 0; i < array_len; i++) {
        fwrite((entry_array + i), sizeof(ENTRY), 1, file);
        fwrite((entry_array + i)->addr, sizeof(char), (entry_array + i)->addr_len, file);
        free((entry_array + i)->addr);
        DEBUG_STRING((entry_array + i)->pwd);
        fwrite((entry_array + i)->pwd, sizeof(char), (entry_array + i)->pwd_len, file);
        free((entry_array + i)->pwd);
    }

    free(entry_array);
}