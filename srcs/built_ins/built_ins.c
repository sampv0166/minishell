#include "../../includes/mini_shell.h"

extern t_env_var env;

/*
TODO : THESE TEST CASES ARE NOT WORKING SAME AS THE SYSTEM ECHO FUNCTION
* echo -n -n -nnnn -nnnnm
* echo "$HOME"
* echo '$HOME' 
* echo "
* echo ""
* echo "\"
* echo "\n \n \n"
* echo ;;
* echo hi";" hihi
*echo hi " ; " hihi
*/

// void	echo(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i + 1])
// 	{
// 		if (!ft_strcmp(str[i + 1], "-n"))
// 			i = 1;
// 		else
// 		{
// 			ft_putstr_fd(str[i + 1], 1);
// 		if (str[i + 2] != NULL)
// 			ft_putchar_fd(' ', 1);
// 		}	
// 		i++;
// 	}
// 	if (ft_strcmp(str[1], "-n") || str[1] == NULL)
// 		ft_putchar_fd('\n', 1);
// }

int	execute_inbuilt(t_pars_tokens *pa_tokens)
{
	if (ft_strcmp(pa_tokens->cmd[0], "echo") == 0)
	{
		echo(pa_tokens->cmd);
		return(EXIT_SUCCESS);
	}
	if (ft_strcmp(pa_tokens->cmd[0], "export") == 0)
		return (export(pa_tokens->cmd));
	if (ft_strcmp(pa_tokens->cmd[0], "env") == 0)
		return (env_var());
	if (ft_strcmp(pa_tokens->cmd[0], "cd") == 0)
		return (cd(pa_tokens->cmd));
	if (ft_strcmp(pa_tokens->cmd[0], "unset") == 0)
		return (unset(pa_tokens->cmd));
	if (ft_strcmp(pa_tokens->cmd[0], "pwd") == 0)
		return (pwd(pa_tokens->cmd, env.env_var));
	if (ft_strcmp(pa_tokens->cmd[0], "exit") == 0)
		return (ft_exit(pa_tokens->cmd));
	return (EXIT_FAILURE);
}


int	handle_inbuilt_redir(t_pars_tokens *pa_toks, int i)
{
	(void)i;
	int		exit_status;
	// int		saved_fds[2];
	if(i)
		i =0;
	// if (pa_toks->fd_in != STDIN_FILENO)
	// {
	// 	saved_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	// 	if (saved_fds[STDIN_FILENO] == -1)
	// 		return (ft_perror(EXIT_FAILURE, "Piping error"));
	// 	if (dup2(pa_toks->fd_in , STDIN_FILENO) == -1)
	// 		return (ft_perror(EXIT_FAILURE, "Piping error"));
	// }
	// if (pa_toks->fd_out != STDOUT_FILENO)
	// {
	// 	saved_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	// 	if (saved_fds[STDOUT_FILENO] == -1)
	// 		return (ft_perror(EXIT_FAILURE, "dup error"));
	// 	if (dup2(pa_toks->fd_out, STDOUT_FILENO) == -1)
	// 		return (ft_perror(EXIT_FAILURE, "dup2 error"));
	// }
	// if (pa_toks->pipe == true)
	// 	exit_status = execute_inbuilt_child(pa_toks);
	// else

	exit_status = execute_inbuilt(pa_toks);
	//execute_inbuilt_reset_fds(pa_toks, saved_fds);
	return (exit_status);
}

int	is_inbuilt(char *cmd)
{

	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}
