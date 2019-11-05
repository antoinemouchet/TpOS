#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>


int main(int argc, char const *argv[])
{
    int i, id, m, n, remember_me, division, start_value, end_value, total;
    printf("Write an int");
    scanf("%d", n);
    printf("Write the number of son, it must be an int");
    scanf("%d", m);
    id = 0;
    i = 0;
    start_value = 0;
    end_value = 0;
    division = n/m;
    total = 0
    //looping to create sons
    for ( i = 0; i <= m && id == 0; i++)
    {   
        //choosing right values for the son
        
        //get last int used by the son (or 0 at first)
        start_value = end_value;
        
        //last son won't be equal to the other sometimes
        if (i == m)
            end_value = n;
        else
        {
            // add to be equal
            end_value += division
        }
        
        identificator[i] = fork();

        //Son case
        if (identificator[i] == 0)
        {
            remember_me = i 
            id = 1;
        }
        
        //Error case
        else if (identificator[i] < 0)
        {
            printf("there was an error generating the process");
            id = -1;
            return 1;
        }
        

    }

    //Add integer 
    
    switch (remember_me)
    {
        //son case    
        case 0:
            int result;
            result = 0
            start_value++;

            //add integer
            for ( start_value; start_value <= end_value; start_value++)
            {
                result += start_value;
            }
            //send result to the father
            sigqueue(getppid(),0, result);
            
            break;
        
        //father case
        default:
            for (i = 0; i <= m; i++)
            {
                //waiting the son's result
                wait(NULL);
                total += result; 
            }
            //TO COMPLETE

            break;
    }
    
    return 0;
}
