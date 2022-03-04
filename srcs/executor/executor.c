#include "../../includes/mini_shell.h"

static bool is_redir(t_pars_tokens *pa_tok, int i)
{
    if (pa_tok[i].is_in == 1 || pa_tok[i].is_out == 1 || pa_tok[i].here_doc == 1 || pa_tok[i].pipe == 1)
        return (true);
    return (false);
}

int handle_pipes(t_pars_tokens *pa_tokens, int i, char **cmd_splitted)
{
    static int last_pipe_read_end;
    int fd[2];


    // ls -la | wc -l >> hi | wc -l

    // "ls" "-la" "|" 
    
    // "|" "wc -l"  ">>" "hi" "|" 

    // "|" "wc" "l" 

    // ls -la | wc -| > hi > file

    if (i > 0)
    {
        printf("Ff");
        //if (cmd_splitted[0][0] == '|' && cmd_splitted[ft_strlen(cmd_splitted[i])][0] == '|')
        if (pa_tokens[i].pipe && pa_tokens[i + 1].pipe && pa_tokens[i - 1].pipe)
        {
            printf("\n1 = 1\n");
            pipe(fd);
            pa_tokens[i].fd_in = fd[0];
            if (pa_tokens[i].fd_out == 1)
                pa_tokens[i].fd_out = fd[1];
        }
        //else if (cmd_splitted[0][0] == '|' && cmd_splitted[ft_strlen(cmd_splitted[i])][0] != '|')
        if (pa_tokens[i - 1].pipe && pa_tokens[i].pipe && !pa_tokens[i + 1].pipe)
        {
            printf("\n2 = 2\n");
            pipe(fd);
            pa_tokens[i].fd_in = fd[0];
             if (pa_tokens[i].fd_out == 1)
                pa_tokens[i].fd_out = fd[1];
            last_pipe_read_end = 0;
        }
    }
    else if (pa_tokens[i].pipe)
    {
       // printf("Ff");
        pipe(fd);
        if (pa_tokens[i].fd_out == 1)
                pa_tokens[i].fd_out = fd[1];
        pa_tokens[i].fd_in = fd[0];
        last_pipe_read_end = fd[0];
    }
}

static int init(char **path_splitted[], t_env_var *env)
{
    char *path;

    path = get_env_value(env, "PATH");
    if (path == NULL)
        return (EXIT_FAILURE);
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

static char *get_abs_cmd(char *cmd, t_env_var *env)
{
    char *abs_cmd_path;
    char **path_split;
    int i;

    // if (access(cmd, F_OK) == 0)
    //     return (ft_strdup(cmd));
    init(&path_split, env);
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
}

int exec_child(t_pars_tokens *pa_tokens, char *abs_path, int i, t_env_var *env)
{
    char buffer[1000];

    char *ptr[] = {"ls", "-la", NULL};
    printf("\n c = %d\n", i);
    if (i > 0)
    {
           printf("\n c = %d\n", i);
        if (pa_tokens[i - 1].pipe && pa_tokens[i].pipe & pa_tokens[i + 1].pipe)
        {
            if (dup2(pa_tokens[i - 1].fd_in, STDIN_FILENO) == -1)
                exit(1);
            if (dup2(pa_tokens[i].fd_out, STDOUT_FILENO) == -1)
                exit(1);
            close(pa_tokens[i].fd_out);
            close(pa_tokens[i - 1].fd_in);
            close(pa_tokens[i].fd_in);
        }
        else if(pa_tokens[i].pipe && !pa_tokens[i + 1].pipe)
        {
            if (dup2(pa_tokens[i - 1].fd_in, STDIN_FILENO) == -1)
                exit(1);
            // if (dup2(pa_tokens[i].fd_out, STDOUT_FILENO) == -1)
            //     exit(1);            
            close(pa_tokens[i - 1].fd_in);     
        }

        // int j;
        // j = read(pa_tokens[i - 1].fd_in,buffer, 1000);
        // printf ("\nbuf = %s\n", buffer);
        // close(pa_tokens[i - 1].fd_in);
        // int j;
        // j = read(pa_tokens[i - 1].fd_in,buffer, 1000);
        // printf ("\nbuf = %s\n", abs_path);
        //printf("\n old_in = %d\n", pa_tokens[i - 1].fd_in);
        //printf("\n in = %d\n", pa_tokens[i].fd_out);
        // if (dup2(pa_tokens[i].fd_in,pa_tokens[i - 1].fd_in) == -1)
        //     exit (1);
        // close (pa_tokens[i].fd_out);
        // close (pa_tokens[i - 1].fd_out);
        // close (pa_tokens[i - 1].fd_in);

    }
    else if (pa_tokens[i].pipe)
    {

        close(pa_tokens[i].fd_in);
        if (dup2(pa_tokens[i].fd_out, STDOUT_FILENO) == -1)
            exit(1);
    }
    if (execve(abs_path, pa_tokens[i].cmd, env->env_var) < 0)
    {
        exit(1);
    }
}

int execute_cmd(t_pars_tokens *pa_tokens, int i, t_env_var *env)
{
    char *abs_cmd_path;
    static int k;
    pid_t pid;
    int status;
    char buffer[1000];
    int s;
    abs_cmd_path = get_abs_cmd(pa_tokens[i].cmd[0], env);
    status = 0;
    pid = fork();
    if (pid < 0)
    {
        exit(0);
    }

    if (pid == 0)
    {
        exec_child(pa_tokens, abs_cmd_path, i, env);
    }
    else
    {
    waitpid(pid, 0, 0);
    if (i > 0)
    {
        if (pa_tokens[i - 1].pipe && pa_tokens[i].pipe & pa_tokens[i + 1].pipe)
        {
            // if (dup2(pa_tokens[i - 1].fd_in, STDIN_FILENO) == -1)
            //     exit(1);
            // if (dup2(pa_tokens[i].fd_out, STDOUT_FILENO) == -1)
            //     exit(1);
            // close(pa_tokens[i].fd_out);
            // close(pa_tokens[i - 1].fd_in);
            // close(pa_tokens[i].fd_in);
            close(pa_tokens[i - 1].fd_in);
            close(pa_tokens[i].fd_out);
        }
        else if(pa_tokens[i].pipe && !pa_tokens[i + 1].pipe)
        {
            
             close(pa_tokens[i - 1].fd_in);
             close(pa_tokens[i].fd_out);
            // if (dup2(pa_tokens[i - 1].fd_in, STDIN_FILENO) == -1)
            //     exit(1);
            // if (dup2(pa_tokens[i].fd_out, STDOUT_FILENO) == -1)
            //     exit(1);            
            // close(pa_tokens[i - 1].fd_in);     
        }
    }
    else if (pa_tokens[i].pipe)
    {

        close(pa_tokens[i].fd_out);
        // if (dup2(pa_tokens[i].fd_out, STDOUT_FILENO) == -1)
        //     int j;
        // printf("\niiii = %d\n", pa_tokens[i].fd_in);
        // j = read(pa_tokens[i].fd_in, buffer, 1000);
        // printf("\nbuf = %s\n", buffer);
        //     exit(1);
    }

        // close(pa_tokens[i].fd_out);
        // close(pa_tokens[i - 1].fd_in);
    
        // //exit (0);
    }
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
        *(i++);
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
    //"ls" "-la" | wc -l > h > k 
    
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

int handle_redirections(t_pars_tokens *pa_tokens, int i, t_env_var *env)
{
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
    handle_pipes(pa_tokens,i, pa_tokens[i].cmd_splitted);
    execute_cmd(pa_tokens, i, env);
}

void executor(char **tokens, t_env_var *env, t_pars_tokens *pa_tkns)
{
    //
    // TODO : replace with env variabels
    // TODO : populate structure from splitted tokens
    // t_pars_tokens pa_tkns[5];
    int i;
    int err_code;
    //      ! DELETE THIS PART LATER AFTER PARSING IS FULLY DONE
    // char *ptr[] = {"ls", "-la", NULL};
    // char *ptrr[] = {"ls", "-la", "|", NULL};
    // pa_tkns[0].cmd_full = "ls -la |";
    // pa_tkns[0].cmd = ptr;
    // pa_tkns[0].cmd_splitted = ptrr;
    // pa_tkns[0].pipe = 1;
    // pa_tkns[0].is_in = 0;
    // pa_tkns[0].is_out = 0;
    // pa_tkns[0].here_doc = 0;
    // pa_tkns[0].fd_in = STDIN_FILENO;
    // pa_tkns[0].fd_out = STDOUT_FILENO;

    // char *ptr1[] = {"wc", "-l", NULL};
    // pa_tkns[1].cmd_full = "wc -l";
    // char *ptr11[] = {"|", "wc", "-l",">", "dff",">", "sdf", NULL};
    // pa_tkns[1].cmd_splitted = ptr11;
    // pa_tkns[1].cmd = ptr1;
    // pa_tkns[1].pipe = 1;
    // pa_tkns[1].is_in = 0;
    // pa_tkns[1].is_out = 1;
    // pa_tkns[1].here_doc = 0;
    // pa_tkns[1].fd_in = STDIN_FILENO;
    // pa_tkns[1].fd_out = STDOUT_FILENO;

//  char *ptr133[] = {"clear", NULL};
//     pa_tkns[2].cmd_full = "wc -l";
//     char *ptr121[] = {"clear", NULL};
//     pa_tkns[2].cmd_splitted = ptr121;
//     pa_tkns[2].cmd = ptr133;
//     pa_tkns[2].pipe = 0;
//     pa_tkns[2].is_in = 0;
//     pa_tkns[2].is_out = 0;
//     pa_tkns[2].here_doc = 0;
//     pa_tkns[2].fd_in = STDIN_FILENO;
//     pa_tkns[2].fd_out = STDOUT_FILENO;

    // char *ptr4[] = {"wc", "-l", NULL};
    // pa_tkns[3].cmd_full = "wc -l";
    // pa_tkns[3].cmd = ptr4;
    // pa_tkns[3].pipe = 1;
    // pa_tkns[3].is_in = 0;
    // pa_tkns[3].is_out = 0;
    // pa_tkns[3].here_doc = 0;
    // pa_tkns[3].fd_in = STDIN_FILENO;
    // pa_tkns[3].fd_out = STDOUT_FILENO;
   //exit(0);
    // char *ptr22[] = {NULL};
    // pa_tkns[2].cmd_full = NULL;
    // pa_tkns[2].cmd = NULL;
    // pa_tkns[2].cmd_splitted = ptr22;
    // pa_tkns[2].pipe = 0;
    // pa_tkns[2].is_in = 0;
    // pa_tkns[2].is_out = 0;
    // pa_tkns[2].here_doc = 0;
    // pa_tkns[2].fd_in = STDIN_FILENO;
    // pa_tkns[2].fd_out = STDOUT_FILENO;

    // ! DELETE THE ABOVE PART IF PARSING FINISHEDD
 
    i = 0;
    while (pa_tkns[i].cmd != NULL)
    {
        if (is_redir(pa_tkns, i))
        {
            err_code = handle_redirections(pa_tkns, i, env);
        }
        else if (pa_tkns[i].cmd_full != NULL)
        {
            printf("here");
            ;
        }
        i++;
    }
    printf("okk");
    // TODO : FREE PARSED TOKENS STRUCTURE
    // free_parsed_tokens(pa_toks);
}


//  ls -ls | wc -l | wc -l 

//  3 structs

//  struct[1].cmd_splitted = [{"ls", "-la", "|", NULL}];
//  struct[2].cmd_splitted = [{"|", "wc", "-l", "|", NULL}];
//  struct[3].cmd_splitted = [{"|", "wc", "-l", NULL}];