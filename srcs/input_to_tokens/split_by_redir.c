
#include "../../includes/mini_shell.h"

extern t_env_var env;


void split_by_redirection(char **arr, char **tokens, t_split *split_info)
{
    if (!token_contains_quote(arr[split_info->i]))
    {
        while (arr[split_info->i][split_info->j])
        {
            split_info->len = 0;
            create_out_redirection_character(arr, split_info, tokens);   
            create_in_redirection_character(arr, split_info, tokens);
            create_pipe_redirection_character(arr, split_info, tokens);
            while(arr[split_info->i][split_info->j] && arr[split_info->i][split_info->j] != '>' && arr[split_info->i][split_info->j] != '<' && arr[split_info->i][split_info->j] != '|') 
            {
                split_info->len++;
                split_info->j++;
            }
            if(split_info->len > 0)
                tokens[split_info->k++] = ft_substr(arr[split_info->i], split_info->j - split_info->len, split_info->len);
        }
    }
    else
    {
        split_info->len = ft_strlen (arr[split_info->i]);
        tokens[split_info->k] = ft_strdup(arr[split_info->i]);
        split_info->k++;
    }
}


/*
    ! why this function ?  
    This function is used to further split the input if it contains pipes or redirections.
    !expected input : char *str    
    echo "hello world" >file|wc -l
    ! expected output : char **str
    str = ["echo", ""hello world"",">","file","|","wc", "-l"]  
*/

char **split_by_pipe_redir(char **arr, t_split *split_info)
{
    init_split_info(split_info);    
    split_info->arr = (char **)ft_calloc(sizeof (char *), (get_len(arr) + 1));

    if (!split_info->arr)
        return (NULL);
    while (arr[split_info->i])
    {
        split_info->j = 0;
        split_info->len = 0;
        split_by_redirection(arr, split_info->arr, split_info);
        split_info->i++;
    }
    split_info->arr[split_info->k] = NULL;
    return (split_info->arr);
}


void create_string_between_quotes(char *str, t_split *split_info)
{
    if(str[split_info->i] && str[split_info->i] == '\"')
        create_string_in_between_dbl_quotes(str ,split_info);
    else if(str[split_info->i] && (str[split_info->i] == '\''))
        create_string_in_between_sngl_quotes(str ,split_info);
    else
    {
        inrement_i_len(split_info);
        if(str[split_info->i] == 0)
        {
            split_info->arr[split_info->array_index++] = ft_substr(str, split_info->i - split_info->len, split_info->len);
            split_info->len = 0; 
            split_info->i++;
            split_info->brk_flg = 0; 
        }
    }
}


/*
    ! why this function ?  
    we cant use our normal split function to create tokens because , if we have a space
    in a string inside quotes, it will be splitted. for this reason we had to modify 
    split function.
    !expected input : char *str    
    echo "hello world">file|wc -l
    ! expected output : char **str
    str = ["echo", ""hello world"",">file|wc -l"]  
*/

char **split_by_quotes(char *str, t_split *split_info)
{
    init_split_info(split_info);
    split_info->arr = (char **)ft_calloc(sizeof (char *), (get_arr_len(str) + 1));
    if (!split_info->arr)
        return (NULL);
    while (str[split_info->i] != '\0' && split_info->brk_flg)
    {
	    if (str[split_info->i] == ' ')
		{
			split_info->arr[split_info->array_index++] = ft_substr(str, split_info->i - split_info->len, split_info->len);
			split_info->len = 0; 
			split_info->i++;
		}
		else if (str[split_info->i] && str[split_info->i] != ' ')
		{
            create_string_between_quotes(str, split_info);
            if(split_info->brk_flg == 0)
                break;
		}
    }
    split_info->arr[split_info->array_index] = NULL;
    return (split_info->arr);
}

char **split_to_tokens(char *input)
{
    t_split si;
    t_split si2;
    split_by_quotes(input, &si);
    if(!si.arr)
        return(NULL);  
    split_by_pipe_redir(si.arr, &si2);
    if(!si2.arr)
        return(NULL);
    ft_free_str_array(&si.arr);
    return (si2.arr);
}
