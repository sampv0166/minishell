#include "../../includes/mini_shell.h"

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

int	execute_inbuilt(t_pars_tokens *pa_tokens, int i)
{
	if (g_env.fd_out == -1)
		return (EXIT_FAILURE);
	if (!ft_strcmp(pa_tokens[i].cmd[0], "echo")
		|| !ft_strcmp(pa_tokens[i].cmd[0], "echo\"\""))
	{
		echo(pa_tokens[i].cmd, pa_tokens[i].cmd_cpy);
		return (EXIT_SUCCESS);
	}
	else if (ft_strcmp(pa_tokens[i].cmd[0], "export") == 0)
		return (export(pa_tokens[i].cmd));
	else if (ft_strcmp(pa_tokens[i].cmd[0], "env") == 0)
		return (env_var());
	else if ((ft_strcmp(pa_tokens[i].cmd[0], "cd") == 0)
		&& (pa_tokens[i].pipe == 2 || pa_tokens[i].pipe == 0))
		return (cd(pa_tokens[i].cmd));
	else if (ft_strcmp(pa_tokens[i].cmd[0], "unset") == 0)
		return (unset(pa_tokens[i].cmd));
	else if (ft_strcmp(pa_tokens[i].cmd[0], "pwd") == 0)
		return (pwd(pa_tokens[i].cmd));
	else if (ft_strcmp(pa_tokens[i].cmd[0], "exit") == 0)
	{
		g_env.stat_code = ft_exit(pa_tokens[i].cmd, pa_tokens[i].pipe);
		return (g_env.stat_code);
	}
	return (EXIT_FAILURE);
}

int	handle_inbuilt_redir(t_pars_tokens *pa_toks, int i, int **p)
{
	if (pa_toks[i].pipe && !pa_toks[i].is_out && !pa_toks[i].is_out_appnd)
	{
		if (pa_toks[i].pipe == 1)
			;
		else
			g_env.fd_out = p[i + 1][1];	
	}
	g_env.stat_code = execute_inbuilt(pa_toks, i);
	return (g_env.stat_code);
}

int	is_inbuilt(char *cmd)
{
	if (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "echo\"\""))
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
