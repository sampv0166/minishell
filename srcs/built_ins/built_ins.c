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

int	execute_inbuilt(t_pars_tokens *pa_tokens , int i)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(pa_tokens[i].cmd[0], "echo") == 0)
	{
		// print_2d_array(pa_tokens->cmd);
		echo(pa_tokens[i].cmd);
		return(EXIT_SUCCESS);
	}
	if (ft_strcmp(pa_tokens[i].cmd[0], "export") == 0)
		return (export(pa_tokens[i].cmd));
	if (ft_strcmp(pa_tokens[i].cmd[0], "env") == 0)
		return (env_var());
	if (ft_strcmp(pa_tokens[i].cmd[0], "cd") == 0)
	{
		ret = cd(pa_tokens[i].cmd);
		return (ret);
	}
	if (ft_strcmp(pa_tokens[i].cmd[0], "unset") == 0)
		return (unset(pa_tokens[i].cmd));
	if (ft_strcmp(pa_tokens[i].cmd[0], "pwd") == 0)
		return (pwd(pa_tokens[i].cmd, env.env_var));
	if (ft_strcmp(pa_tokens[i].cmd[0], "exit") == 0)
	{
		ret = ft_exit(pa_tokens[i].cmd);
		if (!env.trigger)
			exit(ret);
		return (ret);
	}
	return (EXIT_FAILURE);
}


int	handle_inbuilt_redir(t_pars_tokens *pa_toks, int i)
{
	//(void)i;
	int		exit_status;
	// int		saved_fds[2];
	// if(i)
	// 	i = 0;
	// handle builtint redirections here . 
	//exit(0);
	exit_status = execute_inbuilt(pa_toks, i);
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
