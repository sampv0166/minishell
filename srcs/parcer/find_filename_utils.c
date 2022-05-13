#include "../../includes/mini_shell.h"

extern t_env_var env;

void get_cmd_len(t_pars_tokens *pa_tkns,  int i, int *j, int *len)
{
    int  k;

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
        else if(pa_tkns[i].cmd_splitted[k])
        {
            *len++;
            k++;
        }
        else
            break;
    }
   *j = k; 
}

void get_file_len (t_pars_tokens *pa_tkns,  int i, int *j, int *len)
{
    while(pa_tkns[i].cmd_splitted[*j])
    {
        if(pa_tkns[i].cmd_splitted[*j] && pa_tkns[i].cmd_splitted[*j][0] == '<' || pa_tkns[i].cmd_splitted[*j][0] == '>')
        {
            *j++;
            if(pa_tkns[i].cmd_splitted[*j])
                *j++;
        }
        if(pa_tkns[i].cmd_splitted[*j] &&  pa_tkns[i].cmd_splitted[*j][0] == '<' || pa_tkns[i].cmd_splitted[*j][0] == '>')
            continue;
        else if(pa_tkns[i].cmd_splitted[*j])
        {
            *j++;
            *len++;
        }
        else
            break;
    }
}