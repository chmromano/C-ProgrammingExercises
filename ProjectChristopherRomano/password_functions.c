#include "main.h"
#include "helper_functions.h"
#include "strings.h"

bool delete_entry(char *addr, ENTRY *entry_array) {

}

//Function to encrypt/decrypt a password. Returns a char* to the encrypted/decrypted password.
char *crypt(const char *pwd, int pwd_len, char *master) {
    int master_index = 0;
    int pwd_index = 0;

    char *decrypted_pwd;
    decrypted_pwd = malloc(sizeof(char) * pwd_len);
    mem_check(decrypted_pwd);

    while (pwd_index < pwd_len) {
        //XORing characters.
        decrypted_pwd[pwd_index] = (char) (pwd[pwd_index] ^ master[master_index]);
        pwd_index++;
        master_index++;
        //Keeping track of master password being shorter than password.
        if (master_index == (int) strlen(master)) master_index = 0;
    }

    return decrypted_pwd;
}

//Function to create a new entry. Returns an ENTRY* array with the new entry appended to all previous entries.
ENTRY *new_entry(ENTRY *entry_array, int *array_len) {
    entry_array = realloc(entry_array, sizeof(ENTRY) * (*array_len + 1));
    mem_check(entry_array);

    //Store address and address length.
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

    //Store encrypted password and password length.
    (entry_array + *array_len)->pwd_len = (int) strlen(pwd_buffer) + 1;
    (entry_array + *array_len)->pwd = crypt(pwd_buffer, (entry_array + *array_len)->pwd_len, master_buffer);

    DEBUG_STRING((entry_array + *array_len)->pwd);
    //Free buffers and update array length.
    free(master_buffer);
    free(pwd_buffer);
    *array_len = *array_len + 1;

    return entry_array;
}

//Function to print a specific or all entries.
void print_entries(char *addr, ENTRY *entry_array, int array_len) {
    if (array_len == 0) {
        NO_PWD_MSG;
    } else {
        int index = 0;

        //Find how much space is needed to print.
        int longest_index = strlen(NMR);
        int longest_addr = strlen(ADDR);
        int longest_pwd = strlen(PWD);
        for (int i = 0; i < array_len; i++) {
            if (strcmp(PRINT_ALL, addr) == 0 || strcmp((entry_array + i)->addr, addr) == 0) index++;
            if ((entry_array + i)->addr_len > longest_addr) longest_addr = (entry_array + i)->addr_len;
            if ((entry_array + i)->pwd_len > longest_pwd) longest_pwd = (entry_array + i)->pwd_len;
        }

        if (index == 0) {
            //If no matching address is found.
            NO_WEBSITE_MSG;
        } else {
            //Find space for decimals (only matters when >99 passwords are stored but still nice to have).
            int digits = 0;
            int temp_index = index;
            while (temp_index != 0) {
                temp_index = temp_index / 10;
                digits++;
            }
            if (digits > longest_index) longest_index = digits;
            index = 0;

            printf("Enter master password: ");
            char *master_buffer;
            master_buffer = input_string();

            //Printings. Plaintext passwords are freed from memory ASAP.
            printf("\n%-*s | %-*s | %-*s\n", longest_index, NMR, longest_addr, ADDR, longest_pwd, PWD);
            for (int i = 0; i < array_len; i++) {
                if (strcmp(PRINT_ALL, addr) == 0 || strcmp((entry_array + i)->addr, addr) == 0) {
                    index++;
                    char *decrypted_pwd;
                    decrypted_pwd = NULL;
                    decrypted_pwd = crypt((entry_array + i)->pwd, (entry_array + i)->pwd_len, master_buffer);
                    printf("%*d | %*s | %*s\n", longest_index, index, longest_addr, (entry_array + i)->addr,
                           longest_pwd, decrypted_pwd);
                    free(decrypted_pwd);
                }
            }
            free(master_buffer);

            //Spacing.
            PRINT_NEWLINE;
        }
    }
}

//Function to read existing entries from a file. Returns an ENTRY* array with all entries.
ENTRY *read_entries(int *array_len, FILE *file) {
    ENTRY entry_buffer;
    ENTRY *entry_array;
    entry_array = NULL;

    //Read number of entries stored.
    fread(array_len, sizeof(int), 1, file);

    //Read each entry while allocating memory as needed. First ENTRY structure then strings based on stored lengths.
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

//Function to write all entries to a file.
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