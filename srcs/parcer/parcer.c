#include "../../includes/mini_shell.h"

extern t_env_var env;

void set_pipe_type(t_pars_tokens *pa_tkns, t_parser_info *pa_info)
{
    pa_info->j = 0;
    while (pa_info->j < env.count)
    {
        if ((pa_tkns[pa_info->j].cmd_full && pa_tkns[pa_info->j].cmd_full[0] == '|') && (pa_tkns[pa_info->j].cmd_full[ft_strlen(pa_tkns[pa_info->j].cmd_full) - 1] == '|'))
        {
            pa_tkns[pa_info->j].pipe_read_end = 1;
            pa_tkns[pa_info->j].pipe_write_end = 1;
            pa_tkns[pa_info->j].pipe = 3;
        }
        else if (pa_tkns[pa_info->j].cmd_full && pa_tkns[pa_info->j].cmd_full[0] != '|' && pa_tkns[pa_info->j].cmd_full[ft_strlen(pa_tkns[pa_info->j].cmd_full) - 1] == '|')
        {
            pa_tkns[pa_info->j].pipe_read_end = 0;
            pa_tkns[pa_info->j].pipe_write_end = 1;
            pa_tkns[pa_info->j].pipe = 2;
        }
        else if (pa_tkns[pa_info->j].cmd_full && pa_tkns[pa_info->j].cmd_full[0] == '|' && pa_tkns[pa_info->j].cmd_full[ft_strlen(pa_tkns[pa_info->j].cmd_full) - 1] != '|')
        {
            pa_tkns[pa_info->j].pipe_read_end = 1;
            pa_tkns[pa_info->j].pipe_write_end = 0;
            pa_tkns[pa_info->j].pipe = 1;             
        }
        pa_info->j++;
    }
}

static int	exit_close_fds(int fd1, int fd2, int exit_status)
{
	if (fd1 != -1)
		close(fd1);
	if (fd1 != -1)
		close(fd2);
	return (exit_status);
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
    while (true)
	{
		buf = readline("");
		if (buf == NULL)
			return (exit_close_fds(end[1], -1, EXIT_SUCCESS));
		if (ft_strcmp(buf, heredoc) == 0)
			break ;
        else if(buf)
        {
            join = ft_strjoin(join, buf);    
            join = ft_strjoin(join, "\n");
        }
		free(buf);
	}
    int i;
    //int len;
    i = 0;
    write(end[1],join, ft_strlen(join));
    close(end[1]);
	free_me(&join);
    //pa_tkns[pa_info->j].fd_in = end[0];
    pa_tkns[pa_info->j].here_doc_fd = end[0];
    env.fd_in = end[0];
   // ft_putnbr_fd(end[0], 2);
}
void set_redirection_type(t_pars_tokens *pa_tkns, t_parser_info *pa_info, char **tokens)
{
    if(tokens[pa_info->i][0] == '>' && tokens[pa_info->i][1] == '>')
    {     
        pa_tkns[pa_info->j].is_out_appnd = 1; 
    }
    else if(tokens[pa_info->i][0] == '>')
        pa_tkns[pa_info->j].is_out = 1;
    if(tokens[pa_info->i][0] == '<' && tokens[pa_info->i][1] == '<')
    {
        read_here_doc(tokens, pa_info,pa_tkns);
        pa_tkns[pa_info->j].here_doc = 1;
    }
    else if(tokens[pa_info->i][0] == '<')
        pa_tkns[pa_info->j].is_in = 1; 
}



void deal_with_pipes(t_pars_tokens *pa_tkns, t_parser_info *pa_info, char **tokens)
{
    pa_info->arr[pa_info->len] = ((char *)0);
    pa_info->str = ft_strjoin (pa_info->str, tokens[pa_info->i]);
    pa_info->arr1[pa_info->len] = ((char *)0);
    pa_info->len++;
    pa_info->i++;
    pa_tkns[pa_info->j].fd_out = STDOUT_FILENO;
    // pa_tkns[pa_info->j].is_in = 0;
    // pa_tkns[pa_info->j].is_out = 0;
    ///pa_tkns[pa_info->j].is_out_appnd = 0;
    //pa_tkns[pa_info->j].pipe = 0;
}
void create_cmds(t_parser_info *pa_info, char **tokens)
{
    pa_info->arr[pa_info->len] = ft_strdup(tokens[pa_info->i]);
	pa_info->arr1[pa_info->len] = ft_strdup(tokens[pa_info->i]);
    pa_info->str = ft_strjoin (pa_info->str, tokens[pa_info->i]);
    pa_info->len++;
    pa_info->i++;
}

void init_pa_tkns(t_pars_tokens *pa_tkns, t_parser_info *pa_info)
{
    int i;
    i = 2;
    
    while (i < pa_info->pipes_count)
    {
        pa_tkns[i].cmd = NULL;
        pa_tkns[i].cmd_full = NULL;
        pa_tkns[i].cmd_splitted = NULL;
		pa_tkns[i].cmd_cpy = NULL;
        pa_tkns[i].pipe = 0;

        pa_tkns[i].is_in = 0;
        pa_tkns[i].is_out = 0;
        pa_tkns[i].is_out_appnd = 0;
        pa_tkns[i].fd_in = 0;

        pa_tkns[i].fd_out = 0;
        pa_tkns[i].here_doc = 0;

        pa_tkns[i].pipe_read_end = 0;
        pa_tkns[i].pipe_write_end= 0;
        i++;
    }
    env.pa_info = pa_info;
    env.pa_tkns = pa_tkns;
}

int	cmd_w_flags(char *str)
{
	if (!ft_strcmp(str,"ls"))
		return (1);
	else if (!ft_strcmp(str,"wc"))
		return (1);
	return (0);
}

void    parse_rdr_in(t_pars_tokens *pa_tkns, t_parser_info *pa_info)
{
    int i;
    int count;
	int		flag_trig;
    char    **cmd;
    int     trigger;
    int     stp;
	int		index;
	int		trig;
	int		here_doc;

    i = 0;
	trig = 0;
	cmd = NULL;
	flag_trig = 0;
	here_doc = 0;
    trigger = 0;
    count = 0;
	index = 0;
    stp = 0;
	while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL && is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]))
		i += 2;
	index = i;
	if (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
	{
		while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
		{
			if (is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]))
				break;
			flag_trig = 1;
			count++;
			i++;
		}
		if (count == 2 && cmd_w_flags(pa_tkns[pa_info->i].cmd_splitted[count - 2]))
		{
			if (ft_strchr(pa_tkns[pa_info->i].cmd_splitted[count - 1], '-'))
				flag_trig = 0;
		}
		while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
		{
			if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], "<") || !ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], "<<"))
			{
				trigger = 0;
				++i;
				while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
				{
					if (is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]))
						break;
					trigger++;
					i++;
				}
				if (trigger >= 1)
				{
					count = count + trigger - 1;
					if (trigger > 1)
						stp = 1;
				}
				else if (!stp)
				{
					if ((pa_tkns[pa_info->i].cmd_splitted[i] == NULL && ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i - 1], "<")) || !ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], "<"))
						count++;
					else if ((pa_tkns[pa_info->i].cmd_splitted[i] == NULL && strcmp(pa_tkns[pa_info->i].cmd_splitted[i - 1], "<<")) || !strcmp(pa_tkns[pa_info->i].cmd_splitted[i], "<<"))
						count++;
				}
			}
			else if (!stp)
			{
				if (is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]))
				{
					i += 2;
					if (pa_tkns[pa_info->i].cmd_splitted[i] == NULL || (pa_tkns[pa_info->i].cmd_splitted[i] != NULL && !is_rdr(pa_tkns[pa_info->i].cmd_splitted[i])))
						stp = 1;
				}
				else if (pa_tkns[pa_info->i].cmd_splitted[i + 1] != NULL && !ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i + 1], "<"))
				{
					count++;
					i++;
				}
				else if (pa_tkns[pa_info->i].cmd_splitted[i + 1] != NULL && !ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i + 1], "<<"))
				{
					count++;
					i++;
				}
				else
					i++;
			}
			else if (is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]))
			{
				i += 2;
				if (pa_tkns[pa_info->i].cmd_splitted[i] == NULL || ((pa_tkns[pa_info->i].cmd_splitted[i] != NULL) && !is_rdr(pa_tkns[pa_info->i].cmd_splitted[i])))
					stp = 1;
			}
			else
			{
				count++;
				i++;
			}
		}
		if (count == 1 || (count == 2 && cmd_w_flags(pa_tkns[pa_info->i].cmd_splitted[index]) && ft_strchr(pa_tkns[pa_info->i].cmd_splitted[index + 1], '-')))
		{
			while (i > index)
			{
				if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i - 1], "<"))
				{
					count++;
					break;
				}
				else if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i - 1], "<<"))
				{
					here_doc = 1;
					count++;
					break;
				}
				i--;
			}
		}
		cmd = (char **)malloc(sizeof(char *) * (count + 1));
		pa_tkns[pa_info->i].cmd_rdr = (char **)malloc(sizeof(char *) * (count + 1));
		i = 0;
		stp = 0;
		flag_trig = 0;
		count = 0;
		while (pa_tkns[pa_info->i].cmd_splitted[i] == NULL && is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]))
			i += 2;
		while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
		{
			if (is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]))
				break;
			flag_trig = 1;
			cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
			count++;
			i++;
		}
		/*Flag trigger needs to be turned off if cmd contains such commands(ls -la, wc -l, ls -l)*/
		if (count == 2 && cmd_w_flags(pa_tkns[pa_info->i].cmd_splitted[count - 2]))
		{
			if (ft_strchr(pa_tkns[pa_info->i].cmd_splitted[count - 1], '-'))
				flag_trig = 0;
		}
		while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
		{
			if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], "<") || !ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], "<<"))
			{
				trigger = 0;
				++i;
				while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
				{
					/*Trigger is applied here to check how many files are there after input redirection file*/
					/*Taking all the files after there is input redirection files if any and breaks out of the loop after encountered with any redirections*/
					if (is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]))
						break;
					if (trigger >= 1)
					{
						cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
						count++;
					}
					trigger++;
					i++;
				}
				/*If trigger is applied then stop trigger is applied*/
				if (trigger > 1)
					stp = 1;
			}
			else if (!stp)
			{
				/*If stp trigger is zero*/
				if (is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]))
				{
					i += 2;
					/*stp is triggered since there are more files after the output redirection file if the criteria meets*/
					if (pa_tkns[pa_info->i].cmd_splitted[i] == NULL || (pa_tkns[pa_info->i].cmd_splitted[i] != NULL && !is_rdr(pa_tkns[pa_info->i].cmd_splitted[i])))
						stp = 1;
				}
				else if (pa_tkns[pa_info->i].cmd_splitted[i + 1] != NULL && ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i + 1], "<"))
				{
					/*Taking the file before the input redirection sign*/
					cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
					count++;
					i++;
					/*Applying the trigger so that the function will not take the filename at the end*/
					trig = 1;
				}
				else if (pa_tkns[pa_info->i].cmd_splitted[i + 1] != NULL && ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i + 1], "<<"))
				{
					/*Taking the file before the input redirection sign*/
					cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
					count++;
					i++;
					/*Applying the trigger so that the function will not take the filename at the end*/
					trig = 1;
				}
				else
					i++;
			}
			else if (is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]))
			{
				i += 2;
				if (pa_tkns[pa_info->i].cmd_splitted[i] == NULL || ((pa_tkns[pa_info->i].cmd_splitted[i] != NULL) && !is_rdr(pa_tkns[pa_info->i].cmd_splitted[i])))
					stp = 1;
			}
			else
			{
				cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
				count++;
				i++;
			}
		}
		/*This condition is to take the file name at the end
		Special case scenario: wc < file < file2 < file4*/
		if (!stp && !trig && !flag_trig)
		{
			if (i <= 2 || ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i - 2], ">") || ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i - 2], ">>"))
			{
				if (ft_strcmp(cmd[count - 1], pa_tkns[pa_info->i].cmd_splitted[i - 1]))
				{
					cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i - 1]);
					count++;
				}
			}
		}
		/*This condition is to check if the count is 1 and after iterating the whole command, Going backwards to get the file*/ 
		if (count == 1 || (count == 2 && cmd_w_flags(cmd[0]) && ft_strchr(cmd[1], '-')))
		{
			while (i > index)
			{
				if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i - 1], "<"))
				{
					cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
					count++;
					break;
				}
				else if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i - 1], "<<"))
				{
					here_doc = 1;
					cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
					count++;
					break;
				}
				i--;
			}
		}
		cmd[count] = NULL;
		i = 0;
		while (cmd[i] != NULL)
		{
			pa_tkns[pa_info->i].cmd_rdr[i] = ft_strdup(cmd[i]);
			free(cmd[i]);
			i++;
		}
		pa_tkns[pa_info->i].cmd_rdr[i] = NULL;
		free(cmd);
		ft_putendl_fd("CMD", 1);
		print_2d_array(pa_tkns[pa_info->i].cmd_rdr);
		ft_putendl_fd("END", 1);
	}
}

void    parse_rdr_out(t_pars_tokens *pa_tkns, t_parser_info *pa_info)
{
	int	i;
	int	count;
	char	**cmd;
	int		index;

	i = 0;
	count = 0;
	cmd = NULL;
	while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL && is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]))
		i += 2;
	if (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
	{
		while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
		{
			if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
				break;
			else if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">>"))
				break;
			while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
			{
				if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
					break;
				else if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">>"))
					break;
				count++;
				i++;
			}
		}
		while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
		{
			if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
			{
				i += 2;
				if (pa_tkns[pa_info->i].cmd_splitted[i] == NULL)
					break;
				while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
				{
					if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
						break;
					else if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">>"))
						break;
					count++;
					i++;
				}
			}
			else if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">>"))
			{
				i += 2;
				if (pa_tkns[pa_info->i].cmd_splitted[i] == NULL)
					break;
				while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
				{
					if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
						break;
					else if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">>"))
						break;
					count++;
					i++;
				}
			}
			else
			{
				count++;
				i++;
			}
		}
		cmd = (char **)malloc(sizeof(char *) * (count + 1));
		pa_tkns[pa_info->i].cmd_rdr = (char **)malloc(sizeof(char *) * (count + 1));
		i = 0;
		count = 0;
		while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
		{
			if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
				break;
			else if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">>"))
				break;
			while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
			{
				if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
					break;
				else if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">>"))
					break;
				cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
				count++;
				i++;
			}
		}
		while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
		{
			if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
			{
				i += 2;
				if (pa_tkns[pa_info->i].cmd_splitted[i] == NULL)
					break;
				while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
				{
					if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
						break;
					else if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">>"))
						break;
					cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
					count++;
					i++;
				}
			}
			else if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">>"))
			{
				i += 2;
				if (pa_tkns[pa_info->i].cmd_splitted[i] == NULL)
					break;
				while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
				{
					if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
						break;
					else if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">>"))
						break;
					cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
					count++;
					i++;
				}
			}
			else
			{
				cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
				count++;
				i++;
			}
		}
		cmd[count] = NULL;
		i = 0;
		while (cmd[i] != NULL)
		{
			pa_tkns[pa_info->i].cmd_rdr[i] = ft_strdup(cmd[i]);
			free(cmd[i]);
			i++;
		}
		pa_tkns[pa_info->i].cmd_rdr[i] = NULL;
		ft_putendl_fd("CMD", 1);
		print_2d_array(pa_tkns[pa_info->i].cmd_rdr);
		ft_putendl_fd("END", 1);
		free(cmd);
	}
}

t_pars_tokens *parser (char **tokens)
{
    t_pars_tokens *pa_tkns;
    t_parser_info pa_info;

    //pa_info = malloc (sizeof (t_parser_info));
    init_parser_info(&pa_info, tokens);
    pa_tkns = malloc (sizeof (t_pars_tokens) * (pa_info.pipes_count));
    init_pa_tkns(pa_tkns, &pa_info);
    while (pa_info.j < pa_info.pipes_count)
    {
        pa_tkns[pa_info.j].fd_in = 0;
        pa_tkns[pa_info.j].fd_out = 0;
        pa_tkns[pa_info.j].is_in = 0;
        pa_tkns[pa_info.j].is_out = 0;
        pa_tkns[pa_info.j].is_out_appnd = 0;
        pa_tkns[pa_info.j].pipe = 0;
        pa_tkns[pa_info.j].here_doc = 0;
        allocate_cmd_memmory(&pa_info, tokens);
        while(tokens[pa_info.i])
        {
            if (pa_info.i > 0 && tokens[pa_info.i - 1] && tokens[pa_info.i - 1][0] == '|')
                pa_info.str = ft_strjoin(pa_info.str, tokens[pa_info.i - 1]);
            if(tokens[pa_info.i][0] == '|')
            {
                deal_with_pipes(pa_tkns, &pa_info, tokens);
                break ;
            }
            set_redirection_type(pa_tkns, &pa_info, tokens); 
            create_cmds(&pa_info, tokens);
        }
        set_pa_tokens(pa_tkns, &pa_info);
        pa_info.j++;
    }
    set_pipe_type(pa_tkns, &pa_info);
	pa_info.i = 0;

	char **f;
    while (pa_info.i < env.count)
    {
		
        f = find_input_file_names(pa_tkns, pa_info.i);
		ft_free_str_array(&pa_tkns[pa_info.i].cmd);
		pa_tkns[pa_info.i].cmd = f;
		pa_info.i++;
    }
	
    return (pa_tkns);    
}
