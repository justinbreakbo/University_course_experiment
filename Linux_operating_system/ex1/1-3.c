#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void thread(void){
    int i;
    for(i = 0; i < 5; i++){
        printf("线程_%d\n",i);
    }
}

int main(){
    pthread_t id;
    int i,ret;
    ret = pthread_create(&id,NULL,(void *)thread,NULL);
    if(ret != 0){
        printf("线程创建失败!\n");
        exit(1);
    }
    for(i = 0; i < 5; i++){
        printf("主进程_%d\n",i);
        sleep(1);
    }
    pthread_join(id,NULL);
    return (0);
}
