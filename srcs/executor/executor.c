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
    
    if (access(cmd, X_OK) == 0)
    {
        return (ft_strdup(cmd));
    }
    init(&path_split);
    i = 0;
    while (path_split[i])
    {
        abs_cmd_path = get_abs_cmd_path(&abs_cmd_path,path_split[i], cmd);
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

int exec_child(t_pars_tokens *pa_tokens, char *abs_path, int i)
{
    // int g;
    // g = 0;
    // while(pa_tokens[i].cmd[g])
    // {
    //     ft_putstr_fd(pa_tokens[i].cmd[g],2);
    //     g++;
    // }
    // ft_putstr_fd("\n\n",2);
    //  ft_putstr_fd(pa_tokens[i].cmd[g + 1],2);
    //print_2d_array(pa_tokens[i].cmd);
    // handle_pipe_type_one(pa_tokens, i);
    // handle_pipe_type_2_3(pa_tokens, i);
    env.stat_code = execve(abs_path, pa_tokens[i].cmd, env.env_var);
	return (env.stat_code);
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

int handle_output_redirections(char **cmd_split, t_pars_tokens *pa_tokens, int tkn_idx)
{
    int i;
    int fd;

    i = 0;
    fd = 0;
    while (cmd_split[i])
    {
        if (cmd_split && cmd_split[i] && (cmd_split[i][0] == '>' && ft_strlen(cmd_split[i]) == 1 && cmd_split[i + 1]))
        {
            fd = open(ft_strdup(cmd_split[i + 1]), O_RDWR | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
                return (ft_perror(EXIT_FAILURE, "error opening file"));
        }
        if (cmd_split[i] && (cmd_split[i][0] == '>' && cmd_split[i][1] == '>' && ft_strlen(cmd_split[i]) == 2 && cmd_split[i + 1]))
        {
            fd = open(ft_strdup(cmd_split[i + 1]), O_RDWR | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
                return (ft_perror(EXIT_FAILURE, "error opening file")); 
        }
        i++;
    }
    pa_tokens[tkn_idx].fd_out = fd;
    if(pa_tokens[tkn_idx].pipe)
        close(env.fd_out);    
    env.fd_out = fd;
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
        if (handle_output_redirections(pa_tokens[i].cmd_splitted, pa_tokens,i) == EXIT_FAILURE)
            return (EXIT_FAILURE);
    }
    else
    {
        if(pa_tokens[i].pipe == 1)
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

void close_fds(t_pars_tokens *pa_tokens, int i)
{
    if (pa_tokens[i].pipe == 1)
    {
        close(pa_tokens[i].fd_in);
        close(pa_tokens[i - 1].fd_in);
        close(pa_tokens[i].fd_out);

    }
    else if (pa_tokens[i].pipe == 3)
    {
        close(pa_tokens[i].fd_out);
        close(pa_tokens[i - 1].fd_in);
    }
    else if (pa_tokens[i].pipe == 2)
        close(pa_tokens[i].fd_out);
}

int execute_cmd(t_pars_tokens *pa_tokens, int i)
{
    char *abs_cmd_path;
    pid_t pid;
    if (is_redir(pa_tokens, i))
    {
        if(handle_redirections(pa_tokens, i))
        {    
            return (EXIT_FAILURE);
        }
    }
    dup2(env.fd_out, 1);
    close(env.fd_out);
    //     int g;
    // g = 0;
    // while(pa_tokens[i].cmd[g])
    // {
    //     ft_putstr_fd(pa_tokens[i].cmd[g],2);
    //     g++;
    // }
    if (is_inbuilt(pa_tokens[i].cmd[0]))
    {
	    return (handle_inbuilt_redir(pa_tokens, i));
    }
     
    abs_cmd_path = get_abs_cmd(pa_tokens[i].cmd[0]);
    if(abs_cmd_path == NULL)
    {
        if(is_inbuilt(pa_tokens[i].cmd_splitted[0]))
            return (0); 
        else if(pa_tokens[i].is_in)
        {
            pa_tokens[i].cmd = pa_tokens[i].cmd_rdr;
           // exit(0);
            abs_cmd_path = get_abs_cmd(pa_tokens[i].cmd[0]);
        }
        else
        {
            printf (":::command not found\n");
            return(127);
        }
    }
    if (access(abs_cmd_path, X_OK) == 0)
        replace_quote(pa_tokens, i);
    else
    {
        printf ("::command not found\n");
        return(127);
    }
    
    pid = fork();
    if (pid < 0)
        exit(0);
    if (pid == 0)
        exec_child(pa_tokens, abs_cmd_path, i);    
    waitpid(pid, 0, 0);
    free_me(&abs_cmd_path);
    //close_fds(pa_tokens, i);
	return (EXIT_SUCCESS);
}

int check_for_input_files(t_pars_tokens *pa_tkns, int i)
{
    int j;
    j = 0;
   // print_2d_array(pa_tkns[i].cmd_splitted);
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
            return(1);
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
    while(pa_tkns[i].cmd_splitted[j] && j >=0 )
    {
        if(pa_tkns[i].cmd_splitted[j] &&pa_tkns[i].cmd_splitted[j][0] == '<')
        {
            if(ft_strlen(pa_tkns[i].cmd_splitted[j]) == 1)
            {
                fd = open(pa_tkns[i].cmd_splitted[j + 1], O_RDONLY);
                if (fd == -1)
                    ft_perror(EXIT_FAILURE, "error opening file");
                env.fd_in = fd;
                open_files(pa_tkns[i].cmd_splitted , j);
                break;
            }
            else
            {
              env.fd_in = pa_tkns[i].here_doc_fd;
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
            // ft_putnbr_fd(j, 2);
            // ft_putstr_fd(pa_tkns[i].cmd_splitted[j] , 2);
            // printf("\n");
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
            //printf("\n%s\n",pa_tkns[i].cmd_splitted[j]);  
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

void find_input_file_names(t_pars_tokens *pa_tkns, int i)
{
    int j;
    int arr_len;
    j = 0;

    int len;
    len = get_files_arr_len(pa_tkns, i);
    char **files;
    arr_len = 0;
    files = malloc(sizeof (char *) * (len + 1));
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
             
            files[arr_len++] = pa_tkns[i].cmd_splitted[j];
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
            files[arr_len++] = pa_tkns[i].cmd_splitted[j];
            j++;
        }
        else
            break;
    }
    files[arr_len] = NULL;
    pa_tkns[i].cmd = files;
}

int executor(t_pars_tokens *pa_tkns)
{
    int i;
    i = 0;
    
    env.tmp_in = dup(0);
    env.tmp_out = dup(1);
    // env.fd_in = 0;
    // env.fd_out = 1;
    // printf("%s", )
    // if(pa_tkns[env.count].cmd_full[ft_strlen(pa_tkns[env.count].cmd_full)] == '|')
    //     env.count = env.count - 1;
    while (i < env.count)
    {
        // if((env.count - 1 ) == i)
        // {
        //     if(pa_tkns[i].cmd_full[ft_strlen(pa_tkns[i].cmd_full) - 1] == '|')
        //     {
               
        //     }
        // }
        //   ft_putstr_fd(pa_tkns[i].cmd_full, 2);
        if (pa_tkns[i].is_in || pa_tkns[i].here_doc)
        {
            if (!check_for_input_files(pa_tkns, i))
            {
                find_input_fd(pa_tkns, i);
                find_input_file_names(pa_tkns, i);
                env.fd_in = dup(env.fd_in);
            }
            else
            {
               find_input_file_names(pa_tkns, i);
            }
        }
        else
        {
            env.fd_in = dup(env.fd_in);
        }
        dup2(env.fd_in, 0);
        close(env.fd_in);
        execute_cmd(pa_tkns, i);
        i++;
    }
    dup2(env.tmp_in,0);
    dup2(env.tmp_out, 1);
    close(env.tmp_in);
    close(env.tmp_out);  
    return (0);
}