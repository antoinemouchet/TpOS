#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv[])
{
   int day, year;
   char weekday[20], month[20], dtm[100];

   strcpy( dtm, "25:Saturday March:1989" );
   sscanf( dtm, "%d:%s:%d", &day, weekday, &year);

   printf("%s\n", weekday);
   printf("%s\n", dtm);
    
   return(0);
}

/* sscanf CAN EXTRACT THE FIRST VALUE THAT'S SOOOOOOO  GREAAAAAAAT FUCK IT*/