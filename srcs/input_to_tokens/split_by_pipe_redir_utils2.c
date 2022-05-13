#include "../../includes/mini_shell.h"

int syntax_error()
{
    return(EXIT_SUCCESS);
}


void create_out_redirection_character(char **arr, t_split *split_info, char **tokens)
{
    int len;
    len = 0;

    if (arr[split_info->i][split_info->j] == '>' && arr[split_info->i][split_info->j + 1] == '>')
    {
        while(arr[split_info->i][split_info->j] == '>')
        {
            split_info->j++;
            len++;
        }
        tokens[split_info->k++] = ft_substr(arr[split_info->i], (split_info->j) - len, len); 
    }
    else if(arr[split_info->i][split_info->j] == '>' && arr[split_info->i][split_info->j + 1] != '>')
    {
        tokens[split_info->k++] = ft_strdup(">");
        split_info->j++;   
    }
}

void create_in_redirection_character(char **arr, t_split *split_info, char **tokens)
{
    int len;
    len = 0;

    if (arr[split_info->i][split_info->j] == '<' && arr[split_info->i][split_info->j + 1] == '<')
    {
        while(arr[split_info->i][split_info->j] == '<')
        {
            split_info->j++;
            len++;
        }
        tokens[split_info->k++] = ft_substr(arr[split_info->i], (split_info->j) - len, len);
    }
    if (arr[split_info->i][split_info->j] == '<' && arr[split_info->i][split_info->j + 1] != '<')
    {
        tokens[split_info->k++] = ft_strdup("<");
        split_info->j++;   
    }
}

void create_pipe_redirection_character(char **arr, t_split *split_info, char **tokens)
{
    int len;
    len = 0;

    if (arr[split_info->i][split_info->j] == '|')
    {
        while(arr[split_info->i][split_info->j] == '|')
        {
            split_info->j++;
            len++;
        }
        tokens[split_info->k++] = ft_substr(arr[split_info->i], (split_info->j) - len, len);   
    }
}