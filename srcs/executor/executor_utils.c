#include "../../includes/mini_shell.h"

extern t_env_var env;


void wait_for_child_and_restore_fds_(pid_t *pid)
{
    int i;

    i = 0;

    while (i < env.count)
    {
        wait(0);
        i++;
    }
    free(pid);
    restore_fds();
}

void init_and_dup_fd()
{
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
    if(pa_tkns[i].pipe == 1)
    {
        close(env.fd_pipe_in_open);
        close(env.fd_pipe_out_open);
    }
    if(pa_tkns[i].pipe == 2)
        close(env.fd_pipe_out_open);    
}
