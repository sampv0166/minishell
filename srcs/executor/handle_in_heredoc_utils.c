#include "../../includes/mini_shell.h"

int	handle_in_redirections(t_pars_tokens *pa_tkns, int *i)
{
	int	k;

	k = *i;
	if (pa_tkns[k].is_in || pa_tkns[k].here_doc)
	{
		if (handle_in_and_here_doc(pa_tkns, k))
		{
			k++;
			*i = k;
			return (1);
		}
	}
	else
		g_env.fd_in = dup(g_env.fd_in);
	*i = k;
	return (0);
}

void	close_redir_fd(int *fd)
{
	if (*fd != 0)
		close(*fd);
}

void	find_cmd(t_pars_tokens *pa_tkns, int i, int *j)
{
	int	k;

	k = *j;
	while (pa_tkns[i].cmd_splitted[k])
	{
		if ((pa_tkns[i].cmd_splitted[k] && pa_tkns[i].cmd_splitted[k][0] == '<')
			|| pa_tkns[i].cmd_splitted[k][0] == '>')
		{
			k++;
			if (pa_tkns[i].cmd_splitted[k])
				k++;
		}
		if (pa_tkns[i].cmd_splitted[k] && ((pa_tkns[i].cmd_splitted[k][0]
				== '<' || pa_tkns[i].cmd_splitted[k][0] == '>')))
			continue ;
		else
		{
			if (pa_tkns[i].cmd_splitted[k])
			{
				k++;
			}
			break ;
		}
	}
	*j = k;
}

void	increment_j(t_pars_tokens *pa_tkns, int i, int *j)
{
	int	k;

	k = *j;
	if (pa_tkns[i].cmd_splitted[k]
		&& (pa_tkns[i].cmd_splitted[k][0] == '<'
		|| pa_tkns[i].cmd_splitted[k][0] == '>'))
	{
		k++;
		if (pa_tkns[i].cmd_splitted[k])
			k++;
	}
	*j = k;
}
