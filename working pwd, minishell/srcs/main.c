#include "../includes/mini_shell.h"


int main()
{
    // to store the current directory
    char cwd[FILENAME_MAX];

    //to store the input from the command line
    char **parsed;

    char *input;

    char *env;
    
    // to store the child id created using fork()
    pid_t child_pid;

    // this is needed for the waitpid function
    int stat_loc; 
	ft_putstr_fd(" _ __ ___ (_)_ __ (_)___| |__   ___| | |\n", STDERR);
	ft_putstr_fd("| '_ ` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |\n", STDERR);
	ft_putstr_fd("| | | | | | | | | | \\__ \\ | | |  __/ | |\n", STDERR);
	ft_putstr_fd("|_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|\n\n", STDERR);
    while(1)
    {
        // if we want to display the path we can uncomment this later
        //input = readline(getcwd(cwd, sizeof(cwd)));

        // readline() function will display a prompt and read everything after the prompt from commandline
        input = readline("MS SHELL====>");
        
        // split the whole input to seperate strings
        parsed = ft_split(input, ' ');

        // if the input is empty , continue and print the prompt again
        if(!parsed[0])
        {
            continue ;
        }

        // if the first element inside the parse array is "cd" just call the cd function and continue
        if(ft_strcmp(parsed[0], "cd") == 0)
        {
            if(cd(parsed[1]) < 0)
            {
                perror(parsed[1]);
            }
            continue ;
        }

        // if(!ft_strcmp(parsed[0], "pwd"))
        // {
        //     if(!pwd(parsed[0]))
        //     {
        //         perror(parsed[0]);
        //     }
        //     continue ;
        // }

        // create a child process with fork
        // after forking child_pid will be positive integer for parent process
        // after forking child_pid will be 0 for the child process
            child_pid = fork();

        // if any error while forking exit
        if(child_pid < 0)
        {
            perror("Fork Failed");
            exit(1);
        }

        if(child_pid == 0)
        {
            // execve executes system programs like ls , pwd etc ...
            // execve replaces the child process but the id remains unchanged
            //if execve is succesfull it never returns
            if(execve("/bin/sh", parsed, NULL) < 0)
            {
                perror(parsed[0]);
                exit(1);
            }
        }
        else 
        {
            //wait pid Suspends the main process until the child process ends.
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }
        free(parsed);
    }
    return (0);
}
