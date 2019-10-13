#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

    int n_terms, term_1, term_2, term_next, count_terms;

    //Get numbers of terms of Fibonacci sequence to display
    printf("How many terms of the Fibonacci sequence do you want to display?\n>>> ");
    scanf("%d", &n_terms);

    //Make sure number of terms is > or = to 2
    if (n_terms < 2)
    {
        printf("Number of terms must be greater or equal to 2. (%d < 2)", n_terms);
    }
    else
    {
        //Initialize term counters at 0 and first terms always 0 and 1
        count_terms = 0;
        term_1 = 0;
        term_2 = 1;

        //Display sequence
        printf("Fibonacci sequence of %d terms: ", n_terms);

        //Loop until whole sequence is displayed
        for (count_terms; count_terms < n_terms; ++count_terms)
        {
            printf("%d, ", term_1);

            //Compute next term
            term_next = term_1 + term_2;

            //Update term 1 and term 2
            term_1 = term_2;
            term_2 = term_next;
        }
    }

    return 0;
}
