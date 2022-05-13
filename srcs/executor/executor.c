#include "../../includes/mini_shell.h"

extern t_env_var env;

int call_execve(t_pars_tokens *pa_tokens, char *abs_path, int i)
{
    if (!ft_strcmp(pa_tokens[i].cmd[0], "./minishell"))
        increment_s_vals();
    env.stat_code = execve(abs_path, pa_tokens[i].cmd, env.env_var);
    return (env.stat_code);
}


void exec_child(t_pars_tokens *pa_tkns, pid_t *pid, char *path, int *i)
{
    if(!is_inbuilt(pa_tkns[*i].cmd[0]))
    {
        if (pa_tkns[*i]. pipe != 0)
            close(env.fd_pipe_in_open);
        call_execve(pa_tkns, path, *i);
    }
    else
    {
        close(env.fd_pipe_in_open);
        if (*i == env.count - 1)
        {
            free_everything(pa_tkns);
            free(pid);
        }
        exit (0);       
    } 
}

int handle_in_redirections(t_pars_tokens *pa_tkns, int *i)
{
    if (pa_tkns[*i].is_in || pa_tkns[*i].here_doc)
    {
        if (handle_in_and_here_doc(pa_tkns, *i))
        {
            *i++;
            return (1);
        }
    }
    else
        env.fd_in = dup(env.fd_in);
    return (0);    
}

void execute_commands(t_pars_tokens *pa_tkns, char *path, pid_t *pid)
{
    int i;
    
    i = 0;
    while (i < env.count)
    { 
        path = NULL;
        if(handle_in_redirections(pa_tkns , &i))
            continue;
        dup2(env.fd_in, 0);
        close(env.fd_in);
        close_fds(pa_tkns, i, 0);
        if(execute_cmd(pa_tkns, i, &path))
        {
            i++;
            continue;
        }
        close_fds(pa_tkns, i, 1);
        pid[i] = fork();
        if (pid[i] < 0)
            exit(0);
        if (pid[i] == 0)
            exec_child(pa_tkns, pid, path, &i);
        free_me(&path);
        i++;
    }    
}

int executor(t_pars_tokens *pa_tkns)
{
    pid_t *pid;
    char *path;

    pid = malloc(sizeof(pid_t) * env.count);
    init_and_dup_fd();
    execute_commands(pa_tkns, path, pid);
    wait_for_child_and_restore_fds_(pid);
    return (0);
}