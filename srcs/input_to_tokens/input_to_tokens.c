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
            printf("\n%c\n",arr[split_info->i][split_info->j]);
            if(arr[split_info->i][split_info->j] == '>')        
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
    char **tokens;
    init_split_info(split_info);    
    tokens = (char **)ft_calloc(sizeof (char *), (get_len(arr) + 1));
    if (!tokens)
        return (NULL);
    while (arr[split_info->i])
    {
        split_info->j = 0;
        split_info->len = 0;
        split_by_redirection(arr, tokens, split_info);
        split_info->i++;
    }
    tokens[split_info->k] = NULL;
    free_2d_array(arr);
    return (tokens);
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

char **split_to_tokens(char *str, t_split *split_info)
{
    init_split_info(split_info);
    char *temp ;
    split_info->arr = (char **)ft_calloc(sizeof (char *), (get_arr_len(str) + 1));
    if (!split_info->arr)
        return (NULL);    
    while (str[split_info->i] != '\0' && split_info->brk_flg)
    {
	    if (str[split_info->i] == ' ')
			split_info->i++;
		else if (str[split_info->i] && str[split_info->i] != ' ')
		{
            if(str[split_info->i] && str[split_info->i] == '\"')
                create_string_in_between_dbl_quotes(str ,split_info);
            else if(str[split_info->i] && str[split_info->i] == '\'')
                create_string_in_between_sngl_quotes(str ,split_info);
            else
            {
                while (str[split_info->i] && str[split_info->i] != ' ')
                    inrement_i_len(split_info);
                temp =  split_info->arr[split_info->array_index];
			    split_info->arr[split_info->array_index++] = ft_substr(str, split_info->i - split_info->len, split_info->len);
                split_info->len = 0; 
                if(str[split_info->i] == 0)
                    break ;  
            }
		}
    }
    split_info->arr[split_info->array_index] = NULL;
    return (split_info->arr);
}

int input_to_tokens(char *input)
{
    char **tokens;
    t_split *si;
    t_split *si2;
    si = malloc (sizeof (t_split));
    si2 = malloc (sizeof (t_split));
    if(!si || ! si2)
        return (EXIT_FAILURE);
    tokens = split_to_tokens(input, si);
    if(!tokens) 
        return(EXIT_FAILURE);
    tokens = split_by_pipe_redir(tokens, si2);
    if(!tokens) 
        return(EXIT_FAILURE);
    if (!is_token_syntax_valid(tokens))
    {
        printf("Invalid Syntax\n");
        return(258);
    }
    t_pars_tokens *pa_tkns;
    pa_tkns = parser(tokens);
     
    free_split_info(si, si2, tokens);
    // int y;
    // y = 0;
    //    while (y < env.count)
    // {
    //     int j;
    //     j = 0;
    //     printf("\n struct = %d\n", y);
    //     printf("\n-------------cmd---------------------------\n");
    //     while (pa_tkns[y].cmd[j])
    //     {
    //         printf ("%s ",pa_tkns[y].cmd[j]);
    //         j++;
    //     }
    //     printf("\n-------------cmd_splitted---------------------------\n");
    //     j = 0;
    //     while (pa_tkns[y].cmd_splitted[j])
    //     {
    //         printf ("%s ",pa_tkns[y].cmd_splitted[j]);
    //         j++;
    //     }
    //     printf("\n-------------cmd_full---------------------------\n");
    //     printf ("%s ",pa_tkns[y].cmd_full);
    //     printf("\npipe = %d\n", pa_tkns[y].pipe);
    //     printf("\npipe_read_end = %d\n", pa_tkns[y].pipe_read_end);
    //     printf("\npipe_write_end = %d\n", pa_tkns[y].pipe_write_end);
    //     printf("\nis_out = %d\n", pa_tkns[y].is_out);
    //     printf("\nis_append = %d\n", pa_tkns[y].is_out_appnd);
    //     printf("\nis_in = %d\n", pa_tkns[y].is_in);
    //     printf("\nhere_doc = %d\n", pa_tkns[y].here_doc);
    //     printf("\nfd_out = %d\n", pa_tkns[y].fd_out);
    //     y++;
    // }
    executor (pa_tkns);
	return (EXIT_SUCCESS);
}



 


    void print_2d_array(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        printf("%s\n", arr[i]);
        i++;
    }
}
