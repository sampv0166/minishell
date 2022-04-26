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
        else if (pa_tkns[pa_info->j].cmd_full[0] != '|' && pa_tkns[pa_info->j].cmd_full[ft_strlen(pa_tkns[pa_info->j].cmd_full) - 1] == '|')
        {
            pa_tkns[pa_info->j].pipe_read_end = 0;
            pa_tkns[pa_info->j].pipe_write_end = 1;
            pa_tkns[pa_info->j].pipe = 2;
        }
        else if (pa_tkns[pa_info->j].cmd_full[0] == '|' && pa_tkns[pa_info->j].cmd_full[ft_strlen(pa_tkns[pa_info->j].cmd_full) - 1] != '|')
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

    heredoc = NULL;
    if (pipe(end) == -1)
		return (ft_perror(EXIT_FAILURE, "pipe error"));    
	heredoc = cmd_split[pa_info->i + 1];
	if (heredoc == NULL)
		return (exit_close_fds(end[0], end[1], EXIT_FAILURE));
    //printf("%s",heredoc);    
    while (true)
	{
		buf = readline("> ");
		if (buf == NULL)
			return (exit_close_fds(end[1], -1, EXIT_SUCCESS));
		if (ft_strcmp(buf, heredoc) == 0)
			break ;
        ft_putstr_fd(buf, end[1]);
        ft_putchar_fd('\n', end[1]);
		free(buf);
	}
    close(end[1]);
    //pa_tkns[pa_info->j].fd_in = end[0];
    pa_tkns[pa_info->j].here_doc_fd = end[0];
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
    pa_info->arr[pa_info->len] = NULL;
    pa_info->str = ft_strjoin (pa_info->str, tokens[pa_info->i]);
    pa_info->arr1[pa_info->len] = ((char *)0);
    pa_info->len++;
    pa_info->i++;
    pa_tkns[pa_info->j].fd_out = STDOUT_FILENO;
    pa_tkns[pa_info->j].is_in = 0;
    pa_tkns[pa_info->j].is_out = 0;
    pa_tkns[pa_info->j].is_out_appnd = 0;
    pa_tkns[pa_info->j].pipe = 0;

}
void create_cmds(t_parser_info *pa_info, char **tokens)
{
    pa_info->arr[pa_info->len] = ft_strdup(tokens[pa_info->i]);
    if(!(tokens[pa_info->i][0] == '>' && tokens[pa_info->i][1] == '>') && tokens[pa_info->i][0] != '>' && !(tokens[pa_info->i][0] == '<' && tokens[pa_info->i][1] == '<') && tokens[pa_info->i][0] != '<')
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

void    parse_rdr_in(t_pars_tokens *pa_tkns, t_parser_info *pa_info)
{
    int i;
    int count;
	int		flag_trig;
    char    **cmd;
    int     trigger;
    int     stp;
	int		trig;
	char	*str;

    i = 0;
	trig = 0;
	flag_trig = 0;
    trigger = 0;
    count = 0;
	str = NULL;
    stp = 0;
    if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[0], "<"))
        i = 2;
	str = get_abs_cmd(pa_tkns[pa_info->i].cmd_splitted[i]);
    if (!is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]) && !access(str, X_OK))
    {
        count++;
        i++;
    }
	free(str);
	while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
	{
		if (is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]))
			break;
		flag_trig = 1;
		count++;
		i++;
	}
    while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
    {
        if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], "<"))
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
	if (count == 1)
	{
		while (i > 0)
		{
			if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i - 1], "<"))
			{
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
    if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[0], "<"))
        i = 2;
	str = get_abs_cmd(pa_tkns[pa_info->i].cmd_splitted[i]);
    if (!is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]) && !access(str, X_OK))
    {
        cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
        count++;
        i++;
    }
	while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
	{
		if (is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]))
			break;
		flag_trig = 1;
		cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
		count++;
		i++;
	}
    while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
    {
        if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], "<"))
        {
			trigger = 0;
            ++i;
            while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
            {
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
            if (trigger > 1)
                stp = 1;
        }
		else if (!stp)
		{
			if (is_rdr(pa_tkns[pa_info->i].cmd_splitted[i]))
			{
				i += 2;
				if (pa_tkns[pa_info->i].cmd_splitted[i] == NULL || (pa_tkns[pa_info->i].cmd_splitted[i] != NULL && !is_rdr(pa_tkns[pa_info->i].cmd_splitted[i])))
					stp = 1;
			}
			else if (pa_tkns[pa_info->i].cmd_splitted[i + 1] != NULL && ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i + 1], "<"))
			{
				cmd[count] = strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
				count++;
				i++;
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
    if (!stp && !trig && !flag_trig)
    {
		if (i <= 2 || ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i - 2], ">"))
		{
			cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i - 1]);
			count++;
		}
    }
    cmd[count] = NULL;
    if (count == 1)
	{
		while (i > 0)
		{
			if (!strcmp(pa_tkns[pa_info->i].cmd_splitted[i - 1], "<"))
			{
				cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
				count++;
				break;
			}
			i--;
		}
	}
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
    free(cmd);
	free(str);
	ft_putendl_fd("END", 1);
}

void    parse_rdr_out(t_pars_tokens *pa_tkns, t_parser_info *pa_info)
{
	int	i;
	int	count;
	char	**cmd;
	char	*str;

	i = 0;
	count = 0;
	str = get_abs_cmd(pa_tkns[pa_info->i].cmd_splitted[i]);
	if (!access(str, X_OK))
	{
		count++;
		i++;
		free(str);
	}
	while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
	{
		if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
			break;
		while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL && ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
		{
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
			while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL && ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
			{
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
	str = get_abs_cmd(pa_tkns[pa_info->i].cmd_splitted[i]);
	if (!access(str, X_OK))
	{
		cmd[count] = ft_strdup(pa_tkns[pa_info->i].cmd_splitted[i]);
		count++;
		i++;
		free(str);
	}
	while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL)
	{
		if (!ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
			break;
		while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL && ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
		{
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
			while (pa_tkns[pa_info->i].cmd_splitted[i] != NULL && ft_strcmp(pa_tkns[pa_info->i].cmd_splitted[i], ">"))
			{
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

t_pars_tokens *parser (char **tokens)
{
    t_pars_tokens *pa_tkns;
    t_parser_info *pa_info;
    pa_info = malloc (sizeof (t_parser_info));
    init_parser_info(pa_info, tokens);
    pa_tkns = malloc (sizeof (t_pars_tokens) * (pa_info->pipes_count));
    init_pa_tkns(pa_tkns, pa_info);
    while (pa_info->j < pa_info->pipes_count)
    {
        pa_tkns[pa_info->j].fd_in = 0;
        pa_tkns[pa_info->j].fd_out = 0;
        pa_tkns[pa_info->j].is_in = 0;
        pa_tkns[pa_info->j].is_out = 0;
        pa_tkns[pa_info->j].is_out_appnd = 0;
        pa_tkns[pa_info->j].pipe = 0;
        pa_tkns[pa_info->j].here_doc = 0;
        allocate_cmd_memmory(pa_info, tokens);
        while(tokens[pa_info->i])
        {
            if (pa_info->i > 0 && tokens[pa_info->i - 1] && tokens[pa_info->i - 1][0] == '|')
                pa_info->str = ft_strjoin(pa_info->str, tokens[pa_info->i - 1]);
            if(tokens[pa_info->i][0] == '|')
            {
                deal_with_pipes(pa_tkns, pa_info, tokens);
                break ;
            }
            set_redirection_type(pa_tkns, pa_info, tokens); 
            create_cmds(pa_info, tokens);
        }
        set_pa_tokens(pa_tkns, pa_info);
        pa_info->j++;
    }
    set_pipe_type(pa_tkns, pa_info);
    // printf("is_in: %d\n", pa_tkns->is_in);
    // printf("is_out: %d\n", pa_tkns->is_out);
    // printf("is_out_append: %d\n", pa_tkns->is_out_appnd);
    // printf("here_doc: %d\n", pa_tkns->here_doc);
    // printf("Pipes: %d\n", pa_tkns->pipe);
    pa_info->i = 0;
    pa_info->j = 0;

    // while (pa_info->i < pa_info->pipes_count)
    // {
    //     if((pa_tkns[pa_info->i].is_in && pa_tkns[pa_info->i].is_out) || pa_tkns[pa_info->i].is_in)
    //     {
	// 		parse_rdr_in(pa_tkns, pa_info);
    //     }
    //     else if(pa_tkns[pa_info->i].is_out && !pa_tkns[pa_info->i].is_in)
    //     {
    //         parse_rdr_out(pa_tkns, pa_info);
    //     }
    //     pa_info->i++;
    // }

    //if ((pa_tkns->is_in == 1) && !pa_tkns->is_out && !pa_tkns->is_out_appnd && !pa_tkns->here_doc && !pa_tkns->pipe)
       // parse_rdr(pa_tkns, pa_info);  
    return (pa_tkns);    
}

            // if(ft_strchr(str, '|'))
        //     pa_tkns[j].pipe = 1;   
    //ls -la | wc -l | wc -l
    // printf("%ld", ft_strlen(pa_tkns[j].cmd_full));

    // k = pipes_count;

// int get_pipe_len(char **tokens)
// {
//     int i;
//     int len;

//     i = 0;
//     len = 0;

//     while (tokens[i])
//     {
//         if(tokens[i][0] == '|')
//             len++;
//         i++;
//     }
//     return (len);
// }

// int get_count(char **tkns)
// {
//     int i;

//     i = 0;

//     while(tkns[i])
//     {
//         if(tkns[i][0] == '|')
//             return (++i);
//         i++;    
//     }
//     return (i);
// }

// void init_pa_info(t_parser_info *pa_info, char **tokens, t_pars_tokens *pa_tkns)
// {
//     pa_info->pipes_count = 0;
//     pa_info->i = 0;
//     pa_info->k = 0;
//     pa_info->j = 0;
//     pa_info->pipes_count = get_pipe_len(tokens) + 1;
//     pa_tkns = malloc (sizeof (t_pars_tokens) * pa_info->pipes_count + 1);
// }
// t_pars_tokens *parser (char **tokens)
// {
//     t_pars_tokens *pa_tkns;
//     t_parser_info pa_info;
//     init_pa_info(&pa_info, tokens, pa_tkns);


    
    // pa_tkns[pa_info->pipes_count + 1].cmd = NULL;
    // pa_tkns[pa_info.pipes_count + 1].cmd_splitted = NULL;
    // pa_tkns[pa_info.pipes_count + 1].cmd_full = NULL;
    // pa_tkns[pa_info.pipes_count + 1].fd_in = STDIN_FILENO;
    // pa_tkns[pa_info.pipes_count + 1].fd_out = STDOUT_FILENO;
    // pa_tkns[pa_info.pipes_count + 1].pipe = 0;
    // pa_tkns[pa_info.pipes_count + 1].is_in = 0;
    // pa_tkns[pa_info.pipes_count + 1].is_out = 0;
    // pa_tkns[pa_info.pipes_count + 1].is_out_appnd = 0;
    // pa_tkns[pa_info.pipes_count + 1].here_doc = 0;
//     env.count = pa_info.pipes_count;
//     pa_info.k = pa_info.pipes_count;
    
//     while (pa_info.pipes_count)
//     {
//         int len;
//         char **arr;
//         len = get_count(tokens);
//         arr = malloc (sizeof (char *) * len + 1);
    
//         char **arr1;
//         len = get_count(tokens);

//         arr1 = malloc (sizeof (char *) * len);
//         char *str;    
//         str = malloc (sizeof (char) * 1);
//         len = 0;

//         while(tokens[pa_info.i])
//         {
//             if (pa_info.i > 0 && tokens[pa_info.i - 1] && tokens[pa_info.i - 1][0] == '|')
//             {
//                 str = ft_strjoin (str, tokens[pa_info.i - 1]);
//             }
//             if(tokens[pa_info.i][0] == '|')
//             {
//                 arr[len] = ft_strdup(tokens[pa_info.i]);
//                 str = ft_strjoin (str, tokens[pa_info.i]);
//                 len++;
//                 //if(tokens[i])
//                 pa_info.i++;
//                 break ;
//             }
//             if(tokens[pa_info.i][0] == '>' && tokens[pa_info.i][1] == '>')
//                 pa_tkns[pa_info.j].is_out_appnd = 1; 
//             else if(tokens[pa_info.i][0] == '>')
//                 pa_tkns[pa_info.j].is_out = 1;
//             if(tokens[pa_info.i][0] == '<' && tokens[pa_info.i][1] == '<')
//                 pa_tkns[pa_info.j].here_doc = 1;
//             else if(tokens[pa_info.i][0] == '<')
//                 pa_tkns[pa_info.j].is_in = 1;              
//             arr[len] = ft_strdup(tokens[pa_info.i]);
//             if(!(tokens[pa_info.i][0] == '>' && tokens[pa_info.i][1] == '>') && tokens[pa_info.i][0] != '>' && !(tokens[pa_info.i][0] == '<' && tokens[pa_info.i][1] == '<') && tokens[pa_info.i][0] != '<')
//                 arr1[len] = ft_strdup(tokens[pa_info.i]);

//             str = ft_strjoin (str, tokens[pa_info.i]);
//             len++;
//             pa_info.i++;
//         }
//         arr[len] = NULL;
//         arr1[len] = NULL;
//         pa_tkns[pa_info.j].cmd_splitted = arr;
//         pa_tkns[pa_info.j].cmd = arr1;
//         pa_tkns[pa_info.j].cmd_full = str;
//         pa_tkns[pa_info.j].fd_in = STDIN_FILENO;
//         pa_tkns[pa_info.j].fd_out = STDOUT_FILENO;
//         // if(ft_strchr(str, '|'))
//         //     pa_tkns[j].pipe = 1;       
//         pa_info.pipes_count--;
//         pa_info.j++;
//     }
//     pa_info.j = 0;
//     //ls -la | wc -l | wc -l
//     // printf("%ld", ft_strlen(pa_tkns[j].cmd_full));
   
//     while (pa_info.j < env.count)
//     {
//         if ((pa_tkns[pa_info.j].cmd_full && pa_tkns[pa_info.j].cmd_full[0] == '|') && (pa_tkns[pa_info.j].cmd_full[ft_strlen(pa_tkns[pa_info.j].cmd_full) - 1] == '|'))
//         {
//             pa_tkns[pa_info.j].pipe_read_end = 1;
//             pa_tkns[pa_info.j].pipe_write_end = 1;
//             pa_tkns[pa_info.j].pipe = 3;
//         }
//         else if (pa_tkns[pa_info.j].cmd_full[0] != '|' && pa_tkns[pa_info.j].cmd_full[ft_strlen(pa_tkns[pa_info.j].cmd_full) - 1] == '|')
//         {
//             pa_tkns[pa_info.j].pipe_read_end = 0;
//             pa_tkns[pa_info.j].pipe_write_end = 1;
//             pa_tkns[pa_info.j].pipe = 2;
//         }
//         else if (pa_tkns[pa_info.j].cmd_full[0] == '|' && pa_tkns[pa_info.j].cmd_full[ft_strlen(pa_tkns[pa_info.j].cmd_full) - 1] != '|')
//         {
//             pa_tkns[pa_info.j].pipe_read_end = 1;
//             pa_tkns[pa_info.j].pipe_write_end = 0;
//             pa_tkns[pa_info.j].pipe = 1;             
//         }
//         pa_info.j++;
//     }
//     return (pa_tkns);    
// }