#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char * argv[])
{
  
    if(argc==1)
    {
        char arr[256] = {0};
        time_t time_sec = time(NULL);
        struct tm *format_time = localtime(&time_sec);
        strftime(arr, 256, "%a %b %d %X %Z %Y", format_time); 
        puts(arr);
    }

    else if(strcmp(argv[1],"-r")==0)   //Displays the last time the file_name was modified
    {
        char * file_name = argv[2];
        char arr_1[100] = "";
        struct stat dump;
        
        if (!stat(file_name, &dump)) 
        {
        strftime(arr_1, 100, "%d/%m/%Y %H:%M:%S", localtime( &dump.st_mtime));
        printf("\nLast modified date and time is as follows = %s\n", arr_1);
        } 
        
        else 
        {
        printf("Unable to display the time here.\n");
        }
        
    }

    else if(strcmp(argv[1],"-u")==0)   //Displays time according to the GMT
    {
        char arr_2[256] = {0};
        time_t time_sec = time(NULL);
        struct tm *format_time = gmtime(&time_sec);
        strftime(arr_2, 256, "%a %b %d %X %Z %Y", format_time); 
        puts(arr_2);
    }
    
    return 0;
}
