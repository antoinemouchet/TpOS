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

int pgcd (int num_1, int num_2)
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
        return pgcd(num_2, rest);
    }

    //Num 2 greater than num 1
    else
    {
        //get the highest common divisor possible based on rest of division
        rest = get_rest(num_2, num_1);
        return pgcd(num_1, rest);
    }
}


pid_t create_process(void) {
    int pid;

    do
    {
        pid = fork()
    }

    while ((pid == -1) && (errno == EAGAIN))

    return pid;
}


int main(int argc, char const *argv[])
{
    int num_1, num_2, num_3, divider_n12, divider_n13, divider_n21, divider_n23, pgcd;

    //Get numbers
    printf("Insérez le premier nombre:\n>>> ");
    scanf("%d", &num_1);
    printf("Insérez le second nombre:\n>>> ");
    scanf("%d", &num_2);

    //initialize pgcd at 0
    pgcd = 0;
    pid_t pid = create_process();
    
    switch (pid)
    {
    case -1:
        perror("fork");
        return EXIT_FAILURE;
        break;
    case 0:
    /*Son case*/
        if (num_1 == 0 || num_2 == 0)
    {
        printf("One of the number is equal to 0, no divisor possible.");
        return 1;
    }

    //Display PGCD
    printf("Le PGCD de %d et %d est: %d\n", num_1, num_2, pgcd);
    default:
    /*father Case*/
    wait(NULL);
        break;
    }
    return EXIT_SUCCESS;
}
