#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory.h>
#define FREE(X) if(X) free((void*)X)


typedef struct menu{
    void (*func)();
    char *func_name;
}menu;


//GLOBAL vars
char* file_name ;
int size;

void prints(unsigned char* arr,int length, char flag){
    int i=0;
    //printf("length=  %d   arr= %s",length,arr);
    //switch case- different printf for unit
    if(flag=='h')
        printf("Hexadecimal Representation:\n");
    else //flag==d
        printf("Decimal Representation:\n");
    switch (size){
        case 2:
            for (; i < length; i ++){
                if(flag=='h')
                    printf( "%04x " ,(( unsigned short* ) arr)[i] );
                else    //flag==d
                    printf( "%d " ,(( unsigned short* ) arr)[i] );
            }
            break;
        case 4:
            for(;i<length;i++){
                if(flag=='h')
                    printf( "%08x " ,(( unsigned int* ) arr)[i] );
                else    //flag==d
                    printf( "%d " ,(( unsigned int* ) arr)[i] );
            }
            break;
            //default- size==1 (as writen in the lab description)
        default:
            for(;i<length;i++){
                if(flag=='h')
                    printf( "%02x " , arr[i] );
                else //flag==d
                    printf( "%d " , arr[i] );
            }
            break;
    }
    printf("\n");

}

void set_file_name(){
    FREE(file_name);
    printf("enter file name\n");
    file_name=malloc(100* sizeof(char));
    scanf("%s",file_name);
}

void set_unit_size(){
    printf("enter unit size\n");
    int tmp;
    scanf("%d",&tmp);
    //int tmp1=atoi(tmp);
    if(tmp==1 ||tmp==2 || tmp==4)
        size=tmp;
    else
        //printf("illegal size");
        perror("illegal size!");
}

void quit(){
//    printf("file_name: %s",file_name); //TODO- remove when finish
//    printf("   size: %d\n",size); //TODO- remove when finish
    FREE(file_name);
    exit(0);
}

void file_display(){
    int fd=0,length=0;
    //int malloc_size;
    unsigned int file_location=0;
    unsigned char* tmp;
    if(file_name==NULL){
        perror("file_name is null!");
        return;
    }
    if(size==0){
        perror("illegal size!");
        return;
    }
    //open file stream
    if((fd = open(file_name, O_RDONLY))<0){
        perror("Failed open file stream\n");
        return;
    }
    printf("Please enter <location> (in hexadecimal) and <length> (in decimal)\n");
    scanf("%x %d",&file_location,&length);
    fflush( stdin );
    //malloc
    //malloc_size=size*length;
    tmp = malloc(size*length);

    //printf("file_location: %x   length= %d   tmp= %s",file_location,length,tmp);
    //go to entry point
    if(lseek(fd,file_location,SEEK_SET)<0){
        perror("lseek error!");
        return;
    }
    read(fd,tmp,size*length);   //read into buffer;
    close(fd);    //close streaming
    unsigned char* tmp_ptr=tmp;
    prints(tmp,length,'h'); //print hexadecimal
    tmp=tmp_ptr;
    prints(tmp,length,'d');    //print decimal
    FREE(tmp);    //free tmp memory
}

void file_modify(){
    int location=0,fd=0,fd_curr,unsigned_vals=0,val=0;
    if(file_name==NULL){
        perror("file_name is null!");
        return;
    }
    //open file stream
    if((fd = open(file_name, O_RDWR))<0){
        perror("Failed open file stream\n");
        return;
    }
    printf("Please enter <location> <val> (both in hexadecimal)\n");
    scanf("%x %x", &location,&val);
//    printf("location =  %x,  val=  %x\n",location,val);
    unsigned_vals = (unsigned int ) val;
    //go to location align
    fd_curr= (int) lseek(fd, 0, SEEK_END);
    if(fd_curr<0 || (fd_curr+1)<location){
        perror("wrong location!") ;
        return;
    }
    //move location to offset of write-point
    lseek(fd,0,SEEK_SET);
    lseek(fd,location,SEEK_SET);

    ssize_t write_num=write(fd, &unsigned_vals, (size_t) size);
    if(write_num!=size)
        perror("write went wrong!");
    close(fd);
//    printf("@#$@#$");
}

void copy_From_File(){
    char *src_file=malloc(1024);
    char* dst_file=file_name;
    unsigned int src_offset=0,dst_offset=0;
    int length=0;
    int src_fd,dst_fd;
    printf("Please enter <src_file> <src_offset> <dst_offset> <length>\n");
    scanf("%s %x %x %d",src_file,&src_offset,&dst_offset,&length);
    if(!src_file){
        perror("src_file is NULL!");
        FREE(src_file);
        return;
    }
    if(!dst_file){
        perror("src_file is NULL!");
        FREE(src_file);
        return;
    }
    //Open src_file for reading. If this fails, print an error message and return.
    if((src_fd=open(src_file,O_RDONLY))<0){
        perror("open ERROR!");
        FREE(src_file);
        return;
    }
    // Open dst_file for read & write (not write only). If this fails, print an error message and return.
    //TODO - maybe O_WRONLY
    if((dst_fd=open(dst_file,O_RDWR))<0){
        perror("open ERROR!");
        FREE(src_file);
        return;
    }
    //Read length bytes from src_file at offset src_offset and write them to dst_file at dst_offset
    //set the src_fd
    if((lseek(src_fd,src_offset,SEEK_SET))<0){
        perror("lseek#1 ERROR!");
        FREE(src_file);
        return;
    }
    //set the dst_fd
    if((lseek(dst_fd,dst_offset,SEEK_SET))<0){
        perror("lseek#2 ERROR!");
        FREE(src_file);
        return;
    }
    char* buffer=malloc(size * length);
    //read |length| bytes
    if((read(src_fd,buffer,length))<0){
        perror("read from src_file ERROR!");
        FREE(src_file);
        FREE(buffer);
        return;
    }
    //write to dst_file
    if((write(dst_fd,buffer,length))<0){
        perror("write to dst_file ERROR!");
        FREE(src_file);
        FREE(buffer);
        return;
    }
    //got here - succeeded in copying ->close streaming and free()
    printf("Copied %d bytes FROM %s at %X TO %s at %X\n",length,src_file,src_offset,dst_file,dst_offset);
    close(dst_fd);
    close(src_fd);
    FREE(buffer);
    FREE(src_file);
}


int main(int argc, char **argv) {

    size=1;
    struct menu menu[]={{set_file_name,"Set File Name"},
                        {set_unit_size,"Set Unit Size"},
                        {file_display,"File Display"},
                        {file_modify,"File Modify"},
                        {copy_From_File,"Copy From File"},
                        {quit,"Quit"},
                        {NULL,NULL}
                        };
    int cond=1;
    while(cond==1){
        printf("-----------------\n"
               "Choose action:\n"
               "1-Set File Name\n"
               "2-Set Unit Size\n"
               "3-File Display\n"
               "4-File Modify\n"
               "5-Copy From File\n"
               "6-Quit\n"
               "-----------------\n");/*
        printf("-----------------\n");
        printf("Choose action:\n");
        printf("1-Set File Name\n");
        printf("2-Set Unit Size\n");
        printf("3-File Display\n");
        printf("4-File Modify\n");
        printf("5-Copy From File");
        printf("6-Quit\n");
        printf("-----------------\n");*/
        int tmp;
        scanf("%d",&tmp);
        if(tmp<1 || tmp>6)
            perror("illegal input, please try again");
        else
            menu[tmp-1].func();

        }

    return 1;
    }



