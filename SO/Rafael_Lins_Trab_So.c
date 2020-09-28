#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void *pegaid(void *arg){
    char *name = arg;
    pthread_t id = pthread_self();
    pthread_t id2 = syscall(SYS_gettid);
    printf("Eu sou a thread_%s, meu ID com pthread_self(PID) e:%lu e com gettid(TID) e:%lu\n", name, id, id2);
}

void *removepar(void *arg){
    int *num = arg;
    for (int i = 0; i < 100; i++){
        int number = i - 99;
        number = number * (-1);
        if((num[number] % 2) == 0){
            num[number] = 0; 
        }
    }

}

void *remove5(void *arg){
    int *num = arg;
    for (int i =0; i < 100; i++){
        int number = i - 99;
        number = number * (-1);
        if((num[number] % 5) == 0){
            num[number] = 0; 
        }
    }
}

void part1(){
    int num;
    scanf("%d", &num);
    for (int cont = 1; cont <= num; cont++){
    char id[15];
    sprintf(id,"%i",cont);
    pthread_t (thread_[num]);
    pthread_create(&(thread_[num]), NULL, pegaid, &id);
    pthread_join((thread_[num]),NULL);
    }
}

void part2(){
    int vetor[100];
    for (int i = 0; i < 100; i++){
        int num = rand()%100;
        while (num == 0){
            num = rand()%100;
        }
        vetor[i] = num;
    }
    for (int i = 0; i < 100; i++){
        printf("%d\n", vetor[i]);
    }
    pthread_t thread_par, thread_5;
    pthread_create(&(thread_par), NULL, removepar, vetor);
    pthread_create(&(thread_5), NULL, remove5, vetor);
    pthread_join((thread_par),NULL);
    pthread_join((thread_5),NULL);
    printf("\n");
    for (int i = 0; i < 100; i++){
        printf("%d\n", vetor[i]);
    }
}

int main(void){
    part2();
    
}
