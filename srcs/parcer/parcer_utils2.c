#include "../../includes/mini_shell.h"

int	exit_close_fds(int fd1, int fd2, int exit_status)
{
	if (fd1 != -1)
		close(fd1);
	if (fd1 != -1)
		close(fd2);
	return (exit_status);
}

int	is_rdr(char *str)
{
	if (!strcmp(str, ">"))
		return (1);
	else if (!strcmp(str, "<"))
		return (1);
	else if (!strcmp(str, "<<"))
		return (1);
	else if (!strcmp(str, ">>"))
		return (1);
	return (0);
}

int	read_line(char *buf, char **join, int end1, char *heredoc)
{
	(void)end1;
	while (true)
	{
		buf = readline("\033[1m\x1B[31m==> \033[0m\x1B[37m");
		if (buf == NULL)
			return (0);
		if (ft_strcmp(buf, heredoc) == 0)
			break ;
		else if (buf)
		{
			*join = ft_strjoin(*join, buf);
			*join = ft_strjoin(*join, "\n");
		}
		free(buf);
	}
	return (1);
}

static void	heredoc_exp(char **join)
{
	char	*tmp;

	tmp = NULL;
	g_env.here_doc = 1;
	tmp = parse_str(*join);
	free(*join);
	*join = ft_strdup(tmp);
	free(tmp);
}

int	read_here_doc(char **cmd_split, t_parser_info *pa_info,
	t_pars_tokens *pa_tkns)
{
	int		end[2];
	char	*heredoc;
	char	*buf;
	char	*join;

	join = NULL;
	buf = NULL;
	heredoc = NULL;
	if (pipe(end) == -1)
		return (ft_perror(EXIT_FAILURE, "pipe error"));
	heredoc = cmd_split[pa_info->i + 1];
	g_env.here_doc = check_qte_str(heredoc);
	delimit_qtes(heredoc);
	if (heredoc == NULL)
		return (exit_close_fds(end[0], end[1], EXIT_FAILURE));
	if (!read_line(buf, &join, end[1], heredoc))
		printf("WARNING : heredoc delemeted by EOF\n");
	if (!g_env.here_doc && join)
		heredoc_exp(&join);
	write(end[1], join, ft_strlen(join));
	close(end[1]);
	free_me(&join);
	pa_tkns[pa_info->j].here_doc_fd = end[0];
	g_env.fd_in = end[0];
	return (EXIT_SUCCESS);
}
