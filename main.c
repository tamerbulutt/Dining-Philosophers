#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

sem_t chopSticks[5];
sem_t *lock;
int philosopherPosition[5];

void *philosopherEating(void *arg){
    int i = (int)arg;
    
    printf("%d. Filozof dusunuyor...\n",philosopherPosition[i]);
    
    sem_wait(lock);
    sem_wait(&chopSticks[philosopherPosition[i]]);
    sem_wait(&chopSticks[(philosopherPosition[i]+1) % 5]);
    
    printf("%d. Filozof suan yemek yiyor...\n", i);
	printf("%d.Filozofun karni doydu, artik dusunuyor...\n",i);
	
    sem_post(&chopSticks[philosopherPosition[i]]);
    sem_post(&chopSticks[(philosopherPosition[i]+1) % 5]);
    sem_post(lock);

    printf("%d. Filozof dusunuyor\n",philosopherPosition[i]);
    pthread_exit(NULL);
}

int main(){
	int chopSticksNum=5;
    pthread_t philosopher[5];
    int i;
    
    for(i=0; i<5; i++){
        sem_init(&chopSticks[i], 0, 1);
    }
    
    sem_init(lock,0,chopSticksNum-1);	
    
    for(i=0; i<5; i++){
    	philosopherPosition[i] = i;
        pthread_create(&philosopher[i], NULL, philosopherEating, (void*)i);
    }
    
    for(i=0; i<5; i++){
        pthread_join(philosopher[i], NULL);
    }
    
    return 0;
}


