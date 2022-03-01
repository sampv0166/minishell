#include "../../includes/mini_shell.h"

static bool	is_redir(t_pars_tokens *pa_tok, int i)
{
	if (pa_tok[i].is_in == 1 || pa_tok[i].is_out == 1 \
	|| pa_tok[i].here_doc == 1 ||pa_tok[i].pipe == 1)
		return (true);
	return (false);
}

int handle_pipes (t_pars_tokens *pa_tokens, int i, int *pipe_out)
{
    static int last_pipe;
    int fd[2];
    if (i > 0)
    {
        if (pa_tokens[i].pipe && pa_tokens[i + 1].pipe && pa_tokens[i - 1].pipe)
        {
            printf("fsf");
            pipe(fd);
            pa_tokens[i].fd_in = fd[0];
            pa_tokens[i].fd_out = fd[1];
        }
    }
    else if (pa_tokens[i].pipe && pa_tokens[i + 1].pipe)
    {
        printf("bbb");
        pipe(fd);
        pa_tokens[i].fd_out= fd[1];
     //   close (fd[1]);
        pa_tokens[i].fd_in = fd[0];  
        printf ("\nisin = %d\n", pa_tokens[i].fd_in);
        printf ("\nisout = %d\n", pa_tokens[i].fd_out);
    }
}

static int	init(char **path_splitted[], t_env_var *env)
{
	char	*path;

	path = get_env_value(env, "PATH");
	if (path == NULL)
		return (EXIT_FAILURE);
	*path_splitted = ft_split(path, ':');
	free(path);
	if (*path_splitted == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*ft_append(char **dst, char *src)
{
	char	*dst_buf;
	char	*appendet;
	int		appendet_len;

	if (dst == NULL)
		dst_buf = NULL;
	else
		dst_buf = *dst;
	appendet_len = ft_strlen(dst_buf) + ft_strlen(src);
	if (appendet_len == 0)
	{
		//ft_free((void *)dst);
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
	//ft_free((void *)dst);
	return (appendet - appendet_len);
}

static char	*get_abs_cmd_path(char *path_splitted, char *cmd)
{
	char	*abs_cmd_path;

	abs_cmd_path = ft_strjoin(path_splitted, "/");
	if (abs_cmd_path == NULL)
		return (NULL);
	abs_cmd_path = ft_append(&abs_cmd_path, cmd);
	if (abs_cmd_path == NULL)
		return (NULL);
	return (abs_cmd_path);
}


static char* get_abs_cmd (char *cmd, t_env_var *env)
{
    char *abs_cmd_path;
    char **path_split;
    int i;

    if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd)); 
    init(&path_split, env);\
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

int exec_child (t_pars_tokens *pa_tokens, char *abs_path, int i, t_env_var *env)
{
    char buffer[1000];

    char *ptr[] = {"ls", "-la", NULL};
    printf ("\n c = %d\n", i);
    if (i == 1)
    {
        // int j;
        // j = read(pa_tokens[i - 1].fd_in,buffer, 1000);
        // printf ("\nbuf = %s\n", buffer);
        // close(pa_tokens[i - 1].fd_in);
        //int j;
        // j = read(pa_tokens[i - 1].fd_in,buffer, 1000);
        //printf ("\nbuf = %s\n", abs_path);
        printf ("\n old_in = %d\n", pa_tokens[i - 1].fd_in);
        printf ("\n in = %d\n", pa_tokens[i].fd_out);
        // if (dup2(pa_tokens[i].fd_in,pa_tokens[i - 1].fd_in) == -1)
        //     exit (1);
        //close (pa_tokens[i].fd_out);
        if (dup2(pa_tokens[i - 1].fd_in, STDIN_FILENO) == -1)
            exit (1);
         if (dup2(pa_tokens[i].fd_out, STDOUT_FILENO) == -1)
            exit (1);    
        close (pa_tokens[i].fd_out);    
        close (pa_tokens[i - 1].fd_in);
        close (pa_tokens[i].fd_in); 
        // close (pa_tokens[i - 1].fd_out);    
        // close (pa_tokens[i - 1].fd_in);       
    }
    else
    {
        close (pa_tokens[i].fd_in);   
        if (dup2(pa_tokens[i].fd_out, STDOUT_FILENO) == -1)
            exit (1);
    //    if (dup2(pa_tokens[i].fd_in, STDIN_FILENO) == -1)
    //         exit (1);       
    }
    if(execve(abs_path,pa_tokens[i].cmd, env->env_var) < 0)
    {
        write(1, "b\n",2);
        exit(1);
    }
    //;
    // int j;
    // j = read (pa_tokens->is_out,buffer, 1000);
    // printf ("\nbuf = %s\n", buffer);
}

int execute_cmd (t_pars_tokens *pa_tokens, int i, t_env_var *env)
{
    char    *abs_cmd_path;
    static  int k;
    pid_t   pid;
    int     status;
    char    buffer[1000];
    int     s;
    abs_cmd_path = get_abs_cmd (pa_tokens[i].cmd[0], env);
    status = 0;
    pid = fork();
    if (pid < 0)
    {
        printf("sd");
        exit (0);
    }
        
    if (pid == 0)
    {
        exec_child (pa_tokens, abs_cmd_path, i, env);
    }
    //waitpid(pid, 0, 0);
    
    // exit (1);
    // dup2(s, STDOUT_FILENO);
    // printf ("\nfd = %d\n", pa_tokens[i].is_in);
    if (i == 1)
    {  
        close(pa_tokens[i].fd_out);
        int j;
        printf ("\niiii = %d\n", pa_tokens[i].fd_in);
        j = read(pa_tokens[i].fd_in,buffer, 3);
        // // fflush()
        //  printf("\nbuf = %s\n", buffer);
        // close(pa_tokens[i - 1].fd_in);
        // if (dup2(pa_tokens[i].fd_in, STDIN_FILENO) == -1)
        //     exit (1);
        // close(pa_tokens[i].fd_in);       
        // j = read(pa_tokens[i].fd_in,buffer, 1000);
        // // fflush()
        printf("\nbuf = %s\n", buffer);    
        exit (0);
    }
    else
    {
        close(pa_tokens[i].fd_out);
        // int j;
        // printf("\nok\n");
        // printf ("\niiii = %d\n", pa_tokens[i].fd_in);
        // j = read(pa_tokens[i].fd_in,buffer, 1000);
        // printf("\nbuf = %s\n", buffer);
        //exit (1);
     }
}

int handle_redirections (t_pars_tokens *pa_tokens, int i, t_env_var *env, int *pipe_out)
{
   
    handle_pipes (pa_tokens, i, pipe_out);
    execute_cmd (pa_tokens, i, env);        
}

void executor(char **tokens, t_env_var *env)
{
    // TODO : replace with env variabels
    // TODO : populate structure from splitted tokens
    t_pars_tokens pa_tkns[5];
    int     i;
    //      ! DELETE THIS PART LATER
    char    *ptr[] = {"ls", "-la", NULL};
    pa_tkns[0].cmd_full = "ls -la";
    pa_tkns[0].cmd = ptr;
    pa_tkns[0].pipe = 1;
    pa_tkns[0].is_in = 0;
    pa_tkns[0].is_out = 0;
    pa_tkns[0].here_doc = 0;
    pa_tkns[0].fd_in = STDIN_FILENO;
    pa_tkns[0].fd_out = STDOUT_FILENO;

    char *ptr1[] = {"wc", "-l", NULL};
    pa_tkns[1].cmd_full = "wc -l > hi";
     pa_tkns[1].cmd = ptr1;
    pa_tkns[1].pipe = 1;
    pa_tkns[1].is_in = 0;
    pa_tkns[1].is_out = 1;
    pa_tkns[1].here_doc = 0;
    pa_tkns[1].fd_in = STDIN_FILENO;
    pa_tkns[1].fd_out = STDOUT_FILENO;

    char *ptr3[] = {"wc", "-l", NULL};
    pa_tkns[2].cmd_full = "wc -l";
    pa_tkns[2].cmd = ptr3;
    pa_tkns[2].pipe = 1;
    pa_tkns[2].is_in = 0;
    pa_tkns[2].is_out = 0;
    pa_tkns[2].here_doc = 0;
    pa_tkns[2].fd_in = STDIN_FILENO;
    pa_tkns[2].fd_out = STDOUT_FILENO;

    char *ptr4[] = {"wc", "-l", NULL};
    pa_tkns[3].cmd_full = "wc -l";
    pa_tkns[3].cmd = ptr4;
    pa_tkns[3].pipe = 1;
    pa_tkns[3].is_in = 0;
    pa_tkns[3].is_out = 0;
    pa_tkns[3].here_doc = 0;
    pa_tkns[3].fd_in = STDIN_FILENO;
    pa_tkns[3].fd_out = STDOUT_FILENO;

    pa_tkns[4].cmd_full = NULL;
    pa_tkns[4].cmd = NULL;
    pa_tkns[4].pipe = 1;
    pa_tkns[4].is_in = 0;
    pa_tkns[4].is_out = 0;
    pa_tkns[4].here_doc = 0;
    pa_tkns[4].fd_in = STDIN_FILENO;
    pa_tkns[4].fd_out = STDOUT_FILENO;

    // ! DELETE THE ABOVE PART IF PARSING FINISHEDD

    i = 0;
    while(pa_tkns[i].cmd_full != NULL)
    {
        if (is_redir(pa_tkns, i))
        {
            handle_redirections (pa_tkns, i, env);
        }
        else if (pa_tkns[i].cmd_full != NULL)
        {
            ;
        }
        i++;
    }
    
    // TODO : FREE PARSED TOKENS STRUCTURE
    // free_parsed_tokens(pa_toks);
}