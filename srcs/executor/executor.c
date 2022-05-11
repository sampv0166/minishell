#include "../../includes/mini_shell.h"

extern t_env_var env;

static bool is_redir(t_pars_tokens *pa_tok, int i)
{
    if (pa_tok[i].is_in == 1 || pa_tok[i].is_out == 1 || pa_tok[i].here_doc == 1 || pa_tok[i].pipe || pa_tok[i].is_out_appnd == 1 )
        return (true);
    return (false);
}

int handle_pipes(t_pars_tokens *pa_tokens, int i)
{
    int fd[2];
    pipe(fd);
    pa_tokens[i].fd_in = fd[0];
    pa_tokens[i].fd_out = fd[1];  
    env.fd_in = fd[0];
    env.fd_out = fd[1]; 
    env.fd_pipe_in_open = fd[0];
    env.fd_pipe_out_open= fd[1];

	return (0);
}

static int init(char ***path_splitted)
{
    char *path;
    
    path = get_env_value("PATH");
    if (path == NULL)
        return (EXIT_FAILURE);    
    *path_splitted = ft_split(path, ':');
    free(path);
    if (*path_splitted == NULL)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

void	*ft_free(void **p)
{
	if (p == NULL)
		return (NULL);
	free(*p);
	*p = NULL;
	return (NULL);
}


char	*ft_strjoin2(char *saved_line, char *buffer)
{
	char	*new_string;
	int		total_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	total_len = ft_strlen(saved_line) + ft_strlen(buffer) + 1;
	new_string = (char *) malloc(sizeof(char) * (total_len));
	if (new_string == NULL)
		return (NULL);
	while (saved_line && saved_line[i])
		new_string[i++] = saved_line[j++];
	j = 0;
	while (buffer && buffer[j])
		new_string[i++] = buffer[j++];
	new_string[i] = '\0';
	return (new_string);
}


static char *get_abs_cmd_path(char **abs_cmd_path,char *path_splitted, char *cmd)
{ 
    *abs_cmd_path = ft_strjoin2(path_splitted, "/");
    if (abs_cmd_path == NULL)
        return (NULL);   
    *abs_cmd_path = ft_strjoin(*abs_cmd_path, cmd);
    if (*abs_cmd_path == NULL)
        return (*abs_cmd_path);  
    return (*abs_cmd_path);
}
void	*ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		free_me(&split[i]);
		i++;
	}
    free(split);
	return (NULL);
}

char *get_abs_cmd(char *cmd)
{
    char *abs_cmd_path;
    char **path_split;
    char *dup;
    int i;
    if(!cmd)
        return (cmd);
    if (access(cmd, X_OK) == 0)
    {
        return (ft_strdup(cmd));
    }
    init(&path_split);
    i = 0;
    while (path_split[i])
    {
        abs_cmd_path = get_abs_cmd_path(&abs_cmd_path, path_split[i], cmd);
        dup = ft_strdup(abs_cmd_path);
        if (abs_cmd_path == NULL)
            return (NULL);
        if (access(abs_cmd_path, X_OK) == 0)
        {
            ft_free_split(path_split);
            env.split = path_split;
            free_me(&abs_cmd_path);
            return (dup);
        }
        else
        {
            free_me(&dup);
            free_me(&abs_cmd_path);
        }
        i++;
    }
    ft_free_split(path_split);
	return (NULL);
}

void handle_pipe_type_one(t_pars_tokens *pa_tokens, int i)
{
    if (!pa_tokens[i].pipe && pa_tokens[i].fd_out || pa_tokens[i].is_out_appnd || pa_tokens[i].is_in ||  pa_tokens[i].here_doc)
    {    
        if (pa_tokens[i].fd_out != STDOUT_FILENO)
        {
            if (dup2(pa_tokens[i].fd_out, STDOUT_FILENO) == -1)
                exit(1);   
        }
        if (pa_tokens[i].is_in || pa_tokens[i].here_doc)
        {
            if (dup2(pa_tokens[i].fd_in, STDIN_FILENO) == -1)
                exit(1);   
        }
    }
    if (pa_tokens[i].pipe == 1)
    {
        close(pa_tokens[i].fd_in);
        if (dup2(pa_tokens[i - 1].fd_in, STDIN_FILENO) == -1)
            exit(1);          
        if (pa_tokens[i].fd_out != STDOUT_FILENO && (pa_tokens[i].is_out || pa_tokens[i].is_out_appnd))
        {
            if (dup2(pa_tokens[i].fd_out, STDOUT_FILENO) == -1)
                exit(1);   
        }
    }
}

void handle_pipe_type_2_3(t_pars_tokens *pa_tokens, int i)
{
    if (pa_tokens[i].pipe == 3)
    {
        if (dup2(pa_tokens[i - 1].fd_in, STDIN_FILENO) == -1)
             exit(1);
        if (dup2(pa_tokens[i].fd_out, STDOUT_FILENO) == -1)
             exit(1);
        close(pa_tokens[i - 1].fd_in);
        close(pa_tokens[i].fd_in);
        close(pa_tokens[i].fd_out);
    }
    if (pa_tokens[i].pipe == 2)
    {
        close(pa_tokens[i].fd_in);
        if (dup2(pa_tokens[i].fd_out, STDOUT_FILENO) == -1)
             exit(1);      
        close(pa_tokens[i].fd_out);
    }
}

void    placing_vals_SHLVL(char *str)
{
    int i;
    char    *tmp;

    i = get_env("SHLVL");
    tmp = NULL;
    if (env.env_var[i] == NULL)
    {
        tmp = ft_strdup("SHLVL=");
        tmp = ft_strjoin(tmp, str);
        env.env_var = new_env(tmp);
        free(tmp);
    }
    else
    {
        free(env.env_var[i]);
        env.env_var[i] = ft_strdup("SHLVL=");
        env.env_var[i] = ft_strjoin(env.env_var[i], str);
    }
    free(str);
}

void    increment_s_vals(void)
{
    int     i;
    char    *tmp;
    char    *str;

    str = NULL;
    tmp = ft_strdup("$");
    tmp = ft_strjoin(tmp, "SHLVL");
    i = get_env("SHLVL");
    if (env.env_var[i] == NULL)
        str = ft_strdup("0");
    else
        str = get_env_dollar(tmp);
    free(tmp);
    i = ft_atoi(str);
    i++;
    free(str);
    str = ft_itoa(i);
    placing_vals_SHLVL(str);
}

int exec_child(t_pars_tokens *pa_tokens, char *abs_path, int i)
{
    // pa_tokens[i].cmd[1] = NULL;
    // free(abs_path);
    // abs_path = ft_strdup("/bin/");
    // abs_path = ft_strjoin(abs_path, pa_tokens[i].cmd[0]);
    if (!ft_strcmp(pa_tokens[i].cmd[0], "./minishell"))
        increment_s_vals();
    env.stat_code = execve(abs_path, pa_tokens[i].cmd, env.env_var);
    if (env.stat_code)
    {
        // ft_putendl_fd("2", 2);
    }
    return (env.stat_code);
    //exit(0);
}

int ft_perror(int exit_status, char *msg)
{
    perror(msg);
    return (exit_status);
}

int handle_input_redirections(char **cmd_split, t_pars_tokens *pa_tokens, int tkn_idx)
{
    int i;
    int fd;

    i = 0;
    fd = 0;
    while (cmd_split[i])
    {
        if (cmd_split[i][0] == '<' && ft_strlen(cmd_split[i]) == 1 && cmd_split[++i])
        {
            fd = open(ft_strdup(cmd_split[i]), O_RDONLY);
            if (fd == -1)
                return (ft_perror(EXIT_FAILURE, "error opening file"));
        }
        if (cmd_split[i][0] == '<' && cmd_split[i][1] == '<' && ft_strlen(cmd_split[i]) == 2)
        {
            return(EXIT_SUCCESS);
        }
        i++;
    }
    pa_tokens[tkn_idx].fd_in = fd;
    return (EXIT_SUCCESS);
}

int  handle_output_redirections(char **cmd_split, t_pars_tokens *pa_tokens, int tkn_idx)
{
    int i;
    int fd;

    i = 0;
    fd = 0;
  
    if(!(pa_tokens[tkn_idx].is_in && pa_tokens[tkn_idx].here_doc))
    {
        while (cmd_split[i])
        {
            
            if (cmd_split && cmd_split[i] && (cmd_split[i][0] == '>' && ft_strlen(cmd_split[i]) == 1 && cmd_split[i + 1]))
            {
                if(fd != 0)
                    close(fd);
                fd = open(cmd_split[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
                if (fd == -1)
                    return (ft_perror(EXIT_FAILURE, "error opening file"));
            }
            if (cmd_split[i] && (cmd_split[i][0] == '>' && cmd_split[i][1] == '>' && ft_strlen(cmd_split[i]) == 2 && cmd_split[i + 1]))
            {
                if(fd != 0)
                    close(fd);
                fd = open(cmd_split[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
                if (fd == -1)
                    return (ft_perror(EXIT_FAILURE, "error opening file")); 
            }
            i++;
        }
    }
    pa_tokens[tkn_idx].fd_out = fd;
    if(pa_tokens[tkn_idx].pipe)
        close(env.fd_out);    
    env.fd_out = fd;
    if(pa_tokens[tkn_idx].is_out)
        env.open_fd_out = fd;

    return (EXIT_SUCCESS);
}

int handle_redirections(t_pars_tokens *pa_tokens, int i)
{
    if(pa_tokens[i].pipe)
    {
        handle_pipes(pa_tokens,i);
    }
    // if(pa_tokens[i].is_in || pa_tokens[i].here_doc)
    // {
    //     if (handle_input_redirections(pa_tokens[i].cmd_splitted, pa_tokens,i) == EXIT_FAILURE)
    //         return (EXIT_FAILURE);
    // }
    if(pa_tokens[i].is_out || pa_tokens[i].is_out_appnd)
    {
        if(pa_tokens[i].is_in == 0 && pa_tokens[i].here_doc == 0)
            if (handle_output_redirections(pa_tokens[i].cmd_splitted, pa_tokens,i) == EXIT_FAILURE)
                return (EXIT_FAILURE);
    }   
    else if(pa_tokens[i].pipe == 1)
    {
        env.fd_out = dup(env.tmp_out);
    }
	return (EXIT_SUCCESS);
}

void replace_quote (t_pars_tokens *pa_tkns, int i)
{
    int j;
    j = 1;

    while (pa_tkns[i].cmd && pa_tkns[i].cmd[j])
    {
        if(pa_tkns[i].cmd && token_contains_quote(pa_tkns[i].cmd[j]))
        {
            if(pa_tkns[i].cmd[j] && pa_tkns[i].cmd[j][0] == '\"' && pa_tkns[i].cmd[j][ft_strlen(pa_tkns[i].cmd[j]) - 1] == '\"' )
            {
                pa_tkns[i].cmd[j][ft_strlen(pa_tkns[i].cmd[j]) - 1] = '\0';
                pa_tkns[i].cmd[j] = ft_strdup(pa_tkns[i].cmd[j] + 1);
            }    
        }
        j++;
    }
}

int ft_eco_check(char *str)
{
    int i;

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

// void close_fds(t_pars_tokens *pa_tokens, int i)
// {
//     if (pa_tokens[i].pipe == 1)
//     {
//         close(pa_tokens[i].fd_in);
//         close(pa_tokens[i - 1].fd_in);
//         close(pa_tokens[i].fd_out);

//     }
//     else if (pa_tokens[i].pipe == 3)
//     {
//         close(pa_tokens[i].fd_out);
//         close(pa_tokens[i - 1].fd_in);
//     }
//     else if (pa_tokens[i].pipe == 2)
//         close(pa_tokens[i].fd_out);
// }

int execute_cmd(t_pars_tokens *pa_tokens, int i, char **path)
{
    char *abs_cmd_path;
    abs_cmd_path = NULL;
    if (is_redir(pa_tokens, i))
    {
        if(handle_redirections(pa_tokens, i))
            return (EXIT_FAILURE);
    }
    dup2(env.fd_out, 1);
    close(env.fd_out);
    if(pa_tokens[i].cmd[0])
    {
        if(is_inbuilt(pa_tokens[i].cmd[0]))
        {
            return (handle_inbuilt_redir(pa_tokens, i));
        }
    }
    if(pa_tokens[i].cmd && (env.env_var[get_env("PATH")] != NULL))
    {
        //ft_putstr_fd(pa_tokens[i].cmd[0], 2);
        abs_cmd_path = get_abs_cmd(pa_tokens[i].cmd[0]);
        *path = abs_cmd_path;
    }
    if(abs_cmd_path == NULL)
    {
        if(pa_tokens[i].cmd[0])
        {
            if(is_inbuilt(pa_tokens[i].cmd[0]))
                return (0);
        }
        else
        {
            // printf (":::command not found\n");
            env.stat_code = 0;
			return(0);  
        }
    }
    // ft_putchar_fd('\n', 2);
    // ft_putstr_fd(abs_cmd_path, 2);
    // ft_putnbr_fd(i, 2);
    if(abs_cmd_path)
    {
        if (access(abs_cmd_path, X_OK) == 0)
        {
            int f;
            f = 0;

            while (pa_tokens[i].cmd[f])
            {
                delimit_qtes(pa_tokens[i].cmd[f]);
                f++;
            }
        }
    }
    else
    {
        ft_putstr_fd("::command not found\n", 2);
        env.stat_code = 127;
        return(127);
    }

    
    // //close_fds(pa_tokens, i);
    // env.stat_code =  WEXITSTATUS(env.stat_code);
	return (env.stat_code);
}

int check_for_input_files(t_pars_tokens *pa_tkns, int i)
{
    int j;
    j = 0;
   
    while(pa_tkns[i].cmd_splitted[j])
    {
        if(pa_tkns[i].cmd_splitted[j] && pa_tkns[i].cmd_splitted[j][0] == '<' || pa_tkns[i].cmd_splitted[j][0] == '>')
        {
            j++;
            if(pa_tkns[i].cmd_splitted[j])
                j++;
        }
        if(pa_tkns[i].cmd_splitted[j] &&  (pa_tkns[i].cmd_splitted[j][0] == '<' || pa_tkns[i].cmd_splitted[j][0] == '>'))
            continue;
        else
        {
            j++;
            break ;
        }
    }
    while(pa_tkns[i].cmd_splitted && pa_tkns[i].cmd_splitted[j])
    {
        if(pa_tkns[i].cmd_splitted[j] && pa_tkns[i].cmd_splitted[j][0] == '<' || pa_tkns[i].cmd_splitted[j][0] == '>')
        {
            j++;
            if(pa_tkns[i].cmd_splitted[j])
                j++;
        }
        if(pa_tkns[i].cmd_splitted[j] &&  (pa_tkns[i].cmd_splitted[j][0] == '<' || pa_tkns[i].cmd_splitted[j][0] == '>'))
        {
            continue;
        }
        else if(pa_tkns[i].cmd_splitted[j])
        {
            if(access(pa_tkns[i].cmd_splitted[j], F_OK) == 0)
            {
                return(1);
            }
            else
            {
                j++;
                continue;    
            }
        }
        else
        {
            break;
        }
    }
    return (0);
}

int get_2d_arr_len(char **arr)
{
    int i;
    i = 0;

    while(arr && arr[i])
    {
        i++;
    }
    if(i != 0)
        i = i - 1;
    return (i);
}

int get_2d_arr_len2(char **arr)
{
    int i;
    i = 0;
    
    while(arr && arr[i])
    {
        i++;
    }
    return (i);
}


int open_files(char **cmd_split, int i)
{
    int fd;
    fd = 0;
    while (cmd_split[i] && i >= 0)
    {
        if (cmd_split[i] && cmd_split[i][0] == '<' && ft_strlen(cmd_split[i]) == 1)
        {
            fd = open(cmd_split[i + 1], O_RDONLY);
            if (fd == -1)
                return (ft_perror(EXIT_FAILURE, "error opening file"));
        }
        i--;
        if(i < 0)
            break;
    }
}

void find_input_fd(t_pars_tokens  *pa_tkns,int i)
{
    int len;
    int j;
    int fd;
    len = get_2d_arr_len(pa_tkns[i].cmd_splitted);
    j = len;
    fd = 0; 
    while(pa_tkns[i].cmd_splitted[j] && j >=0)
    {
        if(pa_tkns[i].cmd_splitted[j] && pa_tkns[i].cmd_splitted[j][0] == '<')
        {
                // ft_putnbr_fd(pa_tkns[i].here_doc_fd, 2);
                // env.fd_in = pa_tkns[i].here_doc_fd;
            if(ft_strlen(pa_tkns[i].cmd_splitted[j]) == 1)
            {
                // fd = open(pa_tkns[i].cmd_splitted[j + 1], O_RDONLY);
                // if (fd == -1)
                //     ft_perror(EXIT_FAILURE, "error opening file");
                //env.fd_in = fd;
               // return (0);
                //open_files(pa_tkns[i].cmd_splitted , j);
                break;
            }
            else
            {
                env.fd_in = pa_tkns[i].here_doc_fd;
                env.open_heredoc_fdin = pa_tkns[i].here_doc_fd;
                //open_files(pa_tkns[i].cmd_splitted , j);
              break;  
            }
        }
        j--;
    }
}

int get_files_arr_len(t_pars_tokens *pa_tkns, int i)
{
    int len ;
    int j;
    len = 0;
    j = 0;
    while(pa_tkns[i].cmd_splitted[j])
    {

        if(pa_tkns[i].cmd_splitted[j] && pa_tkns[i].cmd_splitted[j][0] == '<' || pa_tkns[i].cmd_splitted[j][0] == '>')
        {
            j++;
            if(pa_tkns[i].cmd_splitted[j])
                j++;  
        }
        if(pa_tkns[i].cmd_splitted[j] &&  (pa_tkns[i].cmd_splitted[j][0] == '<' || pa_tkns[i].cmd_splitted[j][0] == '>'))
            continue;
        else if(pa_tkns[i].cmd_splitted[j])
        {
            len++;
            j++;
        }
        else
            break;
    }
    while(pa_tkns[i].cmd_splitted[j])
    {
        if(pa_tkns[i].cmd_splitted[j] && pa_tkns[i].cmd_splitted[j][0] == '<' || pa_tkns[i].cmd_splitted[j][0] == '>')
        {
            j++;
            if(pa_tkns[i].cmd_splitted[j])
                j++;
        }
        if(pa_tkns[i].cmd_splitted[j] &&  pa_tkns[i].cmd_splitted[j][0] == '<' || pa_tkns[i].cmd_splitted[j][0] == '>')
        {
            continue;
        }
        else if(pa_tkns[i].cmd_splitted[j])
        {
            j++;
            len++;
        }
        else
            break;
    }
    return (len);
}

char **find_input_file_names(t_pars_tokens *pa_tkns, int i)
{
    int j;
    int arr_len;
    j = 0;

    int len;
    len = get_files_arr_len(pa_tkns, i);
    char **files;
    arr_len = 0;
    files = (char ** ) malloc(sizeof (char *) * (len + 1));
    while(pa_tkns[i].cmd_splitted[j])
    {
        if(pa_tkns[i].cmd_splitted[j] && pa_tkns[i].cmd_splitted[j][0] == '<' || pa_tkns[i].cmd_splitted[j][0] == '>')
        {
            j++;
            if(pa_tkns[i].cmd_splitted[j])
                j++;
        }
        if(pa_tkns[i].cmd_splitted[j] &&  (pa_tkns[i].cmd_splitted[j][0] == '<' || pa_tkns[i].cmd_splitted[j][0] == '>'))
            continue;
        else if(pa_tkns[i].cmd_splitted[j])
        {        
            files[arr_len++] =ft_strdup(pa_tkns[i].cmd_splitted[j]);
            j++;
        }
        else
        {    
            break;
        }

    }
    while(pa_tkns[i].cmd_splitted[j])
    {
        if(pa_tkns[i].cmd_splitted[j] && pa_tkns[i].cmd_splitted[j][0] == '<' || pa_tkns[i].cmd_splitted[j][0] == '>')
        {
            j++;
            if(pa_tkns[i].cmd_splitted[j])
                j++;
        }
        if(pa_tkns[i].cmd_splitted[j] &&  (pa_tkns[i].cmd_splitted[j][0] == '<' || pa_tkns[i].cmd_splitted[j][0] == '>'))
        {
            continue;
        }
        else if(pa_tkns[i].cmd_splitted[j])
        {   
            files[arr_len++] = ft_strdup(pa_tkns[i].cmd_splitted[j]);
            j++;
        }
        else
            break;
    }
    files[arr_len] = NULL;
    j = 0;
    return (files);
}

void close_redir_fd(int *fd)
{
    if(*fd != 0)
        close(*fd);  
}

int open_fds(char **cmd_split, int i, int *fd_out, int *fd_in)
{
    if (cmd_split && cmd_split[i] && (cmd_split[i][0] == '>' && ft_strlen(cmd_split[i]) == 1 && cmd_split[i + 1]))
    {
        close_redir_fd(fd_out);
        *fd_out = open(cmd_split[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (*fd_out == -1)
            return (ft_perror(EXIT_FAILURE, "error opening file"));
    }
    if (cmd_split[i] && (cmd_split[i][0] == '>' && cmd_split[i][1] == '>' && ft_strlen(cmd_split[i]) == 2 && cmd_split[i + 1]))
    {
        close_redir_fd(fd_out);    
        *fd_out = open(cmd_split[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
        if (*fd_out == -1)
            return (ft_perror(EXIT_FAILURE, "error opening file")); 
    }
    if (cmd_split[i][0] == '<' && ft_strlen(cmd_split[i]) == 1 && cmd_split[i + 1])
    {
        close_redir_fd(fd_in);    
        *fd_in = open(cmd_split[i + 1], O_RDONLY);
        if (*fd_in == -1)
            return (ft_perror(EXIT_FAILURE, "error opening file"));
    }
    return (0);
}

int open_files_fd(char **cmd_split, t_pars_tokens *pa_tokens, int tkn_idx)
{
    int i;
    int fd_out;
    int fd_in;

    i = 0;
    fd_out = 0;
    fd_in = 0;
    while (cmd_split[i])
    {
        if(open_fds(cmd_split, i , &fd_out,&fd_in))
            return (EXIT_FAILURE);
        i++;
    }
    if(pa_tokens[tkn_idx].is_out)
    {
        env.open_fd_out = fd_out;
        env.fd_out = fd_out;
    }
    if(pa_tokens[tkn_idx].is_in)
    {
        env.open_fd_in = fd_in;
        env.fd_in = fd_in;     
    }
}

void init_and_dup_fd(int *i)
{
    *i = 0;
    env.tmp_in = dup(0);
    env.tmp_out = dup(1);
    env.fd_in = 0;
    env.fd_out = env.tmp_out;
    env.fd_pipe_in_open = 0;
    env.fd_pipe_out_open = 0;
}

void init_redir_helper_fds()
{
    env.open_fd_in = 0;
    env.open_fd_out = 0;
    env.open_heredoc_fdin = 0;
}

void restore_fds()
{
    if(env.open_heredoc_fdin != 0)
        close (env.open_heredoc_fdin);
    dup2(env.tmp_in,0);
    dup2(env.tmp_out, 1);
    close(env.tmp_in);
    close(env.tmp_out);  
}

void close_fds(t_pars_tokens *pa_tkns, int i, int f)
{
    if(f == 0)
    {
        if(pa_tkns[i].pipe == 3)
            close(env.fd_pipe_in_open);
        if(pa_tkns[i].pipe == 1)
            close(env.fd_pipe_in_open);       
        return ;
    }
    if(pa_tkns[i].is_in)
        close (env.open_fd_in);
    if(pa_tkns[i].is_out)
        close (env.open_fd_out);
    // if(pa_tkns[i].pipe == 3)
    //     close(env.fd_pipe_in_open);             
    if(pa_tkns[i].pipe == 1)
        close(env.fd_pipe_in_open);
        close(env.fd_pipe_out_open);
    if(pa_tkns[i].pipe == 2)
        close(env.fd_pipe_out_open);    
}

int handle_in_and_here_doc(t_pars_tokens *pa_tkns, int i)
{
    if (open_files_fd(pa_tkns[i].cmd_splitted, pa_tkns, i) == EXIT_FAILURE)
    {
        return (1);  
    }   
    if (!check_for_input_files(pa_tkns, i))
    {
        find_input_fd(pa_tkns, i);
        env.fd_in = dup(env.fd_in);     
    }
    return (0);
}

int executor(t_pars_tokens *pa_tkns)
{
    int i;
    pid_t *pid;
    char *path;
    pid = malloc(sizeof(pid_t) * env.count);
    init_and_dup_fd(&i);
    while (i < env.count)
    {
       
        path = NULL;
        if (pa_tkns[i].is_in || pa_tkns[i].here_doc)
        {
            if (handle_in_and_here_doc(pa_tkns, i))
            {
                i++;
                continue;
            }
        }
        else
            env.fd_in = dup(env.fd_in);
        dup2(env.fd_in, 0);
        close(env.fd_in);
        close_fds(pa_tkns, i, 0);
        execute_cmd(pa_tkns, i, &path);
        close_fds(pa_tkns, i, 1);

        // ft_putstr_fd(path, 2);
        // ft_putstr_fd("\n", 2);

        pid[i] = fork();
        //ft_putnbr_fd(pid[i], 2);
        // ft_putchar_fd('\n', 2);
        if (pid[i] < 0)
            exit(0);
        if (pid[i] == 0)
        {
            //ft_putnbr_fd(pid[i], 2);
            // ft_putchar_fd('\n', 2);
            if(!is_inbuilt(pa_tkns[i].cmd[0]))
            {
            //     ft_putstr_fd("\n", 2);
            //    ft_putnbr_fd(i, 2);
            //      ft_putstr_fd("\n", 2);
                exec_child(pa_tkns, path, i);
                
            }
            else
            {
                close(env.tmp_in);
                close(env.tmp_out);
                close(env.fd_pipe_in_open);
                exit(0);
            }
        }
        free_me(&path);
        i++;
    }   
   // ft_putnbr_fd(env.fd_pipe_in_open, 1);
	//display prompt again
    
    i = 0;  
    while (i < env.count)
    {
        // ft_putnbr_fd(pid[i], 2);
        // ft_putchar_fd('\n', 2);
        waitpid(pid[i], &env.stat_code, 0);
        i++;
    }
    i = 0;

    free(pid);
    // while (i < env.count)
    // {
    //     free ((void ) pid[i]);
    // }
    restore_fds();
 
    // i = 0;
    // while (i < env.count)
    // {
    //     wait(0);
    //     i++;
    // }

    return (0);
}