#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <limits.h>

char **seperate(char *arr_args)
{
    int ct_size = 1024;
    char *temp_cmd = malloc(ct_size * sizeof(char));
    int tk_cnt = 0;

    int arr_size = 128;
    char **arr_char = malloc(arr_size * sizeof(char *));
    int cnt = 0;

    for (int cnt_ = 0; cnt_ < strlen(arr_args); cnt_++)
    {
        char ch = arr_args[cnt_];
        if (ch == ' ')
        {
            if (cnt + 1 > arr_size)
            {
                arr_size += 100;
                arr_char = realloc(arr_char, arr_size * sizeof(char *));
            }
            if (tk_cnt + 1 > ct_size)
            {
                ct_size += 1024;
                temp_cmd = realloc(temp_cmd, ct_size);
            }

            arr_char[cnt] = temp_cmd;
            cnt++;

            temp_cmd = malloc(ct_size * sizeof(char *));
            tk_cnt = 0;
        }
        else if (ch == '\n')
        {
            if (tk_cnt + 2 > arr_size)
            {
                arr_size = arr_size + 100;
                arr_char = realloc(temp_cmd, ct_size);
            }

            arr_char[cnt] = temp_cmd;
            cnt++;

            arr_char[cnt] = NULL;
            break;
        }
        else
        {
            if (tk_cnt + 1 > ct_size)
            {
                ct_size = ct_size + 1024;
                temp_cmd = realloc(temp_cmd, ct_size);
            }

            temp_cmd[tk_cnt] = ch;
            tk_cnt++;
        }
    }
    return arr_char;
}

void *result(void *CMD_BLOCK)
{
    int counter = 0;
    int length = 0;
    char **temp_cmd = (char **)CMD_BLOCK;

    while (temp_cmd[counter] != NULL)
    {
        length = length + strlen(temp_cmd[counter]) + 1;
        counter += 1;
    }
    char array[length];
    int count = 0;
    counter += 1;
    int cnt_ = 0;
    while (cnt_ < counter - 1)
    {
        int b = strlen(temp_cmd[cnt_]);
        for (int j = 0; j < b; j++)
        {
            array[count] = temp_cmd[cnt_][j];
            count++;
        }
        array[count] = ' ';
        count += 1;
        cnt_ += 1;
    }
    array[length - 1] = '\0';
    system(array);
}
char *cutoff(char *str)
{
    char *c1;
    char *c2;
    char *c3;
    const char *temp = "&t";

    if (*temp && (c2 = c3 = strstr(str, temp)) != NULL)
    {
        size_t length = strlen(temp);
        while ((c3 = strstr(c1 = c3 + length, temp)) != NULL)
        {
            while (c1 < c3)
                *c2++ = *c1++;
        }
        while ((*c2++ = *c1++) != '\0')
            continue;
    }
    return str;
}

void thrd_execute(char **CMD_BLOCK)
{
    // char *cmd = cutoff(CMD_BLOCK[0]);

    if (strcmp(cutoff(CMD_BLOCK[0]), "pwd") == 0)
    {
        char temp[] = "pwd";
        int cnt_ = 1;
        while (CMD_BLOCK[cnt_] != NULL)
        {
            {
                strcat(temp, " ");
                strcat(temp, CMD_BLOCK[cnt_]);
                cnt_++;
            }
        }
        system(temp);
    }

    else if (strcmp(cutoff(CMD_BLOCK[0]), "cd") == 0)
    {
        chdir(CMD_BLOCK[1]);
        printf("Directory changed to : %s\n", CMD_BLOCK[1]);
    }

    else if (strcmp(cutoff(CMD_BLOCK[0]), "echo") == 0)
    {
        if (CMD_BLOCK[1] == NULL)
        {
            printf("--EMPTY--\n");
            return;
        }
        else if (strcmp(CMD_BLOCK[1], "-n") == 0)
        {
            char temp[1000] = "echo -n";
            int cnt_ = 2;
            while (CMD_BLOCK[cnt_] != NULL)
            {
                {
                    strcat(temp, " ");
                    strcat(temp, CMD_BLOCK[cnt_]);
                    cnt_++;
                }
            }
            system(temp);
        }

        else if (strcmp(CMD_BLOCK[1], "*") == 0)
        {
            system("echo *");
        }

        else
        {
            char temp[1024] = "echo";
            int cnt_ = 1;
            while (CMD_BLOCK[cnt_] != NULL)
            {
                {
                    strcat(temp, " ");
                    strcat(temp, CMD_BLOCK[cnt_]);
                    cnt_++;
                }
            }
            system(temp);
        }
    }

    else if (strcmp(CMD_BLOCK[0], "quit") == 0)
    {
        system("quit");
        exit(0);
    }
    else
    {
        pthread_t thread;
        int flag = pthread_create(&thread, NULL, result, CMD_BLOCK);
        assert(flag == 0);
        flag = pthread_join(thread, NULL);
        assert(flag == 0);
    }
}

void runner(char **CMD_BLOCK)
{
    if (strcmp(CMD_BLOCK[0], "echo") == 0)
    {

        if (CMD_BLOCK[1] == NULL)
        {
            printf("Nothing to display!\n");
            return;
        }

        else if (strcmp(CMD_BLOCK[1], "*") == 0) 
        {

            if (fork() != 0) 
            {
                wait(NULL);
            }
            else
            {
                char *bruh[] = {"ls", NULL};
                execvp("ls", bruh);
            }
        }

        else if (strcmp(CMD_BLOCK[1], "-n") == 0)
        {
            int cnt_ = 2;
            while (CMD_BLOCK[cnt_] != NULL)
            {
                {
                    printf("%s ", CMD_BLOCK[cnt_]);
                    cnt_++;
                }
            }
        }

        else
        {
            int cnt_ = 1;

            while (CMD_BLOCK[cnt_] != NULL)
            {
                {
                    printf("%s ", CMD_BLOCK[cnt_]);
                    cnt_++;
                }
            }
            printf("\n");
        }
    }

    else if (strcmp(CMD_BLOCK[0], "cd") == 0)
    {
        chdir(CMD_BLOCK[1]);
        printf("Changing directory to : %s\n", CMD_BLOCK[1]);
    }


    else if (strcmp(CMD_BLOCK[0], "pwd") == 0)
    {
        int t_argc = 0;
        int cnt_ = 0;
        while (CMD_BLOCK[cnt_] != NULL)
        {
            t_argc++;
            cnt_++;
        }
        if (t_argc > 1 && CMD_BLOCK[1][1] == 'p')
        {
            char direc[PATH_MAX];
            getcwd(direc, sizeof(direc));
            char act_path[PATH_MAX + 1];
            char *ptr;
            ptr = realpath(direc, act_path);
            printf("Physical path of direc: %s\n", direc);
        }
        else
        {
            char direc[PATH_MAX];
            if (getcwd(direc, sizeof(direc)) != NULL)
            {
                printf("Current working dir: %s\n", direc);
            }
            else
            {
                perror("getcwd() error");
            }
        }
    }

    //----------------------------------------------------------------------------
    else if (strcmp(CMD_BLOCK[0], "quit") == 0)
    {
        printf("Quitting\n");
        exit(0);
    }
    //-----------------------------------------------------------------------------
    else
    {

        if (fork() != 0)
        {
            wait(NULL);
        }
        else
        {
            execvp(CMD_BLOCK[0], CMD_BLOCK);
        }
    }
}
//===================================================================================================

char *input_line()
{
    size_t temp;
    char *array;
    size_t arr_size = 100;

    array = (char *)malloc(arr_size * sizeof(char));

    if (array == NULL)
    {
        printf("Error : Memory allocation failed\n");
        exit(1);
    }
    temp = getline(&array, &arr_size, stdin);
    return array;
}

int main()
{
    char direc[PATH_MAX];
    getcwd(direc, sizeof(direc));
    setenv("PATH", direc, 1);
    printf("+++++< CUSTOM SHELL >+++++\n");

    while (true)
    {
        printf("->");

        char *CMD_LINE = input_line();
        char **CMD_BLOCK = seperate(CMD_LINE);
        bool cond;
        int cnt_ = strlen(CMD_BLOCK[0]);
        if (CMD_BLOCK[0][cnt_ - 2] == '&' && CMD_BLOCK[0][cnt_ - 1] == 't')
        {
            cond = true;
        }
        else
        {
            cond = false;
        }

        if (cond)
        {
            thrd_execute(CMD_BLOCK);
        }

        free(CMD_LINE);
        runner(CMD_BLOCK);
        free(CMD_BLOCK);
    }

    return 0;
}
