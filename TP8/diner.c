#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NB_PHILO 5
#define FREE 0
#define TAKEN 1

// Global lock
pthread_mutex_t  eating;

// Global array for forks status
int forkStatus[NB_PHILO];

// Get id of the left fork for a philosophe
int leftFork(int philId)
{
    // The id of the fork on the left is one more than phil id
    return ((philId + 1) % NB_PHILO);
}

// Get id of the right fork for a philosophe
int rightFork(int philId)
{
    return (philId % NB_PHILO);
}

void takeForks(int philId)
{
    // Update status of forks, "giving" them to the philosophe
    forkStatus[leftFork(philId)] = TAKEN;
    forkStatus[rightFork(philId)] = TAKEN;
}

void freeForks(int philId)
{
    // Update status of forks, making them free
    forkStatus[leftFork(philId)] = FREE;
    forkStatus[rightFork(philId)] = FREE;
}

void think(int philID)
{
    // Display thinking message
    printf("I'm thinking about something. (Philosophe: %d)\n", philID);
}

void eat(int philID)
{
    // Check if philosophe has the forks in the hands
    if (forkStatus[rightFork(philID)] == TAKEN && forkStatus[leftFork(philID)] == TAKEN)
    {
        // Display eating message
        printf("%d is eating.\n", philID);
    }
}

void * philAction(void * philID)
{
    int philId = * ((int *) philID);
    // Infinite loop
    while (1)
    {
        // Thinking phase
        think(philId);

        // Critical zone
        pthread_mutex_lock(&eating);

        // Take forks to eat
        takeForks(philId);
        // Eat
        eat(philId);
        // Release forks 
        freeForks(philId);

        // End of critical zone
        pthread_mutex_unlock(&eating);
        pthread_exit(NULL);
    }
}

int main(int argc, char const *argv[])
{
    // Initialize return value of mutex creation
    int mutRet;

    pthread_t philosopheIds[NB_PHILO];

    // Create mutex
    mutRet = pthread_mutex_init(&eating, NULL);

    // Check that mutex was correctly initialized
    if (mutRet != 0)
    {
        // Errror
        printf("Error generating mutex.\n");
        return 1;
    }
    
    // Loop until all philos are created
    for (int i = 0; i < NB_PHILO; i++)
    {
        int * idPhilo = (int *) malloc(sizeof(int));
        * idPhilo = i;
        // Create thread with function philAction and argument i
        int threadRet = pthread_create(&(philosopheIds[i]), NULL, philAction, idPhilo);

        // Check that each thread is correctly created
        if (threadRet != 0)
        {
            // Error
            printf("Error creating thread.\n");
            return 1;
        }
    }
    // Loop to end all threads
    for (int i = 0; i < NB_PHILO; i++)
    {
        pthread_join(philosopheIds[i], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&eating);
    
    return 0;
}
