#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

void muld_mkdir(char *dir_path) 
{
    char *check = strrchr(dir_path, '/');
    
    if(check != NULL) 
    {
        *check = 0;
        muld_mkdir(dir_path);
        *check = '/';
        printf("Directory has been successfully created.");
    }
    
    if(mkdir(dir_path, 0777) && errno != EEXIST)
    {
        printf("An error occurred while trying to create '%s'\n", dir_path); 
    }
        
}

void oned_mkdir(const char *fname)
{
    int var = mkdir(fname,0777);
    
    if (var==0)
    {
        printf("Directory has been successfully created.");
    }
    
    else
    {
        printf("Directory creation was unsuccessful.\n");
        exit(1);
    }
}

int main(int argc,char* argv[])
{
    if(argc==1)
    {
      perror("Invalid Input format, Name of directory not present\nFormat is : mkdir [directoryname]");
      exit(0);
    }

    else if(argc==2 && argv[1][0]!='-')
    {
      oned_mkdir(argv[1]);
    }

    else if(argc>2 && argv[1][0]!='-')
    {
        if(argv[1][1]=='v')
        {
            int dir_id=2;
            for(int dir_id=2;dir_id<argc;dir_id++)
            {
                oned_mkdir(argv[dir_id]);
                printf(" mkdir : directory %s created\n",argv[dir_id]);
            }
        }
      
        else if(argv[1][1]=='p')
        {
            muld_mkdir(argv[2]); 
        }
    }
    
    else
    {
        perror("Invalid format for mkdir!\nFormat: mkdir -[option] [dirctories]\n");
        exit(1);
    }
    
    return 0;

}

