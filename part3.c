#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

FILE *fp;
pthread_cond_t cond;
pthread_mutex_t lock;
int pindex = 0;

void putDownChopsticks(int threadIndex){
    pindex++;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void eating(int threadIndex){
    srandom(time(NULL));
    long n;
    do{
        n = random();
    }while( n>500 || n<1);
    
    usleep(n);
    fprintf(fp, "Philosopher %d is eating\n", threadIndex);
}

void pickUpChopsticks(int threadIndex){
    pthread_mutex_trylock(&lock);
    while(pindex != threadIndex){
        pthread_cond_wait(&cond, &lock);
    }
}

void thinking(){
    srandom(time(NULL));
    long n;
    do{
        n = random();
    }while( n>500 || n<1);
    
    usleep(n);
}

void* PhilosopherThread(void* x){
    int* index = x;
    printf("This is philosopher %d\n", *index);
    
    thinking();
    pickUpChopsticks(*index);
    eating(*index);
    putDownChopsticks(*index);

    return NULL;
}

void creatPhilosophers(int nthreads){    
    int i;
    pthread_t tid[nthreads];
    int threads[nthreads];

    for(i = 0; i < nthreads; i++){
        threads[i]=i;
        //&threads[i]
        pthread_create(&tid[i], NULL, PhilosopherThread, threads+i);
    }
    
    //wait for all threads
    for(i = 0; i < nthreads; i++){
        pthread_join(tid[i], NULL);
    }
    printf("%d threads have been joined successfully now\n", nthreads);
}

int main(int argc, char *argv[]){
    int nthreads = atoi(argv[1]);
    printf("Jasmine Ramirez: %d threads\n", nthreads);
    
    if(pthread_mutex_init(&lock, NULL) != 0){
        printf("\nMutex init has failed\n");
        return 1;
    }
    if(pthread_cond_init(&cond, NULL) != 0){
        printf("\nConditional init has failed\n");
        return 1;
    }
    if((fp = fopen("../status.txt", "a")) == NULL){
        printf("\nFopen has failed\n");
        return 1;
    }

    creatPhilosophers(nthreads);

    fclose(fp);
    return 0;
}
