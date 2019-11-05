#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 255


int main(int argc, char const *argv[])
{
    char buf[BUF_SIZE];

    if (argc < 2)
    {
        printf("The program expected at least one file name.");
        //Error, not enough argument.
        return 1;
    }

    //Display files
    for (int i = 1; i < argc; i++)
    {
        //get stats from file
        struct stat statfile;
        stat(argv[i], &statfile);

        //Display file name
        printf("File %s:\n", argv[i]);

        //get descriptor of file
        int fd = open(argv[i], O_RDONLY);
        //Error case
        if (fd == -1)
        {
            perror("Error encountered: ");
            //Error with the file
            return 1;
        }
    
        //get nb of octets in file and store bytes in buf
        int Nboct = read(fd, buf, statfile.st_size);
        if (Nboct == -1)
        {
            perror("Error encountered: ");
            //Error with the file
            return 1;
        }
        //Write on the screen
        write(1, buf, Nboct);

        //Close file
        close(fd);
    }

    return 0;
}
