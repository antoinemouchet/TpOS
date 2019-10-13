#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char const *argv[])
{
    int num_1, num_2, divisor;
    //get numbers from user
    printf("Insert first number:\n>>> ");
    scanf("%d", &num_1);
    printf("Insert second number:\n>>> ");
    scanf("%d", &num_2);

    /* Check numbers are different from 0
    Get PGCD if true */
    if (num_1 != 0 && num_2 != 0)
    {
        divisor = pgcd(num_1, num_2);
        printf("The PGCD of %d and %d is: %d\n", num_1, num_2, divisor);
    }

    else
    {
        printf("One of the number is 0. No PGCD available.");
    }

    scanf("%d", &num_2);
    return 0;
}