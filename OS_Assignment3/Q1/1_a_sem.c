#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

int phil_no[5];
sem_t spoon[5];
int consuming[5];
sem_t sem_lock;

void consumption_tally(int philosopher_id);

void *phil_eat_attempt(void *ptr)
{
    while (1)
    {
        sleep(1);
        sem_wait(&sem_lock);
        printf("The philosopher seated at %d is trying to consume his meal.\n", *(int *)ptr);
        consumption_tally(*(int *)ptr);
        sem_post(&sem_lock);
        sem_wait(&spoon[*(int *)ptr]);
        sleep(1);
        sem_wait(&sem_lock);
        consuming[*(int *)ptr] = 0;
        printf("The philosopher seated at %d has finished consuming his meal.\n", *(int *)ptr);
        consumption_tally((*(int *)ptr + 1) % 5);
        consumption_tally((*(int *)ptr + 4) % 5);
        sem_post(&sem_lock);
    }
}

void consumption_tally(int philosopher_id)
{
    int condition=consuming[(philosopher_id + 1) % 5] != 1 && consuming[(philosopher_id + 4) % 5] != 1;
    if (condition)
    {
        consuming[philosopher_id] = 1;
        sleep(1);
        printf("The philosopher seated at %d picks up the spoons adjacent to him.\n", philosopher_id);
        printf("The philosopher seated at %d is consuming his meal.\n", philosopher_id);
        sem_post(&spoon[philosopher_id]);
    }
}

int main()
{
    sem_init(&sem_lock, 0, 1);

    pthread_t phil[5];
    
    for(int i=0;i<5;i++){
        sem_init(&spoon[i],0,0);
    }
    

    for(int i=0;i<5;i++)
    {
        phil_no[i]=i;
    }
    
    for(int i=0;i<5;i++){
        pthread_create(&phil[i], NULL, phil_eat_attempt, &phil_no[i]);
    }

    int i=0;
    while(i<5){
        pthread_join(phil[i], NULL);
        i++;
    }    
}