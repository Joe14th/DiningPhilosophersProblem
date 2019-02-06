#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t right;
pthread_mutex_t left;

FILE *fp;

void putDownChopsticks(int threadIndex){
    pthread_mutex_unlock(&right);
    pthread_mutex_unlock(&left);
    pthread_exit(NULL);
}

void eating(int threadIndex){
    srandom(time(NULL));
    long n;
    do{
        n = random();
    }while( n>500 || n<1);
    
    usleep(n);
    //printf("eating!!\n");
    fprintf(fp, "Philosopher %d is eating\n", threadIndex);
}

void pickUpChopsticks(int threadIndex){
    pthread_mutex_lock(&left);
    pthread_mutex_lock(&right);
}

void thinking(){
    srandom(time(NULL));
    long n;
    do{
        n = random();
    }while( n>500 || n<1);
    
    usleep(n);
    //printf("random number: %ld\n", n);
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
    //will pass the index of threads to the 
    //thread function PhilosopherThread();    
    int i;
    pthread_t tid[nthreads];
    int threads[nthreads];

    for(i = 0; i < nthreads; i++){
        threads[i]=i;
        pthread_create(&tid[i], NULL, PhilosopherThread, &threads[i]);
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
    
    if(pthread_mutex_init(&left, NULL) != 0){
        printf("\nMutex init has failed\n");
        return 1;
    }
    if(pthread_mutex_init(&right, NULL)!= 0){
        printf("\nMutex init has failed\n");
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
