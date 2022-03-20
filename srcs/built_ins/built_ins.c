#include "../../includes/mini_shell.h"

int cd(char *path) 
{
    return chdir(path);
}

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

void	ft_init(t_flags *flags)
{
	flags->newl_flag = 0;
}
static void	execution(t_flags *flags, char **str)
{
	if (!flags->newl_flag)
		ft_putstr_fd("\n", 1);
	// free_all(str);
}

char	*duplicate(char *str, int *qte)
{
	int	i;
	int	j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (strlen(str) - 2 + 1));
	while (str[i])
	{
		if (str[i] != *qte)
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	free(str);
	return (res);
}

char	*fetch(char **env, char	*lk_up)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	lk_up = strchr(lk_up, '$');
	++lk_up;
	if (lk_up[i])
	{
		while (env[i])
		{
			if (strstr(env[i], lk_up))
			{
				res = strstr(env[i], lk_up);
				res = ft_strchr(res, '=');
				if (res)
					++res;
				break;
			}
			i++;
		}
	}
	return (res);
}

void	ft_putstr_echo(char *str, t_flags *flags, char **env)
{
	int	i;
	int	qte;
	char	*res;

	i = 0;
	qte = 0;
	res = NULL;
	if (str[0] == 34 || str[0] == 39)
	{
		qte = str[0];
		res = duplicate(str, &qte);
		str = strdup(res);
		free(res);
	}
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1])
				ft_putstr_fd(fetch(env, str), 1);
			else
				ft_putchar_fd('$', 1);
			break;
		}
		else if (str[i] != qte)
			ft_putchar_fd(str[i],1);
		i++;
	}
}

void	echo(char **str, char **env)
{
	int	i;
	t_flags	flags;
	i = 1;
	if (str[i])
	{
		if (!ft_strcmp(str[i], "-n"))
		{
			flags.newl_flag = 1;
			i++;
		}
		if (str)
		{
			while (str[i] != NULL)
			{
				ft_putstr_echo(str[i], &flags, env);
				i++;
				if ((str[i] != NULL) && (strchr(str[i], '>') || strchr(str[i], '<') || strchr(str[i], '|')))
					break;
				else if (str[i] != NULL)
					ft_putchar_fd(' ', 1);
			}
		}
	}
	execution(&flags, str);
}

int	execute_inbuilt(t_pars_tokens *pa_tokens, t_env_var *env)
{
	if (ft_strcmp(pa_tokens->cmd[0], "echo") == 0)
	{
		echo(pa_tokens->cmd, env->envp);
		return(EXIT_SUCCESS);
	}
	// if (ft_strcmp(pa_tokens->cmd[0], "export") == 0)
	// 	return (export(pa_tokens->cmd));
	// if (ft_strcmp(pa_tokens->cmd[0], "env") == 0)
	// 	return (env(pa_tokens->cmd));
	// if (ft_strcmp(pa_tokens->cmd[0], "cd") == 0)
	// 	return (cd(pa_tokens->cmd));
	// if (ft_strcmp(pa_tokens->cmd[0], "unset") == 0)
	// 	return (unset(pa_tokens->cmd));
	// if (ft_strcmp(pa_tokens->cmd[0], "pwd") == 0)
	// 	return (pwd());
	// if (ft_strcmp(pa_tokens->cmd[0], "exit") == 0)
	// 	return (exit_inbuilt(pa_tokens->cmd));
	return (EXIT_FAILURE);
}


int	handle_inbuilt_redir(t_pars_tokens *pa_toks, int i, t_env_var *env)
{
	int		exit_status;
	// int		saved_fds[2];

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

	exit_status = execute_inbuilt(pa_toks, env);
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
