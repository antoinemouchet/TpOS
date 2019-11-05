#include <stdio.h>
#include <stdlib.h>
//#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>


int main(int argc, char const *argv[])
{
    int  id, m, n, remember_me, division, start_value, end_value, total;

    int identificator[500];

    //get number to sum to
    printf("Write an int.\n");
    scanf("%d", &n);

    //Get the number of child process
    printf("Write the number of son, it must be an int.\n");
    scanf("%d", &m);

    id = 0;
    start_value = 0;
    end_value = 0;
    division = n/m;
    total = 0;

    //looping to create sons
    for (int i = 0; i <= m && id == 0; i++)
    {   
        // Choosing right values for the son
        
        // Get last int used by the son (or 0 at first)
        start_value = end_value;
        
        // Last son won't be equal to the other sometimes
        if (i == m)
            end_value = n;
        else
        {
            // add to be equal
            end_value += division;
        }
        
        identificator[i] = fork();

        //Son case
        if (identificator[i] == 0)
        {
            remember_me = i;
            id = 1;
        }
        
        //Error case
        else if (identificator[i] < 0)
        {
            perror("There was an error generating the process: ");
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
            result = 0;
            start_value++;

            //add integer
            for (start_value; start_value <= end_value; start_value++)
            {
                result += start_value;
            }
            //send result to the father
            sigqueue(getppid(),0, result);
            
            break;
        
        //father case
        default:
            for (int i = 0; i <= m; i++)
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
