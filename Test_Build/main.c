/*#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *my_file;
    my_file = fopen("image.jpg", "rb");

    if (my_file == NULL) {
        printf("There was an error opening the file.");
    } else {
        unsigned char buffer;
        while(fread(&buffer, 1, 1, my_file) != 0) {
            printf("%c", buffer);
        }
    }

    return 0;
}*/

#include<stdio.h>
int main(){
    char str[20],c=' ';
    int i=0;
    printf("\n Enter the password [max length 10] : ");
    while (i<=9){
        str[i]=getchar();
        c=str[i];
        if(c==13) break;
        else printf("*");
        i++;
    }
    str[i]='\0';
    i=0;
    printf("\n");
    printf("\n Your password is : %s",str);
    return 0;
}