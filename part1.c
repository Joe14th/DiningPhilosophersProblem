#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* PhilosopherThread(void* x){
    int* index = x;
    printf("This is philosopher %d\n", *index);
    return NULL;
}

void creatPhilosophers(int nthreads){    
    int i;
    pthread_t tid[nthreads];
    int threads[nthreads];

    for(i = 0; i < nthreads; i++){
        threads[i]=i;
        pthread_create(&tid[i], NULL, PhilosopherThread, &threads[i]);
    }
    
    for(i = 0; i < nthreads; i++){
        pthread_join(tid[i], NULL);
    }
    printf("%d threads have been joined successfully now\n", nthreads);
}

int main(int argc, char *argv[]){
    int nthreads = atoi(argv[1]);
    printf("Jasmine Ramirez: %d threads\n", nthreads);
    
    creatPhilosophers(nthreads);
    return 0;
}
