#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
 
#define PATH1 "./test_4_1.txt"
#define PATH2 "./test_txt"
 
#define READ_BUFF 100
 
int main()
{
    FILE *fp1, *fp2;
    int c = 0;
    char buf[READ_BUFF] = {0};
    if ((fp1 = fopen(PATH1, "rb")) == NULL) {
       printf("get file1 fp fail");
       return -1;
    }
    if ((fp2 = fopen(PATH2, "wb")) == NULL) {
       printf("get file2 fp fail\n");
       return -1;
    }
    while((c = fread(buf, sizeof(char), READ_BUFF, fp1)) > 0) {
       fwrite(buf, sizeof(char), c, fp2);
    }
    if(fclose(fp1) != 0) {
       puts("close fp1 fail");
    }
    if(fclose(fp2) != 0) {
      puts("close fp2 fail");
    }
    return 0;
}

