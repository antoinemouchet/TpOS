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
    char *buffer = malloc(BUF_SIZE);
    char *buffercopy = buffer;

    // Separator pointer and command name
    char *separation = NULL, *command = NULL;

    // Loop to get every subfolder of /proc
    while ((dirStruct = readdir(directory)) != NULL)
    {
        // Convert pid
        pid = atoi(dirStruct->d_name);
    
        // Update path
        sprintf(path, "/proc/%d/stat", pid);

        // Open file
        fileDescriptor = open(path, O_RDONLY);

        // Get stats from file
        struct stat statfile;
        stat(path, &statfile);

        // Get size of file
        int fileSize = statfile.st_size;

        read(fileDescriptor, buffer, fileSize);
        // init buffer copy to the start of buffer
        buffercopy = buffer;

        // Loop to get every information needed
        for (int i = 0; i < 4; i++)
        {
            // split the string
            separation = strsep(&buffercopy, " ");
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
        printf("%s (command) has pid: %d and its ppid is: %d\n", command, pid, ppid);
        // close the file
        close(fileDescriptor);
    }
    // Check if there is something in the buffer, clear it if yes
    if (buffer)
    {
        free(buffer);
    }
    // Close directory
    closedir(directory);

    return 0;
}