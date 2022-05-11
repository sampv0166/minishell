#include "../../includes/mini_shell.h"

extern t_env_var env;

void print_strcut(t_pars_tokens *pa_tkns)
{
    int y;
    y = 0;
    while (y < env.count)
    {
        int j;
        j = 0;
        printf("\n struct = %d\n", y);
        printf("\n-------------cmd---------------------------\n");
        while (pa_tkns[y].cmd[j])
        {
            printf ("%d: %s ",j , pa_tkns[y].cmd[j]);
            j++;
        }
        printf("\n-------------cmd_splitted---------------------------\n");
        j = 0;
        while (pa_tkns[y].cmd_splitted[j])
        {
            printf ("%d: %s ", j, pa_tkns[y].cmd_splitted[j]);
            j++;
        }
		printf("\n-------------cmd_cpy---------------------------\n");
        j = 0;
        while (pa_tkns[y].cmd_cpy[j])
        {
            printf ("%d: %s ", j, pa_tkns[y].cmd_cpy[j]);
            j++;
        }
        printf("\n-------------cmd_full---------------------------\n");
        printf ("%s ",pa_tkns[y].cmd_full);
        printf("\npipe = %d\n", pa_tkns[y].pipe);
        printf("\npipe_read_end = %d\n", pa_tkns[y].pipe_read_end);
        printf("\npipe_write_end = %d\n", pa_tkns[y].pipe_write_end);
        printf("\nis_out = %d\n", pa_tkns[y].is_out);
        printf("\nis_append = %d\n", pa_tkns[y].is_out_appnd);
        printf("\nis_in = %d\n", pa_tkns[y].is_in);
        printf("\nhere_doc = %d\n", pa_tkns[y].here_doc);
        printf("\nfd_out = %d\n", pa_tkns[y].fd_out);
        y++;
    }
}

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

char **join_toks(char **tok1, char **tok2)
{
    int len;
    len = (get_2d_arr_len2(tok1) + get_2d_arr_len2(tok2))  + 1;
    char **new_toks;
    int i;
    int j;
    new_toks = malloc(sizeof(char *) * len + 1);
    i = 0;
    j = 0;
    while(tok1[i])
    {
        new_toks[i] = ft_strdup(tok1[i]);
        i++;
    }
    while(tok2[j])
    {
        new_toks[j + i] = ft_strdup(tok2[j]);
        j++;
    }
    new_toks[j + i] = NULL;
    ft_free_str_array(&tok1);
    ft_free_str_array(&tok2);
    return (new_toks);
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


char *join_pipes()
{
    char *in;
    char *buf;
    char **toks;

    in = NULL;
    buf = NULL;
    while(1)
    {
        buf = readline("");
        if (buf == NULL)
        {
            free_me(&in);
            return (NULL);
        }
        in = ft_strjoin(in, buf);
        if(ft_strlen(in) > 0)
        {
            if(in[ft_strlen(in) - 1] == '|')
            {
                if(in && in[0] == '|')
                    break ;
                continue;
            }
            else
                break;  
        }
    }
    return (in);
}

char **get_command_for_pipe(char **toks, char ***tokens, char *input)
{
    toks = split_to_tokens(input);
    *tokens = join_toks(*tokens, toks);
    free_me(&input);
    if (!is_token_syntax_valid(*tokens))
    { 
        ft_free_str_array(tokens);
        ft_free_str_array(&toks);
        free_me(&input);
        return (NULL);
    }
    return (*tokens);
}

char **tokens_split(char *input)
{
    char **tokens;
    char **toks;
    tokens = split_to_tokens(input);
    if (!tokens || !is_token_syntax_valid(tokens))
    {
        ft_putstr_fd("Invalid Syntax\n", 2);
        env.stat_code = 258;
        ft_free_str_array(&tokens);
        return (NULL);
    }      
    if(tokens[get_2d_arr_len(tokens)][0] == '|')
    {
        input = join_pipes();
        if(input)
            get_command_for_pipe(toks, &tokens, input);
        else
        {
            ft_free_str_array(&tokens);
            free_env();
            // exit(0);
        }
    }
  
    return (tokens);    
}

int input_to_tokens(char *input)
{
    t_pars_tokens *pa_tkns;
    char    **tokens;

    // TOKEN SPLIT
    tokens = tokens_split(input);
    if(!tokens)
        return (EXIT_FAILURE);
    // PARCER
    pa_tkns  = parser(tokens);
    ft_free_str_array(&tokens);
    // EXPANDER
    expander(pa_tkns);
    //EXECUTOR
	executor(pa_tkns);
    free_everything(pa_tkns);
	return (0);
}
void print_2d_array(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        ft_putstr_fd(arr[i], 2);
         ft_putstr_fd("\n", 2);
        i++;
    }
}

