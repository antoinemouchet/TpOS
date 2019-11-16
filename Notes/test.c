#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
    char character = 'a';

    character = character - 32;

    printf("%c", character);

    return 0;
}
