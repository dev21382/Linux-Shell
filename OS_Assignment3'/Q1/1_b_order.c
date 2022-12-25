#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#define occupied 1

int spoons[5];
int bowl;

char *right="right";
char *left="left";

void pickup_spoon(char* direction,int philosopher_id)
{
  if(direction[0]=='r')
  {
    printf("The philosopher seated at %d picks up the right spoon.\n",
               philosopher_id);
  }
  else
  {
    printf("The philosopher seated at %d picks up the left spoon.\n",
               philosopher_id);
  }
}
void bowllock()
{bowl++;}

void in_lock(int n) 
{
  switch (spoons[n]) 
  {
  case 1:
    spoons[n] = 0;
    break;
  default:
    while (!spoons[n]) 
    {
    };
  }
}

void bowl_l()
{
    if (bowl > 0)
    {bowl--;}
    else if (bowl<=0)
    {while (bowl <= 0)
        {}
    }
}

void out_of_lock(int n)
{spoons[n] = 1;}

void functioneat()
{}


void *phil_eat_attempt(void *n)
{
    int philosopher_id = *(int *)n;
    while (1)
    {
        switch (philosopher_id){
            case 4:
            printf("\n The philospher seated at %d is trying to eat his meal", philosopher_id);
            bowl_l();
            printf("\nThe philospher seated at %d  picks up a bowl", philosopher_id);

            in_lock((philosopher_id + 1) % 5);
            pickup_spoon(right,philosopher_id);
            in_lock(philosopher_id);
            pickup_spoon(left,philosopher_id);
            printf("\nThe philospher seated at %d is eating his meal", philosopher_id);
            functioneat();
            printf("\n The philospher seated at %d has finished eating his meal", philosopher_id);
            bowllock();
            out_of_lock(philosopher_id);
            out_of_lock((philosopher_id + 1) % 5);
            break;
        
        default:
            printf("\nThe philospher seated at %d is trying to eat his meal", philosopher_id);
            bowl_l();
            printf("\nThe philospher seated at %d  picks up a bowl", philosopher_id);
            in_lock(philosopher_id);
            pickup_spoon(left,philosopher_id);
            in_lock((philosopher_id + 1) % 5);
            pickup_spoon(right,philosopher_id);
            printf("\nThe philospher seated at %d is eating his meal", philosopher_id);
            functioneat();
            printf("\nThe philospher seated at %d has finished eating his meal", philosopher_id);
            bowllock();
            out_of_lock((philosopher_id + 1) % 5);
            out_of_lock(philosopher_id);
        
    }
}
}

int main()
{
    int phil_ids[5]={0,1,2,3,4};
    pthread_t philsopher_threads[5];
    bowl = 2;
    int j = 0;
    int id=0;
    while (j < 5)
    {
        spoons[j] = occupied;
        phil_ids[id] = id;
        pthread_create(&philsopher_threads[j], NULL, phil_eat_attempt, (void *)&phil_ids[j]);
        j+=1;
        id+=1;
    }
    int i=0;
    while (i<5)
    {
        pthread_join(philsopher_threads[i], NULL);
        i+=1;
    }
}