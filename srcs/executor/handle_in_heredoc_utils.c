#include "../../includes/mini_shell.h"

extern t_env_var env;

void close_redir_fd(int *fd)
{
    if(*fd != 0)
        close(*fd);  
}

void find_cmd(t_pars_tokens *pa_tkns, int i,int *j)
{
    while(pa_tkns[i].cmd_splitted[*j])
    {
        if(pa_tkns[i].cmd_splitted[*j] && pa_tkns[i].cmd_splitted[*j][0] == '<' || pa_tkns[i].cmd_splitted[*j][0] == '>')
        {
            *j++;
            if(pa_tkns[i].cmd_splitted[*j])
                *j++;
        }
        if(pa_tkns[i].cmd_splitted[*j] &&  (pa_tkns[i].cmd_splitted[*j][0] == '<' || pa_tkns[i].cmd_splitted[*j][0] == '>'))
            continue;
    }
}

void increment_j(t_pars_tokens *pa_tkns, int i, int *j)
{
    if(pa_tkns[i].cmd_splitted[*j] && pa_tkns[i].cmd_splitted[*j][0] == '<' || pa_tkns[i].cmd_splitted[*j][0] == '>')
    {
        *j++;
        if(pa_tkns[i].cmd_splitted[*j])
            *j++;
    }
}