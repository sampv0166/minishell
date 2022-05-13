#include "../../includes/mini_shell.h"

extern t_env_var env;

void close_redir_fd(int *fd)
{
    if(*fd != 0)
        close(*fd);  
}

void find_cmd(t_pars_tokens *pa_tkns, int i,int *j)
{
    int k;

    k = *j;
    while(pa_tkns[i].cmd_splitted[k])
    {
        if(pa_tkns[i].cmd_splitted[k] && pa_tkns[i].cmd_splitted[k][0] == '<' || pa_tkns[i].cmd_splitted[k][0] == '>')
        {
            k++;
            if(pa_tkns[i].cmd_splitted[k])
                k++;
        }
        if(pa_tkns[i].cmd_splitted[k] &&  (pa_tkns[i].cmd_splitted[k][0] == '<' || pa_tkns[i].cmd_splitted[k][0] == '>'))
            continue;
        else
        {
            if (pa_tkns[i].cmd_splitted[k])
            {
                k++;
            }
            break ;
        }       
    }
    *j = k;
}

void increment_j(t_pars_tokens *pa_tkns, int i, int *j)
{
    int k;

    k = *j;

    if(pa_tkns[i].cmd_splitted[k] && pa_tkns[i].cmd_splitted[k][0] == '<' || pa_tkns[i].cmd_splitted[k][0] == '>')
    {
        k++;
        if(pa_tkns[i].cmd_splitted[k])
            k++;
    }
    *j = k;
}