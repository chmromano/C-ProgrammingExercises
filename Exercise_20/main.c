#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define N_WORDS 10

#define N_CHAR_START 2
#define N_CHAR_RANGE 6

//Using no whitespace.
#define ASCII_START 33
#define ASCII_RANGE 94

#define ZERO 0

#define N_PASSWORDS 3

void generate_password(char *password, int size, const char *word_array[]);

int rnd_int_gen(int range, int start);

int main() {
    //Seeding rand() with current time (helps with randomness).
    srand(time(NULL));

    const char *dictionary[N_WORDS];
    //Populating the dictionary.
    dictionary[0] = "Trifling";
    dictionary[1] = "Boycotts";
    dictionary[2] = "Photocopy";
    dictionary[3] = "Relaxation";
    dictionary[4] = "Attraction";
    dictionary[5] = "Charismatic";
    dictionary[6] = "Evanescent";
    dictionary[7] = "Sophisticated";
    dictionary[8] = "Impart";
    dictionary[9] = "Defective";

    //Running the loop to generate 3 passwords.
    for (int i = 0; i < N_PASSWORDS; i++) {
        char *password;
        password = malloc(sizeof(char));
        if (password == NULL) {
            printf("There was an error allocating memory.");
            exit(1);
        }
        password[0] = '\0';
        generate_password(password, N_WORDS, dictionary);
        printf("Password n. %d: %s\n", i + 1, password);
        free(password);
    }

    return 0;
}

//Function to generate a password.
void generate_password(char *password, int size, const char *word_array[]) {
    int word_index = rnd_int_gen(size, ZERO); //Dictionary index from 0 to (size - 1).
    int n_random_characters = rnd_int_gen(N_CHAR_RANGE, N_CHAR_START); //2 to 7 random characters in the password.
    int tot_password_len = (int) strlen(word_array[word_index]) + n_random_characters + 1;

    //After password parameters are set allocate memory.
    password = (char *) realloc(password, tot_password_len * sizeof(char));
    if (password == NULL) {
        printf("There was an error allocating memory.");
        exit(1);
    }

    //Populate whole password with random ASCII characters.
    for (int i = 0; i < tot_password_len - 1; i++) {
        password[i] = (char) rnd_int_gen(ASCII_RANGE, ASCII_START);
    }
    password[tot_password_len - 1] = '\0';

    //Calculate valid insertion position.
    int insertion_range = tot_password_len - (int) strlen(word_array[word_index]);
    int insertion_index = rnd_int_gen(insertion_range, ZERO);
    // Copy the chosen word to complete the password.
    memcpy((void *) &password[insertion_index], word_array[word_index], strlen(word_array[word_index]));

    //Debug help.
    //printf("\nN. random char: %d\nWord index: %d\nPwd. length: %lu\nPassword: %s\n", n_random_characters, word_index, strlen(password), password);
}

//Function to generate random int.
int rnd_int_gen(int range, int start) {
    return rand() % range + start;
}