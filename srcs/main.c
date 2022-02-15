#include "../includes/mini_shell.h"


INPUT_TO_TOKENS_H

static int get_input(void)
{
    char *input;
    int ret;

    while(1)
    {
        input = readline("MS SHELL====>");
        if(ft_strlen(input) > 0)
            add_history(input);
        if(input == NULL)
            exit(EXIT_SUCCESS); // TODO : free everything  
        ret = input_to_tokens(input);
        if(ret == EXIT_FAILURE)
            return (EXIT_FAILURE); // TODO : free everything  
        free (input);
    }
    return (EXIT_FAILURE);
}

int main(int ac, char **argv, char **envp)
{
    t_env_var *env;

    handle_signals();

    env = init_env_vars(envp);
    if(env == NULL)
        return (EXIT_FAILURE); // TODO :  free everything
    if(!get_input())
        return (EXIT_FAILURE); // TODO :  free everything
    return (EXIT_SUCCESS);    
}


    // // to store the current directory
    // char	cwd[FILENAME_MAX];

    // //to store the input from the command line
    // char **parsed;

    // char *input;

    // char *env;
    
    // // to store the child id created using fork()
    // pid_t child_pid;

    // // this is needed for the waitpid function
    // int stat_loc; 
	// ft_putstr_fd(" _ __ ___ (_)_ __ (_)___| |__   ___| | |\n", STDERR);
	// ft_putstr_fd("| '_ ` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |\n", STDERR);
	// ft_putstr_fd("| | | | | | | | | | \\__ \\ | | |  __/ | |\n", STDERR);
	// ft_putstr_fd("|_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|\n\n", STDERR);
    // while(1)
    // {
    //     // if we want to display the path we can uncomment this later
    //     //input = readline(getcwd(cwd, sizeof(cwd)));

    //     // readline() function will display a prompt and read everything after the prompt from commandline
    //     input = readline("MS SHELL====>");
        
    //     // split the whole input to seperate strings
    //     parsed = ft_split(input, ' ');

    //     // if the input is empty , continue and print the prompt again
    //     if(!parsed[0])
    //     {
    //         continue ;
    //     }

    //     // if the first element inside the parse array is "cd" just call the cd function and continue
    //     if(ft_strcmp(parsed[0], "cd") == 0)
    //     {
    //         if(cd(parsed[1]) < 0)
    //         {
    //             perror(parsed[1]);
    //         }
    //         continue ;
    //     }

    //     // if(!ft_strcmp(parsed[0], "pwd"))
    //     // {
    //     //     if(!pwd(parsed[0]))
    //     //     {
    //     //         perror(parsed[0]);
    //     //     }
    //     //     continue ;
    //     // }

    //     // create a child process with fork
    //     // after forking child_pid will be positive integer for parent process
    //     // after forking child_pid will be 0 for the child process
    //         child_pid = fork();

    //     // if any error while forking exit
    //     if(child_pid < 0)
    //     {
    //         perror("Fork Failed");
	// 		exit(1);
	// 	}
		
	// 	if(child_pid == 0)
	// 	{
	// 		// execve executes system programs like ls , pwd etc ...
    //         // execve replaces the child process but the id remains unchanged
    //         //if execve is succesfull it never returns
	// 		if (!strcmp(parsed[0], "ls") || !strcmp(parsed[0], "pwd"))
    //         {
	// 			if(execve("/bin/sh", parsed, NULL) < 0)
    //             {
	// 				perror(parsed[0]);
	// 				exit(1);
	// 			}
	// 		}

	// 		//echo command function
	// 		if (!strcmp(parsed[0], "echo"))
	// 			echo(parsed);
	// 	}
    //     else 
    //     {
    //         //wait pid Suspends the main process until the child process ends.
    //         waitpid(child_pid, &stat_loc, WUNTRACED);
    //     }
    //     free(parsed);
    // }
   // return (0);
//}
