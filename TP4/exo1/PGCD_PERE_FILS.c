#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

int get_rest(int num_1, int num_2)
{
    return num_1 - (num_2 * (num_1/num_2));
}

int GetPGCD (int num_1, int num_2)
{
    int rest;

    //Check if num 2 is divisor of num 1
    if (num_1 % num_2 == 0)
    {
        /*Basic case*/
        return num_2;
    }

    /* Recursive case 

    Num 1 greater than num 2 */
    else if (num_1 > num_2)
    {
        //get the highest common divisor possible based on rest of division
        rest = get_rest(num_1, num_2);
        return GetPGCD(num_2, rest);
    }

    //Num 2 greater than num 1
    else
    {
        //get the highest common divisor possible based on rest of division
        rest = get_rest(num_2, num_1);
        return GetPGCD(num_1, rest);
    }
}


int create_process(void) {
    int n;

    //Loop until a fork can be created
    do
    {
        n = fork();
    }

    while ((n == -1) && (errno == EAGAIN));

    return n;
}


int main(int argc, char const *argv[])
{
    int num_1, num_2, pgcd;

    //Get numbers
    printf("Insert first number:\n>>> ");
    scanf("%d", &num_1);
    printf("Insert second number:\n>>> ");
    scanf("%d", &num_2);

    //initialize pgcd at 0
    pgcd = 0;
    int n = create_process();
    
    switch (n)
    {
        //Error case
        case -1:
            perror("fork");
            return EXIT_FAILURE;

        /*Son case
        Get PGCD of numbers*/
        case 0:

            //Make sure there is no 0
            if (num_1 == 0 || num_2 == 0)
            {
                printf("One of the number is equal to 0, no pgcd possible.");
                
                //Error return 1 and terminate program
                return 1;
            }
            else
            {
                pgcd = GetPGCD(num_1, num_2);
            }

            //Display PGCD
            printf("The GCD of %d and %d is: %d\n", num_1, num_2, pgcd);
            printf("Son is done.\n");
            printf("Son's pid is %d\n", getpid());
            break;

        /*father Case*/
        default:
        
            wait(NULL);
            printf("Dad is done.\n");
            printf("Dad's pid is %d\n", getpid());
            break;
    }

    return 0;
}
