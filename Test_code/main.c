#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIGNATURE printf("%s\n", name);
#define FILE_N "bin.bin"
char name[32] = {84, 97, 115, 107,
                 32, 83, 111, 108,
                 117, 116, 105, 111,
                 110, 32, 98, 121, 32,
                 86, 97, 115, 105, 108,
                 121, 32, 68, 97, 118,
                 121, 100, 111, 118};
typedef struct AUTO {
    char *maker;
    char *model;
    int price;
    float emissions;
}AUTO;
void rm_n_r(char *str);
void main_menu();
bool writeCar(FILE *f, AUTO *c_add);
size_t getfl(FILE *fp);
int readInt();
int printAll(const char *fn);
int addCar(const char *fn);
float readFloat();

int main () {
    SIGNATURE
    //Initializing variables
    FILE *fp;
    int userChoice = 0;
    while (userChoice != 3) {
        main_menu();
        userChoice = readInt();
        switch (userChoice) {
            case 1:
                printf("You chose printing all cars!\n");
                if (!printAll(FILE_N)){
                    printf("File is empty\n Add something first! \n\n");
                }
                break;
            case 2:
                printf("You chose adding a car!\n");
                if (addCar(FILE_N)) {
                    printf("Car added successfully!\n");
                } else {
                    printf("Program was not able to add a car.\n");
                }
                break;
            case 3:
                printf("EXITING THE PROGRAM!\n");
                break;
            default:
                printf("That is out of your choice scope...\n");
                break;
        }
    }
    return 0;
}


void main_menu(){
    printf("   __  ______   _____  __  __  ________  ____  __\n");
    printf("  /  |/  / _ | /  _/ |/ / /  |/  / __/ |/ / / / /\n");
    printf(" / /|_/ / __ |_/ //    / / /|_/ / _//    / /_/ / \n");
    printf("/_/  /_/_/ |_/___/_/|_/ /_/  /_/___/_/|_/|____/\n");
    printf("              CHOOSE YOUR OPTION                 \n");
    printf("1. Print all cars in a file\n");
    printf("2. Add new car to a file\n");
    printf("3. Quit the program\n");
    printf("Enter your choice <<< ");
}

//Reading an integer
int readInt(){
    char s[15];
    int o;
    do{
        fgets(s, 15, stdin);
    }while(sscanf(s, "%d", &o) != 1);
    return o;
}

//Reading a float
float readFloat(){
    char s[15];
    float o;
    do{
        fgets(s, 15, stdin);
    }while(sscanf(s, "%f", &o) != 1);
    return o;
}

int addCar(const char *fn){
    FILE *fp;
    AUTO *new_car = malloc(sizeof(AUTO));
    char *maker = NULL, *model = NULL;
    size_t maker_s = 0, model_s = 0;
    //GETTING INPUT FOR CAR DATA
    //Asking for maker
    printf("Enter car maker <<< ");
    new_car->maker = calloc(getline(&maker, &maker_s, stdin)-1, sizeof(char));
    rm_n_r(maker);
    new_car->maker = maker;
    //Asking for model
    printf("Enter %s's model <<< ", new_car->maker);
    new_car->model = calloc(getline(&model, &model_s, stdin)-1, sizeof(char));
    rm_n_r(model);
    new_car->model = model;
    //Asking for price
    printf("Enter %s's price <<< ", new_car->model);
    new_car->price = readInt();
    //Asking for emission
    printf("Enter %s's co2 emissions g/km (float) <<< ", new_car->model);
    new_car->emissions = readFloat();
    //WORKING WITH A FILE
    fp = fopen(fn, "ab");
    if (fp == NULL){
        printf("%s\n", strerror(2));
    } else{
        if (!writeCar(fp, new_car)){
            printf("Car input is incorrect or empty");
            return 0;
        }
    }
    fclose(fp);
    //Check this for memory leaks
#if 1
    free(maker);
    free(model);
#endif

#if 1
    free(new_car);
#endif
    return 1;
}
//Printing all cars from a file
int printAll(const char *fn){
    FILE *fp;
    char *carline = NULL;
    size_t file_s;
    const char *cara = "@";
    char *tok_car;
    int el_counter = 0;
    //WORKING WITH A FILE
    fp = fopen(fn, "rb");
    if (fp == NULL){
        printf("%s\n", strerror(2));
    } else{
        file_s = getfl(fp);
        if (file_s == 0){ //Checking if the file is empty
            return 0;
        }else{
            carline = (char*)calloc(file_s, sizeof(char));
            fread(carline, sizeof(char), file_s, fp);
            tok_car = strtok(carline, cara);
            while (tok_car != NULL){
                el_counter++;
                printf("%-10s", tok_car);
                tok_car = strtok(NULL, cara);
                if (el_counter == 4){
                    printf("\n");
                    el_counter = 0;
                }
            }
        }
    }
    fclose(fp);
    free(carline);
    carline = NULL;
    return 1;
}

//Getting the length of a file
size_t getfl(FILE *fp){
    long file_s;
    fseek(fp, 0, SEEK_END);
    file_s = ftell(fp);
    rewind(fp);
    return file_s;
}

//removing the unnecessary characters from a input string
void rm_n_r(char *str){
    for (int i = 0; i < strlen(str); ++i) {
        if(str[i] == '\r' || str[i] == '\n'){
            str[i] = '\0';
        }
    }
}
/* Writing a car data to a file using delimiter.
 * Using  @ to separate cars from each other*/
bool writeCar(FILE *f, AUTO *c_add){
    char *carput = NULL;
    size_t str = ((strlen(c_add->model) + strlen(c_add->maker) + 10)*sizeof(char)) + (sizeof(c_add->price)+sizeof(c_add->emissions));
    if (c_add == NULL){
        return false;
    }else {
#if 1
        carput = malloc(str);
        snprintf(carput, str, "@%s@t%s@%d@%.2f", c_add->maker, c_add->model, c_add->price, c_add->emissions);
        fwrite(carput, sizeof(char), strlen(carput), f);
        carput = NULL;
#endif
    }
    return true;
}