#include "../includes/mini_shell.h"


int main()
{
    char cwd[FILENAME_MAX];
    char **parsed;
    char *input;
    pid_t child_pid;
    int stat_loc; 

    while(1)
    {
        input = readline(getcwd(cwd, sizeof(cwd)));
        parsed = ft_split(input, ' ');


        if(!parsed[0])
        {
            continue ;
        }

        if(ft_strcmp(parsed[0], "cd") == 0)
        {
            if(cd(parsed[1]) < 0)
            {
                perror(parsed[1]);
            }
            continue ;
        }

        child_pid = fork();

        if(child_pid < 0)
        {
            perror("Fork Failed");
            exit(1);
        }

        if(child_pid == 0)
        {
            if(execvp(parsed[0], parsed) < 0)
            {
                perror(parsed[0]);
                exit(1);
            }
        }
        else 
        {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }

        free(parsed);
    }
    return (0);
}
