#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
<<<<<<< HEAD
int is_divisor(int num_1, int num_2){
    /* Function to test if num 2 is a divisor of num 1
    by using the result of the modulo.*/
    
    if (num_1 % num_2 == 0){
        return 1;
    }

    else {
        return 0;
    }

    return 0;
}
pid_t create_process(void) {
    int pid;
    do {
        pid = fork()
    } while ((pid == -1) && (errno == EAGAIN))
    return pid;
}
int main(int argc, char const *argv[])
{
    int num_1, num_2, num_3, divider_n12, divider_n13, divider_n21, divider_n23, pgcd;

    //Get numbers
    printf("Insérez le premier nombre:\n>>> ");
    scanf("%d", &num_1);
    printf("Insérez le second nombre:\n>>> ");
=======

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
>>>>>>> 323056dc38ac4e373d4c72d1aff207082c3b36ef
    scanf("%d", &num_2);

    //initialize pgcd at 0
    pgcd = 0;
<<<<<<< HEAD
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
    
    /*Num 3 is equal to the smallest between num 1 and num 2
    if num 1 and num 2 are different */
    if (num_1 == num_2){
        pgcd = num_1;
    }
    else if (num_1 > num_2){
        num_3 = num_2;
    }
    else{
        num_3 = num_1;
    }

    //Loop until pgcd found
    while (pgcd == 0){

        if (num_1 == num_3 || num_2 == num_3){
            //Num 1 bigger than num 2
            if (num_1 > num_2){
                //Check if n2 is a divider of n1
                divider_n12 = is_divisor(num_1, num_2);

                if (divider_n12){
                    pgcd = num_2;
                }
            }
            //Num2 bigger than num 1
            else if (num_2 > num_1){
                //Check if num 1 is a divisor of num 2
                divider_n21 = is_divisor(num_2, num_1);
                if (divider_n21){
                    pgcd = num_1;
                }
            }
        }

        else {
            //Check if num 3 is a divisor of num1 and num 2
            divider_n13 = is_divisor(num_1, num_3);
            divider_n23 = is_divisor(num_2, num_3);

            if (divider_n13 && divider_n23){
                pgcd = num_3;
            }
        }

        //Decrease the value of possible pgcd
        num_3 -= 1;
    }

    //Display PGCD
    printf("Le PGCD de %d et %d est: %d\n", num_1, num_2, pgcd);
    default:
    /*father Case*/
    wait(NULL);
        break;
    }
    return EXIT_SUCCESS;
=======
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
>>>>>>> 323056dc38ac4e373d4c72d1aff207082c3b36ef
}
