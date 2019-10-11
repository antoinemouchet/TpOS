#include <stdio.h>
#include <stdlib.h>

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
    return 0;
}
