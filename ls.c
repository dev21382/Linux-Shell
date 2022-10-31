#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <errno.h>

void fun_check(int *a_check,int *l_check,char **argv)
{
  	    *a_check = 0;
        *l_check = 0;
        char *ptr = (char *)(argv[1] + 1);
        while (*ptr)
        {
            if (*ptr == 'a')
                *a_check = 1;
            else if (*ptr == '1')
                *l_check = 1;
            else
            {
                perror("The option which you want to choose is not available.");
                exit(EXIT_FAILURE);
            }

            ptr++;
        }
}

void ls_command(const char *dir, int a_check, int l_check)
{
    DIR *dir_stream = opendir(dir);
    struct dirent *dfile;
    if (!dir_stream)
    {
        if (errno == ENOENT)
        {
            perror("This Directory does not exist !!");
        }
        
        else
        {
            perror("Here the shell is unable to read the directory."); // EACCES error
        }
        exit(EXIT_FAILURE);

    }


    while ((dfile = readdir(dir_stream)) != NULL)
    {
        if (!a_check && dfile->d_name[0] == '.')
        {
            continue;
        }
        printf("%s  ", dfile->d_name);
        if (l_check)
            printf("\n");
    }
    
    if (!l_check)
        printf("\n");
}

int main(int argc, const char **argv)
{
    if (argc == 1)
    {
        ls_command(".", 0, 0);
    }
    
    else if (argc == 2)
    {
        if (argv[1][0] == '-')
        {
            int a_check = 0;
            int l_check = 0;
            fun_check(&a_check,&l_check,argv);
            ls_command(".", a_check, l_check);
        }
        
        else
        {
            ls_command(argv[1], 0, 0);
        }

    }
    
    else if (argc == 3)
    {
        if (argv[1][0] != '-')
        {
            perror("Invalid command input !!");
            exit(EXIT_FAILURE);
        }
        
        int a_check = 0;
        int l_check = 0;
        fun_check(&a_check,&l_check,argv);
        
        ls_command(argv[2], a_check, l_check);
    
    }

    return 0;
}
