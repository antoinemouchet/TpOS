#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h> 

int main(int argc, char* argv[])
{
    // Initialisation 

    // Variables
    int i, j;
    // Boards
    char command[1024] = "";
    char data[1024];
    // Pointers
    FILE* file_data_in;
    FILE* file_data_out;
    
    

    // Read command argument
    j = 0;
    for (i = 1; i < argc-1; ++i) 
    {
        // String command will end at j-1
        strcpy(&command[j], argv[i]);
        j += strlen(argv[i]);
        command[j++] = ' ';
    }
    // Mark end of the string
    command[j - 1] = '\0';

    // Test if the command exist and raise error if it doesn't
    char bin_path[100];
    sprintf(bin_path, "/bin/%s",command); 
    int file_tester;
    file_tester = access(bin_path,X_OK);

    if (file_tester==0)
    {
        // If file exist
        printf("Your command %s has been treated to the appropriate file.\n",command);
    }
    else
    {
        // if command doesn't exist
        printf("Sorry, the command %s doesn't exist \n",command);
    }
    
    // Launch command
    file_data_in = open(command, O_RDONLY);
    if (file_data_in == NULL) 
    {
        return 1;
    }

    // Save command output data
    file_data_out = open(argv[argc - 1], O_WRONLY|O_CREAT, S_IRWXU);
    while (i = read(data, sizeof(char), 1024, file_data_in)) 
    {
        write(data, sizeof(char), i, file_data_out);
    }
    // Files closing
    close(file_data_in);
    close(file_data_out);

    return 0;
}