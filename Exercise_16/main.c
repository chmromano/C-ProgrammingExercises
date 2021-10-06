#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool validate_filename(char string[]);

int validate_int(bool offset);

int main() {
    //Create pointer to array of data from file, and variable to keep track of the amount of allocated memory.
    uint8_t *data = NULL;
    int data_items = 0;

    //Get the name of the file.
    char *file_name = NULL;
    file_name = (char *) malloc(sizeof(char));
    if (file_name == NULL) {
        printf("Error allocating memory. Ending program.");
        exit(1);
    }
    file_name[0] = '\0';
    printf("Enter file name: ");
    while (validate_filename(file_name) == false);

    FILE *my_file;
    my_file = fopen(file_name, "rb");

    if (my_file == NULL) {
        printf("Error opening the file. ");
    } else {
        //Read bytes from the file 1 by 1 until end of the file. Copy bytes to array and reallocate memory as needed.
        uint8_t buffer = 0;
        for (int i = 0; fread(&buffer, sizeof(uint8_t), (size_t) 1, my_file) != 0; i++) {
            data_items++;
            data = (uint8_t *) realloc(data, sizeof(uint8_t) * data_items);
            if (data == NULL) {
                printf("Error allocating memory. Ending program.");
                exit(1);
            }
            data[i] = buffer;
        }

        printf("File size: %d bytes\n", data_items);

        int offset;
        int bytes_to_remove;
        //Check that offset from start and bytes to remove don't go out of bounds.
        bool valid_offset_and_bytes = false;
        while (valid_offset_and_bytes == false) {
            offset = validate_int(true);
            bytes_to_remove = validate_int(false);
            if (offset + bytes_to_remove > data_items) {
                printf("Invalid offset and bytes to remove combination, please try again.\n");
            } else {
                valid_offset_and_bytes = true;
            }
        }

        if (bytes_to_remove == 0) {
            printf("No bytes were removed.");
        } else {
            //Overwrite bytes_to_remove array elements, starting from offset, then move rest of the array forward.
            for (int i = offset; i < data_items - bytes_to_remove; i++) {
                data[i] = data[i + bytes_to_remove];
            }
            //Reallocate memory to new array size (without bytes_to_remove).
            data = (uint8_t *) realloc(data, sizeof(uint8_t) * (data_items - bytes_to_remove));
            if (data == NULL) {
                printf("Error allocating memory. Ending program.");
                exit(1);
            }

            //Close file and open for writing.
            fclose(my_file);
            my_file = fopen(file_name, "wb");

            //Write array (in bytes) to file.
            if (my_file == NULL) {
                printf("Error opening the file. ");
            } else {
                fwrite(data, sizeof(uint8_t), (data_items - bytes_to_remove), my_file);
            }

            if (bytes_to_remove == 1) {
                printf("Removed %d byte.", bytes_to_remove);
            } else {
                printf("Removed %d bytes.", bytes_to_remove);
            }
        }
    }

    free(file_name);
    free(data);
    fclose(my_file);
    return 0;
}

//Function to get filename.
bool validate_filename(char string[]) {
    bool success = true;
    bool read_string = true;
    int allocated = 0;

    while (read_string == true) {

        int character;
        character = getchar();

        if (character == '\n' || character == '\r' || character == '\f') {
            read_string = false;
        } else {
            allocated++;
            string = (char *) realloc(string, (allocated + 1) * sizeof(char));

            if (string == NULL) {
                printf("Error reallocating memory. Ending program.");
                exit(1);
            }

            string[allocated - 1] = (char) character;
            string[allocated] = '\0';
        }
    }

    if (strlen(string) == 0) {
        printf("Enter valid file name: ");
        success = false;
    }

    return success;
}

//Function to validate the integer inputs.
int validate_int(bool offset) {
    int ch;
    int input = 0;
    bool valid_input = false;

    if (offset == true) {
        printf("Enter offset from start of file: ");
    } else {
        printf("Enter number of bytes to remove: ");
    }

    while (valid_input == false) {
        if (scanf("%d", &input) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {

            while ((ch = getchar()) != '\n' && ch != EOF);

            if (offset == true) {
                printf("Invalid characters. Enter offset size: ");
            } else {
                printf("Invalid characters. Enter bytes to remove: ");
            }

        } else if (input < 0) {
            if (offset == true) {
                printf("Invalid offset. Enter offset size: ");
            } else {
                printf("Invalid number. Enter bytes to remove: ");
            }
        } else {
            valid_input = true;
        }
    }

    return input;
}