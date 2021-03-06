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


sem_t S; // Variavel Semaforo.

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

    pthread_t thread_par, thread_5;
    pthread_create(&(thread_par), NULL, removepar, vetor_modificado);
    pthread_create(&(thread_5), NULL, remove5, vetor_modificado);
    pthread_join((thread_par),NULL);
    pthread_join((thread_5),NULL);

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
    pthread_t thread_par_semaphore,thread_5_semaphore ;
    pthread_create(&(thread_par_semaphore), NULL, removepar_semaphore, vetor_modificado);
    pthread_create(&(thread_5_semaphore), NULL, remove5_semaphore, vetor_modificado);
    pthread_join((thread_par_semaphore),NULL);
    pthread_join((thread_5_semaphore),NULL);
    printf("\n");

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

    part1(); // Exibe 'N' Threads com sua respectiva ID

    printf("\n");
}

void EX02(){

    clock_t t1,t2,t3; // Pegar tempo de execucao em Ms.
    sem_init(&S, 0,1);
    t1 = clock();

    part2_semaphore(); // Completa e remove do vetor com Semaforo.

    t1 = clock() - t1;
    printf("Tempo do EX com semaforo: %lf ms\n", ((double)t1)/((CLOCKS_PER_SEC/1000)));
    t2 = clock();

    part2_thread();  // Completa e remove do vetor com Threads.

    t2 = clock() - t2;  
    printf("Tempo do EX sem semaforo e com thread: %lf ms\n", ((double)t2)/((CLOCKS_PER_SEC/1000)));
    t3 = clock();

    part2(); // Completa e remove do vetor sem nada.

    t3 = clock() - t3;
    printf("Tempo do EX sem threads nem semaforo: %lf ms\n", ((double)t3)/((CLOCKS_PER_SEC/1000)));
    printf("\n");
}

void EX03(){
    clock_t t1;
    t1 = clock();
    int fd1[2]; // Pipe 1
    int fd2[2]; // Pipe 2
    pid_t child_pid;
    int child_status;
    child_pid = fork();
   
    switch (child_pid){

        case -1:

            //Em caso de erro do processo.

            perror("fork");
            exit(1);

        case 0:

            //Executa quando o processo Pai chegar no Wait.

            close(fd1[1]);
            int* vets2[100000];
            read(fd1[0], vets2, sizeof(vets2)+1);
            remove5(vets2);
            close(fd1[0]);
            write(fd1[1], vets2, sizeof(vets2)+1);
            close(fd1[1]);
            
            exit(0); //Termina de executar e deixa o processo Pai seguir.

        default:

            //Executa antes do processo filho.

            close(fd1[0]);
            close(fd2[0]);
            int vets_mod[100000];
            int vets_comp[100000];
            for (int i = 0; i < 100000; i++){
                int num = rand()%100;
                while (num == 0){
                    num = rand()%100;
                }
            vets_mod[i] = num;
            vets_comp[i] = num;
            }            
            
            write(fd2[1], vets_comp, sizeof(vets_comp)+1);
            write(fd1[1], vets_mod, sizeof(vets_mod)+1);
            close(fd1[1]);
            close(fd2[1]);
            
            wait(&child_status);  // Executa quando o processo filho acabar.
            
            close(fd1[1]);
            close(fd2[1]);
            int vets3[100000];
            int vets_comp2[100000];
            read(fd1[0], vets3, sizeof(vets3)+1);
            read(fd2[0], vets_comp2, sizeof(vets_comp2)+1);

            removepar(vets3);

            close(fd1[0]);
            close(fd2[0]);
            write(fd1[1], vets3, sizeof(vets3)+1);
            write(fd2[1], vets_comp2, sizeof(vets_comp2)+1);
            close(fd1[1]);
            close(fd2[1]);

            avalia_vet(vets3,vets_comp2);  
    }
    t1 = clock() - t1; //Pega o tempo em Milessegundos (ms), desde o inicio do EX03.

    printf("com processos %lf ms\n", ((double)t1)/((CLOCKS_PER_SEC/1000)));
}

void main(void){

    /*
        Rode um Exercicio por vez.
    */

    //EX01();
    //EX02();
    //EX03();
}
