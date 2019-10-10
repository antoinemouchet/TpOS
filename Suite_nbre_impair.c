#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int number, parity, result;
    //Get number from user
    printf("Saisissez un nombre:\n>>> ");
    scanf("%d", &number);

    /* Check if number is odd or even*/
    if (number % 2 == 0){
        parity = 1;
    }
    else{
        parity = 0;
    }

    while (number > 0){
        //If number was even, make it an odd
        if (parity){
            number -= 1;
        }

        //Increase result
        result += number;
        //Decrease number
        number -= 2;
    }

    printf("The result is:\n>>> %d", result);

    return 0;
}
