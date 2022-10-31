#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void rm_command(const char path[])
{
    DIR *dir;
    char *completepath;
    struct stat sp;
    struct stat se;
    struct dirent *entry;
    size_t len_path;

    stat(path, &sp);
    if (S_ISDIR(sp.st_mode) == 0) 
    {
        fprintf(stderr, "%s: %s\n", "is not a directory", path);
        exit(-1);
    }

    if ((dir = opendir(path)) == NULL) 
    {
        fprintf(stderr, "%s: %s\n", "Cannot open the directory with the given path", path);
        exit(-1);
    }

    len_path = strlen(path);
    while ((entry = readdir(dir))!= NULL) 
    {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        completepath = calloc(len_path + strlen(entry->d_name) + 1, sizeof(char));
        strcpy(completepath, path);
        strcat(strcat(completepath, "/"), entry->d_name);
        stat(completepath, &se);

        if (S_ISDIR(se.st_mode) != 0) 
        {
            rm_command(completepath);
            continue;
        }

        if (unlink(completepath) != 0) // removing a file object
        {
            printf("Unable to remove the given file: %s\n", completepath);
        }

        free(completepath);
    }

    if (rmdir(path) == 0)
    {
        printf("Directory removed: %s\n", path);
    }
    else
    {
        printf("Can`t remove a directory: %s\n", path);
    }
    
    closedir(dir);
}


int main(int argc, char *argv[])
{
    if (argc > 1 && argv[1][0] == '-')
    {
        if (argv[1][1] == 'i')
        {
            for(int i=2;i<argc;i++)
            {
                printf("rm: do you want to remove the file '%s' ?",argv[i]);
                char c;
                fflush(stdin);
                scanf("%s",&c);
                if(c=='y')
                {
                    if(remove(argv[i])!=0)
                    {
                        printf("File: %s does not exist", argv[i]);
                    }
                    else
                    {
                        printf("File: %s has been removed successfully.", argv[i]);
                    }
                }
            }
        }
      
        else if (argv[1][1] == 'r')
        {
            for(int i=2;i<argc;i++)
            {
                rm_command(argv[i]);
            }
        }

        else
        {
            perror("Invalid command !!");
        }
    }
    
    else if (argc > 1)
    {
        for(int i=1;i<argc;i++)
        {
            if (remove(argv[i]) != 0)
            {
                printf("File: %s does not exist", argv[i]);
            }
        }
    }
    
    else
    {
        perror("Invalid format for the rm command !!\nFormat to be followed is : rm -[option] [file/directory]");
    }

    return 0;

}
