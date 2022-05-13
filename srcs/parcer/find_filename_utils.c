#include "../../includes/mini_shell.h"

extern t_env_var env;

void get_cmd_len(t_pars_tokens *pa_tkns,  int i, int *j, int *len)
{
    int  k;
    int l;

    l = *len;
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
            l++;
            k++;
        }
        else
            break;
    }
   *j = k; 
   *len = l;
}

void get_file_len (t_pars_tokens *pa_tkns,  int i, int *j, int *len)
{
    int  k;
    int l;

    l = *len;
    k = *j;
    while(pa_tkns[i].cmd_splitted[k])
    {
        if(pa_tkns[i].cmd_splitted[k] && pa_tkns[i].cmd_splitted[k][0] == '<' || pa_tkns[i].cmd_splitted[k][0] == '>')
        {
            k++;
            if(pa_tkns[i].cmd_splitted[k])
                k++;
        }
        if(pa_tkns[i].cmd_splitted[k] &&  pa_tkns[i].cmd_splitted[k][0] == '<' || pa_tkns[i].cmd_splitted[k][0] == '>')
            continue;
        else if(pa_tkns[i].cmd_splitted[k])
        {
            k++;
            l++;
        }
        else
            break;
    }
    *j = k; 
   *len = l;
}