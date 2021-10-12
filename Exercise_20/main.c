#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define N_WORDS 10

#define N_CHAR_START 2
#define N_CHAR_RANGE 6

#define ASCII_START 33
#define ASCII_RANGE 94

#define ZERO 0

#define N_PASSWORDS 3

void generate_password(char *password, int size, const char *word_array[]);

int rnd_int_gen(int range, int start);

int main() {
    srand(time(NULL));

    //Populating the dictionary.
    const char *dictionary[N_WORDS];
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

//Function to generate the password.
void generate_password(char *password, int size, const char *word_array[]) {
    int word_index = rnd_int_gen(size, ZERO); //Dictionary index from 0 to (size - 1)
    int n_random_characters = rnd_int_gen(N_CHAR_RANGE, N_CHAR_START); //2 to 7 random characters in the password
    int tot_password_len = (int) strlen(word_array[word_index]) + n_random_characters + 1;

    password = (char *) realloc(password, (tot_password_len) * sizeof(char));
    if (password == NULL) {
        printf("There was an error allocating memory.");
        exit(1);
    }

    for (int i = 0; i < n_random_characters; i++) {
        password[i] = (char) rnd_int_gen(ASCII_RANGE, ASCII_START);
    }

    // strlen(...) + 1 copies end of string character '\0' as well.
    memcpy((void *) &password[n_random_characters], word_array[word_index], strlen(word_array[word_index]) + 1);


    //printf("%d - %d - %d - %s\n", n_random_characters, word_index, tot_password_len, password); //Debug help.
}

//Function to generate random int.
int rnd_int_gen(int range, int start) {
    return rand() % range + start;
}