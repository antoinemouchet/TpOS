#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define NB_PHILO 5
#define FREE 0
#define TAKEN 1

pthread_mutex_t  table;


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

}

void freeForks(int philId)
{

}

void think()
{
    printf("I'm thinking about something.\n");
}

void* philAction(int philId)
{
    while (1)
    {
        think();
        lock(table);

    }
    
}

int main(int argc, char const *argv[])
{
    // Initialize return value of mutex creation
    int mutRet;

    pthread_t philosopheIds[NB_PHILO];

    // Create mutex
    mutRet = pthread_mutex_init(&table, NULL);

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
        // Create thread with function philAction and argument i
        int threadRet = pthread_create(&(philosopheIds[i]), NULL, &philAction, &i);

        // Check that each thread is correctly created
        if (threadRet != 0)
        {
            // Error
            // strerror returns a string describing the error
            strerror(threadRet);
            return 1;
        }
        

    }
    
    

    return 0;
}


