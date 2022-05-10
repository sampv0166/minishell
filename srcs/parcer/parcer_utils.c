#include "../../includes/mini_shell.h"

extern t_env_var env;



int get_pipe_len(char **tokens)
{
    int i;
    int len;

    i = 0;
    len = 0;
    //  exit(0);
    //  ft_putstr_fd(tokens[i], 2); 
   
    while (tokens[i])
    {
       
        if(tokens[i][0] == '|')
            len++;      
        i++;
         
    }
   
    return (len);
}

int get_count(char **tkns , int j)
{
    int i;

    i = j;

    while(tkns[i])
    {
        if(tkns[i][0] == '|')
        {
            return (++i);
        }
        i++;    
    }
    return (i);
}

void init_parser_info(t_parser_info *pa_info, char **tokens)
{
    pa_info->pipes_count = 0;
    pa_info->i = 0;
    pa_info->k = 0;
    pa_info->len = 0;
    pa_info->arr = NULL;
    pa_info->arr1= NULL;
    pa_info->str = NULL;
    pa_info->j = 0;

    pa_info->pipes_count = get_pipe_len(tokens) + 1;
    env.count = pa_info->pipes_count;
}

void allocate_cmd_memmory(t_parser_info *pa_info, char **tokens)
{  
    pa_info->len = get_count(tokens, pa_info->i);
    pa_info->arr = ft_calloc(sizeof(char *), ((pa_info->len) + 1));
    //pa_info->arr = malloc (sizeof (char *) *  ((pa_info->len) + 1)); // check_what
    pa_info->arr1 = ft_calloc(sizeof(char *), ((pa_info->len) + 1)); // check_what  
    pa_info->str = ((char *)0);
    pa_info->len = 0;
}

void set_pa_tokens(t_pars_tokens *pa_tkns, t_parser_info *pa_info)
{
    pa_info->arr[pa_info->len] = NULL;
    pa_info->arr1[pa_info->len] = NULL;
    pa_tkns[pa_info->j].cmd_splitted = pa_info->arr;
	pa_tkns[pa_info->j].cmd_cpy = pa_info->arr;
    pa_tkns[pa_info->j].cmd =  pa_info->arr1;
    pa_tkns[pa_info->j].cmd_full = pa_info->str;
}

int	is_rdr(char *str)
{
	if (!strcmp(str, ">"))
		return (1);
	else if (!strcmp(str, "<"))
		return (1);
	else if (!strcmp(str, "<<"))
		return (1);
	else if (!strcmp(str, ">>"))
		return (1);
	return (0);
}