#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

sem_t spoons[5];
int consuming[5];
sem_t sem_lock;
sem_t bowl;

void consumption_tally(int philosopher_id);

void spoon_leave(int philosopher_id)
{
    sem_wait(&sem_lock);
    consuming[philosopher_id] = 0;
    printf("The philosopher seated at %d has finished consuming his meal.\n", philosopher_id);
    consumption_tally((philosopher_id + 1) % 5);
    consumption_tally((philosopher_id+ 4) % 5);
    sem_post(&sem_lock);
    sem_post(&bowl);
}

void consumption_tally(int philosopher_id)
{
    int condition=consuming[(philosopher_id + 1) % 5] != 1 && consuming[(philosopher_id + 4) % 5] != 1;
    if (condition)
    {
        consuming[philosopher_id] = 1;
        sleep(2);
        
        printf("The philosopher seated at %d picks up the spoons adjacent to him.\n", philosopher_id);

        sem_post(&spoons[philosopher_id]);
    }
}

void *phil_eat_attempt(void *ptr)
{
    while (1)
    {
        sleep(1);
        sem_wait(&sem_lock);
        printf("The philosopher seated at %d is trying to consume his meal.\n", *(int *)ptr);
        consumption_tally(*(int *)ptr);
        sem_post(&sem_lock);
        sem_wait(&spoons[*(int *)ptr]);
        sleep(1);
        sem_wait(&bowl);
        printf("The philosopher seated at %d picks up a bowl to consume his meal from.\n", *(int *)ptr);
        printf("The philosopher seated at %d is consuming his meal.\n", *(int *)ptr);
        sleep(1);
        spoon_leave(*(int *)ptr);
        sleep(2);
    }
}

int main()
{
    int phil_no[5]={0,1,2,3,4};
    pthread_t phil_ids[5];
    sem_init(&bowl,0,2);
    sem_init(&sem_lock, 0, 1);
    int j = 0;
    while (j < 5)
    {
        sem_init(&spoons[j], 0, 0);
        j++;
    }
    j=0;
    while (j<5)
    {
        pthread_create(&phil_ids[j], NULL, phil_eat_attempt, &phil_no[j]);
        j++;
    }
    j=0;
    while (j<5)
    {
        pthread_join(phil_ids[j], NULL);
        j++;
    }
}