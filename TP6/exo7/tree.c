#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
#include <fcntl.h> 
#include <errno.h>
#include <dirent.h>
#include <string.h>

int main(void)
{
    // Set directory
    DIR *initDir = opendir("/proc");

    // Structure for directory
    struct dirent *directory;

    // Pid's and file descriptor
    int pid, fd;
    char path[256];
    char displayInfo[3];

    // for each subfolder of /proc
    while ((directory = readdir(initDir)) != NULL)
    {
        // Change pid to int and store pid number into display informations
        pid = atoi(directory->d_name);
        displayInfo[0] = directory->d_name;
        
        // Get path of status file
        sprintf(path, "/initDir/%d/status", pid);
        // Open file
        fd = open(path, O_RDONLY);

        // Initialize line
        char *line = NULL;
        // Initialize return value of getline and 
        int read, len;
        // Loop on every line
        while ((read = getline(&line, &len, fd)) != -1)
        {
            // Check if line with command name
            if (strstr(line, "Name:"))
            {
                strcpy(displayInfo[2], strtok(line, "Name:"));
            }
            // Check if line with PPID
            else if(strstr(line, "PPID:"))
            {
                strcpy(displayInfo[1], strtok(line, "PPID:"));
            }
            printf("%s", line);
        }
        // Free the line
        free(line);

        // Display result
        printf("- PID: %d  \tPPID: %d  \tCOMMAND: %s\n", displayInfo[0], displayInfo[1], displayInfo[2]);
        // Close file
        close(fd);
    }
    // Close directory
    closedir(initDir);

    return 0;
}