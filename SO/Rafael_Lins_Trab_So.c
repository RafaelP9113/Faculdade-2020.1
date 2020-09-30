#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <sys/shm.h>


/*
    Linha para execucao no prompt
    gcc -pthread -o teste Rafael_Lins_Trab_So.c

*/


sem_t S;

void avalia_vet(int * vet_mod, int * vet_comp){    
    int cont = 0;
    for (int i = 0; i < 100000; i++){
        if((vet_mod[i] != 0) && (vet_mod[i] % 2) == 0){
            cont += 1;
        }
        if((vet_mod[i] != 0) && (vet_mod[i] % 5) == 0){
            cont += 1;
        }
        if(((vet_comp[i] != 0) && (vet_comp[i] % 2) != 0) && ((vet_comp[i] != 0) && (vet_comp[i] % 5) != 0)){
            if(vet_mod[i] == 0){
                cont += 1;            
            }        
        }
    }
    if (cont >= 1){
        printf("Deu ruim ai...\n");
        printf("%d\n", cont);
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
        if((num[number] % 2) == 0){
            num[number] = 0; 
        }
    }

}

void *remove5(void *arg){
    int *num = arg;
    for (int i =0; i < 100000; i++){
        int number = i - 99999;
        number = number * (-1);
        if((num[number] % 5) == 0){
            num[number] = 0; 
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
    int vetor_modificado[100000], vetor_completo[100000];
    for (int i = 0; i < 100000; i++){
        int num = rand()%100;
        while (num == 0){
            num = rand()%100;
        }
        vetor_modificado[i] = num;
        vetor_completo[i] = num;
    }
/*      for (int i = 0; i < 100000; i++){
        printf("%d ", vetor_modificado[i]);
      }  
*/
    pthread_t thread_par, thread_5;
    pthread_create(&(thread_par), NULL, removepar, vetor_modificado);
    pthread_create(&(thread_5), NULL, remove5, vetor_modificado);
    pthread_join((thread_par),NULL);
    pthread_join((thread_5),NULL);

/*      for (int i = 0; i < 100000; i++){
        printf("%d ", vetor_modificado[i]);
      }  
*/
    avalia_vet(vetor_modificado, vetor_completo);    
}

void part2_semaphore(){
    int vetor_modificado[100000], vetor_completo[100000];
    for (int i = 0; i < 100000; i++){
        int num = rand()%100;
        while (num == 0){
            num = rand()%100;
        }
        vetor_modificado[i] = num;
        vetor_completo[i] = num;
    }
/*      for (int i = 0; i < 100000; i++){
        printf("%d ", vetor_modificado[i]);
      }  
*/
    pthread_t thread_par_semaphore,thread_5_semaphore ;
    pthread_create(&(thread_par_semaphore), NULL, removepar_semaphore, vetor_modificado);
    pthread_create(&(thread_5_semaphore), NULL, remove5_semaphore, vetor_modificado);
    pthread_join((thread_par_semaphore),NULL);
    pthread_join((thread_5_semaphore),NULL);
    printf("\n");
/*      for (int i = 0; i < 100000; i++){
        printf("%d ", vetor_modificado[i]);
      }  
*/
    avalia_vet(vetor_modificado, vetor_completo);
}

void part2(){
    int vetor_modificado[100000], vetor_completo[100000];
    for (int i = 0; i < 100000; i++){
        int num = rand()%100;
        while (num == 0){
            num = rand()%100;
        }
        vetor_modificado[i] = num;
        vetor_completo[i] = num;
    }
    removepar(vetor_modificado);
    remove5(vetor_modificado);
  
    avalia_vet(vetor_modificado, vetor_completo);
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

void EX03(){
    clock_t t1;
    t1 = clock();
    int vetor_modificado[100000], vetor_completo[100000];
    int shm_id;
    char* shm_addr;
    char* shm_addr_ro;
    shm_id = shmget(100, (2*sizeof(vetor_modificado[100000])), IPC_CREAT | IPC_EXCL | 0600);
    shm_addr = shmat(shm_id, NULL,0);

    typedef struct{
        int vet_mod[100000];
        int vet_comp[100000];   
    }vetores;
    int* vetores_num;
    struct vetores* vets;
    vetores_num = (int *) shm_addr;
    //*vetores_num = 0;
    //vets = (struct vetores*) ((void*)shm_addr+(sizeof(int)));
    
    
    for (int i = 0; i < 100000; i++){
        int num = rand()%100;
        while (num == 0){
            num = rand()%100;
        }
        vetor_modificado[i] = num;
        vetor_completo[i] = num;
        vets->vet_mod[i] = num;
        //vets[0].vet_comp[i] = num;
    }
   
    pid_t child_pid;
    int child_status;
    child_pid = fork();
   
    switch (child_pid){
        case -1:
            perror("fork");
            exit(1);
        case 0:
            remove5(vetor_modificado);
            
            exit(0);
        default:
            //printf("eae antes\n"); faz primeiro de tudo
            //remove5(vetor_modificado);
            wait(&child_status); 
            removepar(vetor_modificado);
            avalia_vet(vetor_modificado, vetor_completo);
    
            //printf("eae depois\n"); faz quando acabar processo filho  
            
    }
    t1 = clock() - t1;
    printf("com processos %lf ms\n", ((double)t1)/((CLOCKS_PER_SEC/1000)));
}

int main(void){
    //EX01();
    //EX02();
    EX03();
}
    
