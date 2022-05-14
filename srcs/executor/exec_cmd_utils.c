#include "../../includes/mini_shell.h"

extern t_env_var	env;

int	is_redir(t_pars_tokens *pa_tok, int i)
{
	if (pa_tok[i].is_in == 1 || pa_tok[i].is_out == 1
		|| pa_tok[i].here_doc == 1 || pa_tok[i].pipe
		|| pa_tok[i].is_out_appnd == 1)
		return (1);
	return (0);
}

static void	set_fd1(int *fd, char **cmd_split, int *k)
{
	if (*fd != 0)
		close(*fd);
	*fd = open(cmd_split[(*k) + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
}

int	set_fds(char **cmd_split, int *i, int *fd)
{
	int	k;

	k = *i;
	while (cmd_split[k])
	{
		if (cmd_split && cmd_split[k] && (cmd_split[k][0] == '>'
			&& ft_strlen(cmd_split[k]) == 1 && cmd_split[k + 1]))
		{
			if (*fd != 0)
				close(*fd);
			*fd = open(cmd_split[k + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (*fd == -1)
				return (ft_perror(EXIT_FAILURE, "error opening file"));
		}
		if (cmd_split[k] && (cmd_split[k][0] == '>' && cmd_split[k][1] == '>'
			&& ft_strlen(cmd_split[k]) == 2 && cmd_split[k + 1]))
		{
			set_fd1(fd, cmd_split, &k);
			if (*fd == -1)
				return (ft_perror(EXIT_FAILURE, "error opening file"));
		}
		k++;
	}
	*i = k;
	return (0);
}

int	ft_eco_check(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 4 || ft_strlen(str) == 6)
	{
		if (str[0] == 'e' || str[0] == 'E')
			if (str[1] == 'c' || str[1] == 'C')
				if (str[2] == 'h' || str[2] == 'H')
					if (str[3] == 'o' || str[3] == 'O')
						return (1);
	}
	return (0);
}

int	handle_pipes(t_pars_tokens *pa_tokens, int i)
{
	int	fd[2];

	pipe(fd);
	pa_tokens[i].fd_in = fd[0];
	pa_tokens[i].fd_out = fd[1];
	env.fd_in = fd[0];
	env.fd_out = fd[1];
	env.fd_pipe_in_open = fd[0];
	env.fd_pipe_out_open = fd[1];
	return (0);
}
