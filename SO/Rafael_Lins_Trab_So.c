#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

/*
    Linha para execucao no prompt
    gcc -pthread -o teste Rafael_Lins_Trab_So.c

*/

sem_t S;

void avalia_vet(int * vet){
    int *num = vet;    
    int cont = 0;
    for (int i = 0; i < 100000; i++){
        if((vet[i] != 0) && (vet[i] % 2) == 0){
            cont += 1;
        }
        if((vet[i] != 0) && (vet[i] % 5) == 0){
            cont += 1;
        }
    }
    if (cont >= 1){
        printf("Deu ruim ai...\n");
    }
    else{
        printf("Tudo certo meu bom !\n");
    }
    


}


void *pegaid(void *arg){
    char *name = arg;
    pthread_t id = pthread_self();
    pthread_t id2 = syscall(SYS_gettid);
    printf("Eu sou a thread_%s, meu ID com pthread_self(PID) e:%lu e com gettid(TID) e:%lu\n", name, id, id2);
}

void *removepar(void *arg){
    int *num = arg;
    for (int i = 0; i < 100000; i++){
        int number = i - 99999;
        number = number * (-1);
        if((num[i] % 2) == 0){
            num[i] = 0; 
        }
    }

}

void *remove5(void *arg){
    int *num = arg;
    for (int i =0; i < 100000; i++){
        int number = i - 99999;
        number = number * (-1);
        if((num[i] % 5) == 0){
            num[i] = 0; 
        }
    }
}

void *remove5_semaphore(void *arg){
    sem_wait(&S);
    int *num = arg;
    for (int i =0; i < 100000; i++){
        int number = i - 99999;
        number = number * (-1);
        if((num[number] % 5) == 0){
            num[number] = 0; 
        }
    }
    sem_post(&S);
}

void *removepar_semaphore(void *arg){
    sem_wait(&S);
    int *num = arg;
    for (int i = 0; i < 100000; i++){
        int number = i - 99999;
        number = number * (-1);
        if((num[number] % 2) == 0){
            num[number] = 0; 
        }
    }
    sem_post(&S);
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



void part2_thread(){
    int vetor[100000];
    for (int i = 0; i < 100000; i++){
        int num = rand()%100;
        while (num == 0){
            num = rand()%100;
        }
        vetor[i] = num;
    }
/*      for (int i = 0; i < 100000; i++){
        printf("%d ", vetor[i]);
      }  
*/
    pthread_t thread_par, thread_5;
    pthread_create(&(thread_par), NULL, removepar, vetor);
    pthread_create(&(thread_5), NULL, remove5, vetor);
    pthread_join((thread_par),NULL);
    pthread_join((thread_5),NULL);

/*      for (int i = 0; i < 100000; i++){
        printf("%d ", vetor[i]);
      }  
*/
    avalia_vet(vetor);    
}

void part2_semaphore(){
    int vetor[100000];
    for (int i = 0; i < 100000; i++){
        int num = rand()%100;
        while (num == 0){
            num = rand()%100;
        }
        vetor[i] = num;
    }
/*      for (int i = 0; i < 100000; i++){
        printf("%d ", vetor[i]);
      }  
*/
    pthread_t thread_par_semaphore,thread_5_semaphore ;
    pthread_create(&(thread_par_semaphore), NULL, removepar_semaphore, vetor);
    pthread_create(&(thread_5_semaphore), NULL, remove5_semaphore, vetor);
    pthread_join((thread_par_semaphore),NULL);
    pthread_join((thread_5_semaphore),NULL);
    printf("\n");
/*      for (int i = 0; i < 100000; i++){
        printf("%d ", vetor[i]);
      }  
*/
    avalia_vet(vetor);
}

void part2(){
    int vetor[100000];
    for (int i = 0; i < 100000; i++){
        int num = rand()%100;
        while (num == 0){
            num = rand()%100;
        }
        vetor[i] = num;
    }
    removepar(vetor);
    remove5(vetor);
  
    avalia_vet(vetor);
}

void EX01(){
    part1();
    printf("\n");
}

void EX02(){
    clock_t t1,t2,t3;
    sem_init(&S, 0,1);
    t1 = clock();
    part2_semaphore();
    t1 = clock() - t1;
    printf("com semaforo %lf ms\n", ((double)t1)/((CLOCKS_PER_SEC/1000)));
    t2 = clock();
    part2_thread();
    t2 = clock() - t2;  
    printf("sem semaforo, com thread %lf ms\n", ((double)t2)/((CLOCKS_PER_SEC/1000)));
    t3 = clock();
    part2();
    t3 = clock() - t3;
    printf("sem nada %lf ms\n", ((double)t3)/((CLOCKS_PER_SEC/1000)));
    printf("\n");
}

int main(void){
    EX01();
    EX02();
}
