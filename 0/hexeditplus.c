#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory.h>
#define FREE(X) if(X) free((void*)X)


typedef struct main_menu{
    char *name;
    void (*func)();
}main_menu;


//GLOBAL vars
char* file_name ;
int size;

void set_file_name(){
    FREE(file_name);
    printf("enter file name");
    file_name=malloc(100* sizeof(char));
    scanf("%s",file_name);
}

void set_unit_size(){
    printf("enter unit size");
    int tmp;
    scanf("%d",&tmp);
    //int tmp1=atoi(tmp);
    if(tmp==1 ||tmp==2 || tmp==4)
        size=tmp;
    else
        //printf("illegal size");
        perror("illegal size! \n");
}

void quit(){
    printf("file_name: %s",file_name); //TODO- remove when finish
    printf("size: %d\n",size); //TODO- remove when finish
    FREE(file_name);
    exit(EXIT_SUCCESS);
}


int main(int argc, char **argv) {

    int cond=1;
    while(cond==1){
        printf("Choose action:\n");
        printf("1-Set File Name\n");
        printf("2-Set Unit Size\n");
        printf("3-Quit\n");
        int tmp;
        scanf("%d",&tmp);
        switch (tmp){
            case 1:
                set_file_name();
                break;
            case 2 :
                    set_unit_size();
                    break;

            case 3:
                    quit();
            default:
                break;
            }

        }


    }


    /*
    set_file_name();
    printf("file_name: %s\n",file_name);
    int i=0;
    for(;i<3;i++){
        printf("before: %d\n", size);
        set_unit_size();
        printf("after: %d\n", size);
    }
    quit();*/

