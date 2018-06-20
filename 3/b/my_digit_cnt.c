#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory.h>

int dig_counter(char* str){
    /*int output=0;
    char* tmp=str;
    while(tmp!='\0'){
        output++;
        ++tmp;
    }
    return output;*/
    int output;
    for(output = 0; str[output] != '\0'; ++output);
    return output;
}
int main(int argc, char **argv) {
    if(argc<1){
        printf("0\n");
        exit(EXIT_FAILURE);
    }
    int print=dig_counter(argv[1]);
    printf("The number of digits in the string is: %d \n", print);

    exit(EXIT_SUCCESS);
}
