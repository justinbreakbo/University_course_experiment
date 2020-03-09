#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 10


int main (int argc, char **argv)
{
    int fd1 =0 ;
    int fd2 =0 ;
    char buf1[BUF_SIZE]="";
    char buf2[BUF_SIZE]="";


    fd1 = open("test_4_1.txt", O_RDONLY);
    fd2 = open("test_4_2.txt",O_RDWR);
    read(fd1, buf1, BUF_SIZE);
    read(fd2, buf2, BUF_SIZE);
    //printf("此时文件1内容：%s\n",buf1);
    //printf("此时文件2内容：%s\n",buf2);
    printf("把文件1的内容复制到文件2...\n");

    write(fd2, buf1, strlen(buf1));
    close(fd1);
    close(fd2);

    fd1 = open("test_4_1.txt", O_RDONLY);
    fd2 = open("test_4_2.txt",O_RDONLY);
    read(fd1, buf1, BUF_SIZE);
    read(fd2, buf2, BUF_SIZE);
    //printf("此时文件1内容：%s\n",buf1);
    //printf("此时文件2内容：%s\n",buf2);
    close(fd1);
    close(fd2);
    return 0;
}

