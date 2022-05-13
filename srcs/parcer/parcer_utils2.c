
#include "../../includes/mini_shell.h"

extern t_env_var env;

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



int read_line(char *buf, char **join, int end1, char *heredoc)
{
    while (true)
	{
		buf = readline("> ");
		if (buf == NULL)
			return (EXIT_SUCCESS);
		if (ft_strcmp(buf, heredoc) == 0)
			break ;
        else if(buf)
        {
            *join = ft_strjoin(*join, buf);    
            *join = ft_strjoin(*join, "\n");
        }
		free(buf);
	}
	return (1);
}

int read_here_doc(char **cmd_split, t_parser_info *pa_info, t_pars_tokens *pa_tkns)
{
    int		end[2];
    char *heredoc;
    char *buf;
    char *join;

    join = NULL;
    heredoc = NULL;
    if (pipe(end) == -1)
		return (ft_perror(EXIT_FAILURE, "pipe error"));    
	heredoc = cmd_split[pa_info->i + 1];
	delimit_qtes(heredoc);
	if (heredoc == NULL)
		return (exit_close_fds(end[0], end[1], EXIT_FAILURE));    
	if(!read_line(buf, &join, end[1],heredoc))
		return (EXIT_FAILURE);
	write(end[1],join, ft_strlen(join));
   
	close(end[1]);
	free_me(&join);
	 
    pa_tkns[pa_info->j].here_doc_fd = end[0];
    env.fd_in = end[0];
}