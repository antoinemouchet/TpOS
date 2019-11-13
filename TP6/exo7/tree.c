#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include<unistd.h>
#include <fcntl.h> 
#include <errno.h>
#include <dirent.h>


#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    DIR *directory = opendir("/proc");

    // Structure of directory
    struct dirent *dirStruct;
    // pid, ppid, and file descriptor 
    int pid, ppid, fileDescriptor;

    // Path string
    char path[256];

    // Buffers
    char *buffer = malloc(BUF_SIZE* sizeof(char));
    char *copyBuffer = buffer;

    // Separator pointer and command name
    char *separation = NULL, *command = NULL;

    // Loop to get every subfolder of /proc
    while ((dirStruct = readdir(directory)) != NULL)
    {
        // Convert pid
        pid = atoi(dirStruct->d_name);

        // Make sure we're looping on process folder
        if (pid > 0)
        {
            // Update path
            sprintf(path, "/proc/%d/stat", pid);

            // Open file
            fileDescriptor = open(path, O_RDONLY);
            
            // Get infos on file
            struct stat statfile;
            stat(path, &statfile);

            // Read file
            read(fileDescriptor, buffer, statfile.st_size);
            // Set copy of buffer to the start of buffer
            copyBuffer = buffer;

            // Loop to get every information needed
            for (int i = 0; i < 4; i++)
            {
                // split the string
                separation = strsep(&copyBuffer, " ");
                // Second split is the commande name
                if (i == 1)
                {
                    command = separation;
                }
                // Fourth split is the ppid
                if (i == 3)
                {
                    ppid = atoi(separation);
                }
            }
            // Display result
            printf("%s (command) had pid: %d and its ppid is: %d\n", command, pid, ppid);
            // close the file
            close(fileDescriptor);
        }
    }
    // Free memory allocated to buffer
    free(buffer);
    // Close directory
    closedir(directory);

    return 0;
}