#include <stdio.h>
#include <stdlib.h>
//#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

int FinalResult = 0;
int NbKidDone = 0;

void handler(int signum, siginfo_t *info, void *ucontext)
{
    // Add computed sum to Final result
    FinalResult += info -> si_value.sival_int;

    // Display which child sent this sum
    printf("The child with pid %d sent the result: %d.\n", info -> si_pid, info -> si_value.sival_int);

    // Increase the nb of kid done by 1
    NbKidDone++;
}

int ComputeSum(int StartValue, int EndValue)
{
    // Initialize result of sum to 0
    int sum = 0;

    // Loop to get all the integers at sum
    for (int i = StartValue; i <= EndValue; i++)
    {
        // Add number to sum
        sum += i;
    }

    printf("Child with pid (%d) computed sum from %d to %d.\nThe result was: %d.\n", getpid(), StartValue, EndValue, sum);
    // Return the sum
    return sum;
}



int main(int argc, char const *argv[])
{
    int division, m, n, forkReturn, id = 0;

    struct sigaction act;
            
    // Associating a function so we use sigaction
    act.sa_sigaction = &handler;

    // Using this flag with real-time signal allow to obtain data from si_value from siginfo_t struct
    act.sa_flags = SA_SIGINFO;

    // SIGRTMIN is a real-time signal. The advantage is that they'll queue up when multiple are sent
    int success = sigaction(SIGRTMIN, &act, NULL);

    // Error while modifyinf 
    if (success == -1)
    {
        perror("An error occured: ");
        // Error
        return 1;
    }

    /* IF WE WANT TO GET INFORMATIONS DIRECTLY FROM THE COMMAND LINE USE THIS METHOD
    if (argc != 3)
    {
        printf("Wrong amount of arguments, insert the number to reach and the amount of child process to create.\n");
        // Error
        return 1;
    }
    // Convert string to integer using atoi()
    // Get number to reach.
    n = atoi(argv[1]);

    // Get number of child process to create
    m = atoi(argv[2]);
    */

    // SCANF method
    // Get number to sum to
    printf("Write an int.\n");
    scanf("%d", &n);

    // Get the number of child process
    printf("Write the number of son, it must be an int.\n");
    scanf("%d", &m);
    
   // Get division
    division = n / m;
 
    // Looping to get all sums (by creating sons)
    for (int i = 0; i < m && id == 0; i++)
    {   
        //Create a child
        forkReturn = fork();

        // Son case
        // Here we want to compute a sum
        if (forkReturn == 0)
        {
            int result;
            // Declare structure to send 
            union sigval value;

            // Check that it's not the last segment
            if (i < m - 1)
            {
                // Get the sum of each segment
                result = ComputeSum(i * division + 1, division * (i + 1));
            }

            // Last segment, get sum to last number
            else
            {
                // The sum of last segment is till n is reached
                result = ComputeSum(i * division + 1, n);
                printf("Ici? %d\n", result);
            }

            // Store result of the sum
            value.sival_int = result;

            // Get parent pid
            int parentPid = getppid();

            //Display and send informations to parent process
            printf("Child (pid: %d) sends %d to its parent (pid: %d).\n", getpid(), result, parentPid);
            sigqueue(parentPid, SIGRTMIN, value);
            
            id = 1;
            exit(0);
            
        }
        
        // Error case
        else if (forkReturn < 0)
        {
            perror("There was an error generating the process: ");
            // Make sure to leave loop
            return 1;
        }
        else
        {
            pause();
            id = 1;
        }
        
    }

    /*while (NbKidDone != m)
    {
        pause();
    }*/

    // Display final result
    if (NbKidDone == m)
    {
        printf("The sum to %d is: %d.\n", n, FinalResult);
    }

    return 0;
}
