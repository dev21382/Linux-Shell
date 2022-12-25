#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int spoons[5];

char *right="right";
char *left="left";

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

void out_of_lock(int n) 
{ 
  spoons[n] = 1; 
}

void eat_try(int philosopher_id)
{
  printf("The philospher seated at %d is trying to eat his meal.\n",
               philosopher_id);
}

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

void *phil_eat_attempt(void *n) 
{
  int philosopher_id = *(int *)n;
  while (1) 
  {
    switch (philosopher_id) 
    {
      case 4:
        eat_try(philosopher_id);
        in_lock((philosopher_id + 1) % 5);
        pickup_spoon(right,philosopher_id);
        in_lock(philosopher_id);
        pickup_spoon(left,philosopher_id);
        printf("The philospher seated at %d is eating from his bowl.\n",
               philosopher_id);
        printf("In the midst of eating his meal.\n");
        sleep(1);
        printf("The philospher seated at %d has finished eating his meal.\n",
               philosopher_id);
        out_of_lock(philosopher_id);
        out_of_lock((philosopher_id + 1) % 5);
        break;

      default:
        eat_try(philosopher_id);
        in_lock(philosopher_id);
        pickup_spoon(left,philosopher_id);
        in_lock((philosopher_id + 1) % 5);
        pickup_spoon(right,philosopher_id);
        printf("The philosopher seated at %d is eating from his bowl.\n",
               philosopher_id);
        printf("In the midst of eating his meal.\n");
        sleep(1);
        printf("The philospher seated at %d has finished eating his meal.\n",
               philosopher_id);
        out_of_lock((philosopher_id + 1) % 5);
        out_of_lock(philosopher_id);
    }
  }
}

int main() 
{
  pthread_t philosopher_threads[5];
  int phil_ids[5] = {0, 1, 2, 3, 4};
  
  for (int i = 0; i < 5; i++) 
  {
    spoons[i] = 1;
  }
  
  for (int j = 0; j < 5; j++) 
  {
    spoons[j] = 1;
    pthread_create(&philosopher_threads[j], NULL, phil_eat_attempt, (void *)&phil_ids[j]);
    j++;
  }

  int i = 0;
  while (i < 5) 
  {
    pthread_join(philosopher_threads[i], NULL);
    i++;
  }
  return 0;
}




