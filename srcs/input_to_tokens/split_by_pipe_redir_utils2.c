#include "../../includes/mini_shell.h"

void create_out_redirection_character(char **arr, t_split *split_info, char **tokens)
{
    // if (arr[split_info->i][split_info->j] == '>' && arr[split_info->i][split_info->j + 1] == '>')
    // {
    //     tokens[split_info->k++] = ft_strdup(">>");
    //     split_info->j = split_info->j + 2;
    //     printf("\n%c\n",arr[split_info->i][split_info->j]);
    //     if(arr[split_info->i][split_info->j] == '>')
    //         return (1);
    //     //exit(0);
    // }
    // if (arr[split_info->i][split_info->j] == '>' && arr[split_info->i][split_info->j + 1] != '>')
    // {
    //     tokens[split_info->k++] = ft_strdup(">");
    //     split_info->j++;
    // }
    while(arr[split_info->i][split_info->j] == '>')
    {
        
    }

}

void create_in_redirection_character(char **arr, t_split *split_info, char **tokens)
{
    if (arr[split_info->i][split_info->j] == '<' && arr[split_info->i][split_info->j + 1] == '<')
    {
        tokens[split_info->k++] = ft_strdup("<<");
        split_info->j = split_info->j + 2;   
    }
    if (arr[split_info->i][split_info->j] == '<' && arr[split_info->i][split_info->j + 1] != '<')
    {
        tokens[split_info->k++] = ft_strdup("<");
        split_info->j++;   
    }
}

void create_pipe_redirection_character(char **arr, t_split *split_info, char **tokens)
{
    if (arr[split_info->i][split_info->j] == '|')
    {
        tokens[split_info->k++] = ft_strdup("|");
        split_info->j++;   
    }
}