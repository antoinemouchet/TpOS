#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
#include <fcntl.h> 
#include <errno.h>


int main(int argc, char const *argv[])
{
    // Check that correct amount of arguments was given
    if (argc != 4)
    {
        printf("Wrong amount of arguments. Please insert 3 arguments.\n");
        // Terminate with error
        return 1;
    }

    // Create third file (user has read,write and execute permission) and get its descriptor
    int newFileDescriptor = open(argv[3], O_RDWR | O_CREAT | O_APPEND, S_IRWXU);

    // Error case
    if (newFileDescriptor == -1)
    {
        // Display Error
        perror("Error encountered: ");

        // Error with the file
        return 1;
    }
    

    // Loop to add the 2 first files into the third
    for (int i = 0; i < 2; i++)
    {
       // Get stats from file
        struct stat statfile;
        stat(argv[i], &statfile);
        
        // Get size of file
        off_t fileSize = statfile.st_size;

        // Initialize a buffer with size of file
        char buf[fileSize];

        // Display file name
        printf("File %s:\n", argv[i]);

        // Get descriptor of file
        int fd = open(argv[i], O_RDONLY);
        // Error case
        if (fd == -1)
        {
            perror("Error encountered: ");
            //Error with the file
            return 1;
        }
    
        // Get nb of octets in file and store bytes in buf
        int Nboct = read(fd, buf, fileSize);
        if (Nboct == -1)
        {
            perror("Error encountered: ");
            //Error with the file
            return 1;
        }
        // Write in the third file
        int success = write(newFileDescriptor, buf, Nboct);

        if (success == -1)
        {
            perror("Error while writing in file: ");
            // Error
            return 1;
        }

        // Close file
        close(fd);
    }
    // Close new file
    close(newFileDescriptor);
    

    return 0;
}
