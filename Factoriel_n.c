#include <stdio.h>
#include <stdlib.h>

int factorial(int number){

    if (number == 0 || number == 1){
        return 1;
    }

    else{
        return number * factorial(number - 1);
    }

}

int main(int argc, char const *argv[])
{

    int number, result;

    //Get number from user
    printf("Insert a number:\n>>> ");
    scanf("%d", &number);

    //Get factorial of number
    result = factorial(number);

    //Display result
    printf("The factorial of %d is: %d", number, result);

    return 0;
}
