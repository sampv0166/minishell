#include "../../includes/mini_shell.h"

extern t_env_var env;

int access_cmnd(char *abs_cmd_path, t_pars_tokens *pa_tokens, int i)
{
    int f;
    f = 0;

    if(abs_cmd_path)
    {
        if (access(abs_cmd_path, X_OK) == 0)
        {
            while (pa_tokens[i].cmd[f])
            {
                delimit_qtes(pa_tokens[i].cmd[f]);
                f++;
            }
        }
    }
    return (0);
}

int handle_inbuilt(char *abs_cmd_path, t_pars_tokens *pa_tokens, int i)
{
    if(abs_cmd_path == NULL)
    {
        if(pa_tokens[i].cmd[0])
        {
            if(is_inbuilt(pa_tokens[i].cmd[0]))
                return (1);
        }
        else
        {
            env.stat_code = 0;
			return(1);  
        }
    }
    return (0);
}


int  handle_output_redirections(char **cmd_split, t_pars_tokens *pa_tokens, int tkn_idx)
{
    int i;
    int fd;

    i = 0;
    fd = 0;
    if(!(pa_tokens[tkn_idx].is_in && pa_tokens[tkn_idx].here_doc))
        set_fds(cmd_split, &i , &fd);
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
            return (handle_inbuilt_redir(pa_tokens, i));
    }
    if(pa_tokens[i].cmd && (env.env_var[get_env("PATH")] != NULL))
    {
        abs_cmd_path = get_abs_cmd(pa_tokens[i].cmd[0]);
        *path = abs_cmd_path;
    }
    if (access_cmnd(abs_cmd_path , pa_tokens, i))
        return (127);
    else
        return (0);
}