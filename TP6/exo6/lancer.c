#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h> 

#define BUF_SIZE 1024

// Fonction to check if path is a directory
int isDir(const char *path)
{
    struct stat statFile;
    stat(path, &statFile);

    // 1 if path is a directory
    return S_ISREG(statFile.st_mode);
}


int main(int argc, char* argv[])
{
    // Counter
    int  n, j;
    // Strings
    char command[BUF_SIZE] = "";
    char data[BUF_SIZE];

    // Files
    FILE* input;
    // Output file is last argument
    FILE* output = argv[argc-1];
    
    // Loop to get every argument
    for (n = 1; n < argc-1; n++) 
    {
        // String command will end at j-1
        strcat(command, argv[n]);
        strcat(command, ' ');
    }

    // Mark end of the string
    command[strlen(command)-1] = '\0';

    // Initialize path of potential command.
    // Command name is 2nd argument 
    char binPath[100];
    sprintf(binPath, "/bin/%s", argv[1]); 

    // Check if command can be executed
    int fileTest;
    fileTest = access(binPath, X_OK);

    // Supposed command is a command
    if (!fileTest)
    {
        printf("Command: %s treated successfully.\n",command);
    }
    // Command not executable
    else if (fileTest != -1)
    {
        printf("Command: %s can not be executed.\n",command);
        return 1;
    }
    else
    {
        perror("Unknow error");
    }
    
    // Launch command
    input = popen(command, 'r');
    
    // Save output to file
    int fdOut = open(argv[argc - 1], O_WRONLY|O_CREAT, S_IRWXU);
    // Write Output data into file
    write(fdOut, input, strlen(input));

    // Close files
    pclose(input);
    close(output);

    return 0;
}