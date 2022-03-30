#include "../../includes/mini_shell.h"

extern t_env_var env;

static bool is_redir(t_pars_tokens *pa_tok, int i)
{
    if (pa_tok[i].is_in == 1 || pa_tok[i].is_out == 1 || pa_tok[i].here_doc == 1 || pa_tok[i].pipe)
        return (true);
    return (false);
}

int handle_pipes(t_pars_tokens *pa_tokens, int i, char **cmd_splitted)
{
    static int last_pipe_read_end;
    int fd[2];
    pipe(fd);
    pa_tokens[i].fd_in = fd[0];
    pa_tokens[i].fd_out = fd[1];
	return (0);
}

static int init(char **path_splitted[])
{
    char *path;
    
    path = get_env_value("PATH");
    if (path == NULL)
    {
        return (EXIT_FAILURE);   
    }
    *path_splitted = ft_split(path, ':');
    free(path);
    if (*path_splitted == NULL)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

char *ft_append(char **dst, char *src)
{
    char *dst_buf;
    char *appendet;
    int appendet_len;

    if (dst == NULL)
        dst_buf = NULL;
    else
        dst_buf = *dst;
    appendet_len = ft_strlen(dst_buf) + ft_strlen(src);
    if (appendet_len == 0)
    {
        // ft_free((void *)dst);
        return (NULL);
    }
    appendet = malloc((appendet_len + 1) * sizeof(*appendet));
    if (appendet == NULL)
        return (NULL);
    while (dst_buf && *dst_buf)
        *appendet++ = *dst_buf++;
    while (src && *src)
        *appendet++ = *src++;
    *appendet = '\0';
    // ft_free((void *)dst);
    return (appendet - appendet_len);
}

static char *get_abs_cmd_path(char *path_splitted, char *cmd)
{
    char *abs_cmd_path;

    abs_cmd_path = ft_strjoin(path_splitted, "/");
    if (abs_cmd_path == NULL)
        return (NULL);
    abs_cmd_path = ft_append(&abs_cmd_path, cmd);
    if (abs_cmd_path == NULL)
        return (NULL);
    return (abs_cmd_path);
}

static char *get_abs_cmd(char *cmd)
{
    char *abs_cmd_path;
    char **path_split;
    int i;
    init(&path_split);
    i = 0;
    while (path_split[i])
    {
        
        abs_cmd_path = get_abs_cmd_path(path_split[i], cmd);
        if (abs_cmd_path == NULL)
            return (NULL);
        if (access(abs_cmd_path, F_OK) == 0)
        {
            return (abs_cmd_path);
        }
        i++;
    }
	return (NULL);
}

void handle_pipe_type_one(t_pars_tokens *pa_tokens, int i)
{
    if (!pa_tokens[i].pipe && pa_tokens[i].fd_out)
    {    
        // if (dup2(pa_tokens[i - 1].fd_in, STDIN_FILENO) == -1)
        //      exit(1);
        if (pa_tokens[i].fd_out != STDOUT_FILENO && pa_tokens[i].is_out)
        {
            if (dup2(pa_tokens[i].fd_out, STDOUT_FILENO) == -1)
                exit(1);   
        }
    }
    printf("%d", pa_tokens[i].pipe);

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
     printf("pipe_type == %d", pa_tokens[i].pipe);
    handle_pipe_type_one(pa_tokens, i);
    handle_pipe_type_2_3(pa_tokens, i);
    // ft_putnbr_fd(pa_tokens[i].fd_in, 2);
    // ft_putnbr_fd(pa_tokens[i].fd_out, 2);
    // exit(0);
    env.stat_code = execve(abs_path, pa_tokens[i].cmd, env.env_var);
    if (env.stat_code < 0)
        exit(1);  
	return (0);
}

int ft_perror(int exit_status, char *msg)
{
    perror(msg);
    return (exit_status);
}

void *get_file_name(char **cmd_split, int *i)
{   
    int j;

    j = 0;
    while (cmd_split[(*i)][j])
    {
        if (cmd_split[(*i)][j] == '<' && ft_strlen(cmd_split[(*i)]) == 1)
            break ;
        (*i)++;
    }
    if (cmd_split[(*i) + 1][j])
    {
        (*i)++;
        return (ft_strdup(cmd_split[(*i)]));
        (*i)++;
    }
    return (NULL);
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
        if (cmd_split[i][0] == '>' && ft_strlen(cmd_split[i]) == 1 && cmd_split[i + 1])
        {
            fd = open(ft_strdup(cmd_split[i + 1]), O_RDWR | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
                return (ft_perror(EXIT_FAILURE, "error opening file"));
        }
        if (cmd_split[i][0] == '>' && cmd_split[i][1] == '>' && ft_strlen(cmd_split[i]) == 2 && cmd_split[i + 1])
        {
            fd = open(ft_strdup(cmd_split[i + 1]), O_RDWR | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
                return (ft_perror(EXIT_FAILURE, "error opening file"));
            i++;  
        }
        i++;
    }
    pa_tokens[tkn_idx].fd_out = fd;
    return (EXIT_SUCCESS);
}

int handle_redirections(t_pars_tokens *pa_tokens, int i)
{
    if(pa_tokens[i].pipe)
    {
        handle_pipes(pa_tokens,i, pa_tokens[i].cmd_splitted);
    }
    if(pa_tokens[i].is_in)
    {
        if (handle_input_redirections(pa_tokens[i].cmd_splitted, pa_tokens,i) == EXIT_FAILURE)
            return (EXIT_FAILURE);
    }
    if(pa_tokens[i].is_out)
    {
        if (handle_output_redirections(pa_tokens[i].cmd_splitted, pa_tokens,i) == EXIT_FAILURE)
            return (EXIT_FAILURE);
    }
	return (0);
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
    {
        close(pa_tokens[i].fd_out);
    }
}

int execute_cmd(t_pars_tokens *pa_tokens, int i)
{
    char *abs_cmd_path;
    pid_t pid;
     
    if (is_redir(pa_tokens, i))
        handle_redirections(pa_tokens, i);
    if (is_inbuilt(pa_tokens->cmd[0]))
	    return (handle_inbuilt_redir(pa_tokens, i));
    abs_cmd_path = get_abs_cmd(pa_tokens[i].cmd[0]);
	
    if (access(abs_cmd_path, F_OK) == 0)
        replace_quote(pa_tokens, i);
    else
    {
        printf (":command not found");
        return(127);
    }
    pid = fork();
    if (pid < 0)
        exit(0);
    if (pid == 0)
        exec_child(pa_tokens, abs_cmd_path, i);
    waitpid(pid, 0, 0);
    close_fds(pa_tokens, i);
	exit(0);
	return (0);
	
}

int executor(t_pars_tokens *pa_tkns)
{
    int i;
    int err_code;
    i = 0;
    while (pa_tkns[i].cmd)
    {
        execute_cmd(pa_tkns, i);
        i++;
    }
    return (0);
}