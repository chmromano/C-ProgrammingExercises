#include "main.h"
#include "strings.h"
#include "helper_functions.h"
#include "password_functions.h"

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

//Function to delete an entry.
ENTRY *delete_entry(ENTRY *entry_array, int *array_len) {
    if (*array_len == 0) {
        NO_PWD_MSG;
    } else {
        PWD_DELETE_SEARCH_MSG;
        char *addr;
        addr = input_string();

        int indexes_len = 0;
        int *indexes;
        indexes = malloc(sizeof(int));
        mem_check(indexes);

        //Get indexes matching the website.
        for (int i = 0; i < *array_len; i++) {
            if (strcmp(entry_array[i].addr, addr) == 0) {
                indexes = realloc(indexes, sizeof(int) * (indexes_len + 1));
                mem_check(indexes);
                indexes[indexes_len] = i;
                indexes_len++;
            }
        }

        if (indexes_len == 0) {
            NO_WEBSITE_MSG;
        } else if (indexes_len == 1) {
            //Delete a single entry.
            for (int i = indexes[indexes_len - 1]; i < *array_len; i++) {
                entry_array[i] = entry_array[i + 1];
            }
            (*array_len)--;
            entry_array = realloc(entry_array, sizeof(ENTRY) * (*array_len));
            mem_check(entry_array);
            PWD_DELETE_SUCCESS_MSG;
        } else {
            //Ask user which entry to delete.
            MULTIPLE_PWD_MSG;
            print_entries(addr, entry_array, *array_len);
            PWD_DELETE_CHOICE(indexes_len);
            int index_to_del = 0;
            while (input_integer(&index_to_del) == false || index_to_del > indexes_len || index_to_del < 0) {
                INVALID_DELETE_MSG(indexes_len);
            }
            if (index_to_del == 0) {
                PWD_DELETE_ABORT_MSG;
            } else {
                for (int i = indexes[index_to_del - 1]; i < *array_len; i++) {
                    entry_array[i] = entry_array[i + 1];
                }
                (*array_len)--;
                entry_array = realloc(entry_array, sizeof(ENTRY) * (*array_len));
                mem_check(entry_array);
                PWD_DELETE_SUCCESS_MSG;
            }
        }

        free(addr);
        free(indexes);
    }

    return entry_array;
}

//Function to create a new entry. Returns an ENTRY* array with the new entry appended to all previous entries.
ENTRY *new_entry(ENTRY *entry_array, int *array_len) {
    entry_array = realloc(entry_array, sizeof(ENTRY) * (*array_len + 1));
    mem_check(entry_array);

    //Store address and address length.
    ADDRESS_MSG;
    entry_array[*array_len].addr = input_string();
    entry_array[*array_len].addr_len = (int) strlen(entry_array[*array_len].addr) + 1;

    PWD_MSG;
    char *pwd_buffer;
    pwd_buffer = input_string();

    MASTER_PWD_MSG;
    char *master_buffer;
    master_buffer = input_string();

    //Store encrypted password and password length.
    entry_array[*array_len].pwd_len = (int) strlen(pwd_buffer) + 1;
    entry_array[*array_len].pwd = crypt(pwd_buffer, entry_array[*array_len].pwd_len, master_buffer);

    //Free buffers and update array length.
    free(master_buffer);
    free(pwd_buffer);
    (*array_len)++;

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
            if (strcmp(PRINT_ALL, addr) == 0 || strcmp(entry_array[i].addr, addr) == 0) index++;
            if (entry_array[i].addr_len > longest_addr) longest_addr = entry_array[i].addr_len;
            if (entry_array[i].pwd_len > longest_pwd) longest_pwd = entry_array[i].pwd_len;
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

            MASTER_PWD_MSG;
            char *master_buffer;
            master_buffer = input_string();

            //Printings. Plaintext passwords are freed from memory ASAP.
            printf("\n| %-*s | %-*s | %-*s |\n", longest_index, NMR, longest_addr, ADDR, longest_pwd, PWD);
            for (int i = 0; i < array_len; i++) {
                if (strcmp(PRINT_ALL, addr) == 0 || strcmp(entry_array[i].addr, addr) == 0) {
                    index++;
                    char *decrypted_pwd;
                    decrypted_pwd = crypt(entry_array[i].pwd, entry_array[i].pwd_len, master_buffer);
                    printf("| %*d | %-*s | %-*s |\n", longest_index, index, longest_addr, entry_array[i].addr,
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
    ENTRY *entry_array;

    //Read number of entries stored.
    fread(array_len, sizeof(int), 1, file);

    //Read each entry while allocating memory as needed. First ENTRY structure then strings based on stored lengths.
    for (int i = 0; i < *array_len; i++) {
        entry_array = realloc(entry_array, sizeof(ENTRY) * (i + 1));
        mem_check(entry_array);

        fread(&entry_array[i], sizeof(ENTRY), 1, file);

        entry_array[i].addr = malloc(sizeof(char) * entry_array[i].addr_len);
        mem_check(entry_array[i].addr);
        fread(entry_array[i].addr, sizeof(char), entry_array[i].addr_len, file);

        entry_array[i].pwd = malloc(sizeof(char) * entry_array[i].pwd_len);
        mem_check(entry_array[i].pwd);
        fread(entry_array[i].pwd, sizeof(char), entry_array[i].pwd_len, file);
    }

    return entry_array;
}

//Function to write all entries to a file.
void write_entries(ENTRY *entry_array, int array_len, FILE *file) {

    //Write array length.
    fwrite(&array_len, sizeof(int), 1, file);

    //Write ENTRY struct. Then write addres and write password, and free their memory.
    for (int i = 0; i < array_len; i++) {
        fwrite(&entry_array[i], sizeof(ENTRY), 1, file);
        fwrite(entry_array[i].addr, sizeof(char), entry_array[i].addr_len, file);
        free(entry_array[i].addr);
        fwrite(entry_array[i].pwd, sizeof(char), entry_array[i].pwd_len, file);
        free(entry_array[i].pwd);
    }

    //Free array memory.
    free(entry_array);
}