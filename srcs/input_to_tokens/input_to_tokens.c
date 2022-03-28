#include "../../includes/mini_shell.h"

extern t_env_var env;

char	*ft_strchr_2(const char *str, int c)
{
	size_t	i;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		i++;
	}
	if (c == '\0')
		return ((char *)str + i);
	return (0);
}


/*
    ! why this function ?  
    skip characters untill we encounter the next double quote and increment len
    !expected input : char *str , int i, int len   
    
    !return values
    returns 0 if there is no closing qutoe
    returns 1 if there is a closing quote
*/
int    skip_and_increment_len_dbl_qts(char *str, int *i, int *len)
{
    (*i)++;
//     printf("%d", *i);
//    exit(0);
//    *i++;
    if(str[*i] && ft_strchr_2(str + *i, '\"'))
    {
        while(str[*i] && str[*i] != '\"')
          (*i)++;
    (*len)++;
    if(str[*i] == '\"')
        (*i)++;
    }
    else
    {
        (*len)++;
        return (0);
    }
    return (1);
}

/*
    ! why this function ?  
    skip characters untill we encounter the next single quote and increment len
    
    !expected input : char *str , int i, int len   
    
    !return values
    returns 0 if there is no closing qutoe
    returns 1 if there is a closing quote
*/

int    skip_and_increment_len_sngl_qts(char *str, int *i, int *len)
{
    (*i)++;
//     printf("%d", *i);
//    exit(0);
//    *i++;
    if(str[*i] && ft_strchr_2(str + *i, '\''))
    {
        while(str[*i] && str[*i] != '\'')
          (*i)++;
    (*len)++;
    if(str[*i] == '\'')
        (*i)++;
    }
    else
    {
        (*len)++;
        return (0);
    }
    return (1);
}

/*
    ! why this function ?  
    To count the number of arrays needed to store the splitted input.
    *expected input : char *str    
    echo "hello world">file|wc -l
    1       2           3       4   
    * expected output : int len
    4
    ? how it works
    * loop through the string
    * skip if the character is a space
    * if its not space , check if its double quotes or single quotes and call dbl_qts function
    * if its neither single or double qts, skip the spaces and increment length
*/

int get_arr_len(char *str)
{
    int len;
    int i;
    
    i = 0;
    len = 0;
    while(str[i])
    {
        if (str[i] == ' ')
			i++;
		else if (str[i] != ' ' && str[i])
		{
            if(str[i] == '\"')
            {   
                if (!skip_and_increment_len_dbl_qts (str, &i, &len))
                    break ;   
            }
            else if(str[i] == '\'')
            {
                if(!skip_and_increment_len_sngl_qts (str, &i, &len))
                    break;
            }
            else
            {
                while (str[i] && str[i] != ' ')
				    i++;
			    len++;
            }
		}
    }
    return (len);
}
void inrement_i_len(t_split *split_info)
{
    split_info->i++;
    split_info->len++;
}
/*
    ! why this function ?  
    check if there is closing quote in the string and create new string of characters in between
    quotes
    !expected input : char *str - string from substring to be created
    !                 int i - current index of the str
    !                 char **arr - array where the new string will be stored
    !                 int arr_index - index of arr   
    echo "hello world">file|wc -l
    ! expected output : char **str
    str = [""hello world""] 

    !return values
    returns 0 if there is no closing qutoe
    returns 1 if there is a closing quote
*/
int create_string_in_between_dbl_quotes(char *str,t_split *split_info)
{
    inrement_i_len(split_info);
    if(str[split_info->i] && ft_strchr_2(str + split_info->i, '\"'))
    {
        while(str[split_info->i] && str[split_info->i] != '\"')
            inrement_i_len(split_info);
        if(str[split_info->i] == '\"')
            inrement_i_len(split_info);
        split_info->arr[split_info->array_index++] = ft_substr(str, split_info->i - split_info->len, split_info->len);
        split_info->len = 0;
    }
    else
    {
        while(str[split_info->i] && str[split_info->i] != '\"')
            split_info->len++;
        split_info->arr[split_info->array_index++] = ft_substr(str, split_info->i - split_info->len, split_info->len);
        split_info->len= 0;
        split_info->brk_flg = 0;
        return (0);      
    }
    return (1);
}

/*
    ! why this function ?  
    check if there is closing quote in the string and create new string of characters in between
    quotes
    !expected input : char *str - string from substring to be created
    !                 int i - current index of the str
    !                 char **arr - array where the new string will be stored
    !                 int arr_index - index of arr   
    echo "hello world">file|wc -l
    ! expected output : char **str
    str = [""hello world""] 

    !return values
    returns 0 if there is no closing qutoe
    returns 1 if there is a closing quote
*/
int create_string_in_between_sngl_quotes(char *str, t_split *split_info)
{
    inrement_i_len(split_info);
    if(str[split_info->i] && ft_strchr_2(str + split_info->i, '\''))
    {
        while(str[split_info->i] && str[split_info->i] != '\'')
            inrement_i_len(split_info);
        if(str[split_info->i] == '\'')
            inrement_i_len(split_info);
        split_info->arr[split_info->array_index++] = ft_substr(str, split_info->i - split_info->len, split_info->len);
        split_info->len = 0;
    }
    else
    {
        while(str[split_info->i] && str[split_info->i] != '\'')
            split_info->len++;
        split_info->arr[split_info->array_index++] = ft_substr(str, split_info->i - split_info->len, split_info->len);
        split_info->len= 0;
        split_info->brk_flg = 0;
        return (0);      
    }
    return (1);
}

void init_split_info(t_split *split_info)
{
    split_info->i = 0;
    split_info->array_index = 0;
    split_info->len = 0;
    split_info->brk_flg = 1;
    split_info->k = 0;
    split_info->j = 0;
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
char **split_to_tokens(char *str, char **tokens)
{
    t_split split_info;
    init_split_info(&split_info);

    split_info.arr = malloc (sizeof (char *) * get_arr_len(str) + 1);
    if (!split_info.arr)
        return (NULL);
    while (str[split_info.i] != '\0' && split_info.brk_flg)
    {
	    if (str[split_info.i] == ' ')
			split_info.i++;
		else if (str[split_info.i] && str[split_info.i] != ' ')
		{
            if(str[split_info.i] && str[split_info.i] == '\"')
                create_string_in_between_dbl_quotes(str ,&split_info);
            else if(str[split_info.i] && str[split_info.i] == '\'')
                create_string_in_between_sngl_quotes(str ,&split_info);
            else
            {
                while (str[split_info.i] && str[split_info.i] != ' ')
                    inrement_i_len(&split_info);
			    split_info.arr[split_info.array_index++] = ft_substr(str, split_info.i - split_info.len, split_info.len);
			    split_info.len = 0; 
                if(str[split_info.i] == 0)
                    break ;  
            }
		}
    }
    split_info.arr[split_info.array_index] = '\0';
    return (split_info.arr);
}

bool is_input_valid (char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        if (input[i] == '\'')
			while (input[++i] && input[i] != '\'')
				;
		if (input[i] == '\"')
			while (input[++i] && input[i] != '\"')
				;
        if(input[i] == '\\' || input[i] == ';')
            return (false);
        i++;    
    }
    return (true);
}  

bool token_contains_quote(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == '\'' || str[i] == '\"')
            return (true);
        i++;
    }
    return (false);
}

bool is_token_redir(char *str)
{
    if(ft_strlen (str) == 2)
    {
        if(ft_strnstr(str, "<<", 2) || ft_strnstr(str, ">>", 2))
            return (true);
    }
    if(ft_strlen (str) == 1)
    {
        if(ft_strnstr(str, "<", 1) || ft_strnstr(str, ">", 1))
            return (true);
    }
    return (false);
}

bool is_token_pipe(char *str)
{
    
    if(ft_strlen (str) == 1)
    {
        if(ft_strchr(str, '|'))
            return (true);     
    }
    return (false);
}

bool is_special_charater_correct(char *str)
{
    if(ft_strlen (str) != 2)
    {
        if(ft_strnstr(str, "<<", 2) || ft_strnstr(str, ">>", 2))
            return (false);
    }
    if(ft_strlen (str) != 1)
    {
	    if ((ft_strchr(str, '<') && !ft_strnstr(str, "<<", 2)) \
		|| (ft_strchr(str, '>') && !ft_strnstr(str, ">>", 2)) \
		|| (ft_strchr(str, '|') && !ft_strnstr(str, "||", 2)))
			return (false);   
    }
    return (true);
}

bool is_token_syntax_valid (char **tokens)
{
    /*
        TODO : check if token contains a single or double quote
        TODO : CHECK IF THE NEXT TOKEN IS NULL AND CURRENT LOOP COUNT TOKEN IS A REDIRECTION 
        TODO : CHECK THERE ARE NOT MORE THAN 2 SPECAL CHARACTERS WITHOUT QUOTES
        TODO : CHECK IF THE NEXT TOKEN IS NULL AND CURRENT LOOP COUNT TOKEN IS A PIPE
    */
   
    int i;

    i = 0;

    while (tokens[i] != NULL)
    { 
        if (!token_contains_quote(tokens[i]))
        {
            if(tokens[i] && tokens[i + 1] == NULL)
            {
                if(is_token_redir(tokens[i]))
                {
                    return (false);
                }
                if(is_token_pipe(tokens[i]))
                {
                    return (false);    
                }
            }
            if(!is_special_charater_correct(tokens[i]))
            {
                return (false);
            }
        }
        i++;
    }
    return (true);
} 
void get_len_out_redirection(char **arr, int *i, int *j, int *size)
{
    if (arr[*i][*j] == '>' && arr[*i][(*j) + 1] == '>')
    {
        if (arr[*i][(*j) - 1] != ' ' && arr[*i][(*j) - 1] != '\0' ) 
            (*size)++;
        if (arr[*i][(*j) + 1] != ' ' && arr[*i][(*j) + 1] != '\0' ) 
            (*size)++;  
    }
    else if (arr[*i][*j] == '>' && arr[*i][(*j) + 1] != '>')
    {
        if (arr[*i][(*j) - 1] != ' ' && arr[*i][(*j) - 1] != '\0' ) 
            (*size)++;
        if (arr[*i][(*j) + 1] != ' ' && arr[*i][(*j) + 1] != '\0' ) 
            (*size)++;    
    } 
}

void get_len_in_redirection(char **arr, int *i, int *j, int *size)
{
    if (arr[*i][*j] == '<' && arr[*i][(*j) + 1] == '<')
    {
        if (arr[*i][(*j) - 1] != ' ' && arr[*i][(*j) - 1] != '\0' ) 
            (*size)++;
        if (arr[*i][(*j) + 1] != ' ' && arr[*i][(*j) + 1] != '\0' ) 
            (*size)++;  
    }
    else if (arr[*i][*j] == '<' && arr[*i][(*j) + 1] != '<')
    {
        if (arr[*i][(*j) - 1] != ' ' && arr[*i][(*j) - 1] != '\0' ) 
            (*size)++;
        if (arr[*i][(*j) + 1] != ' ' && arr[*i][(*j) + 1] != '\0' ) 
            (*size)++;    
    } 
}

void get_len_pipe(char **arr, int *i, int *j, int *size)
{
    if(arr[*i][*j] == '|')
    {
        if (arr[*i][(*j) - 1] != ' ' && arr[*i][(*j) - 1] != '\0' ) 
            (*size)++;
        if (arr[*i][(*j) + 1] != ' ' && arr[*i][(*j) + 1] != '\0' ) 
            (*size)++;       
    }   
}
int syntax_error()
{
    return(EXIT_SUCCESS);
}

void create_out_redirection_character(char **arr, t_split *split_info, char **tokens)
{
    if (arr[split_info->i][split_info->j] == '>' && arr[split_info->i][split_info->j + 1] == '>')
    {
        tokens[split_info->k++] = ft_strdup(">>");
        split_info->j = split_info->j + 2;   
    }
    if (arr[split_info->i][split_info->j] == '>' && arr[split_info->i][split_info->j + 1] != '>')
    {
        tokens[split_info->k++] = ft_strdup(">");
        split_info->j++;   
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

/*
    ! why this function ?  
    count how many arrays needed to store tokens if redirections and pipe are not seperated by space
    !expected input : char **arr   
    echo "hello world" > file  |  wc -l
    1       2          3  4    5  6   7
    ! expected output : int len
    7
*/
int get_len(char **arr)
{
    int size;
    int i;
    int j;
    size = 0;
    i = 0;
    j = 0;
    while (arr[i])
    {
        j = 0;
        while (arr[i][j])
        {
            get_len_out_redirection(arr, &i, &j,&size);
            get_len_in_redirection(arr, &i, &j, &size);   
            get_len_pipe(arr, &i, &j,&size);   
            j++;
        }
        size++;
        i++;
    }
    return (size);
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
char **split_by_pipe_redir(char **arr)
{
    t_split split_info;
    init_split_info(&split_info);
         
    char **tokens;
    tokens = (char **) malloc (sizeof (char *) * (get_len(arr) + 1));
    if (!tokens)
        return (NULL);
    
    tokens[get_len(arr)] = NULL;
    while (arr[split_info.i])
    {
        split_info.j = 0;
        split_info.len = 0;
        split_by_redirection(arr, tokens, &split_info);
        split_info.i++;
    }
    
    tokens[split_info.k] = NULL;
    free_2d_array(arr);
    return (tokens);
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
int input_to_tokens(char *input)
{
    char **tokens;
    int ret;
    tokens = NULL;
    ret = 0;
    tokens = split_to_tokens(input, tokens);
    if(!tokens)
        return(1);
    tokens = split_by_pipe_redir(tokens);
    if (!is_token_syntax_valid(tokens))
    {
        printf("invalid syntax");
        return(2);
    }
    t_pars_tokens *pa_tkns;
    
    pa_tkns = parser(tokens);
    int y;
    y = 0;

//    printf ("%d", env.count);
//     while (y < env.count)
//     {
//         int j;
//         j = 0;
//         printf("\n struct = %d\n", y);
//         printf("\n-------------cmd---------------------------\n");
//         while (pa_tkns[y].cmd[j])
//         {
//             printf ("%s ",pa_tkns[y].cmd[j]);
//             j++;
//         }
//        printf("\n-------------cmd_splitted---------------------------\n");
//         j = 0;
//         while (pa_tkns[y].cmd_splitted[j])
//         {
//             printf ("%s ",pa_tkns[y].cmd_splitted[j]);
//             j++;
//         }
//         printf("\n-------------cmd_full---------------------------\n");
//         printf ("%s ",pa_tkns[y].cmd_full);
//         printf("\npipe = %d\n", pa_tkns[y].pipe);
//         printf("\npipe_read_end = %d\n", pa_tkns[y].pipe_read_end);
//         printf("\npipe_write_end = %d\n", pa_tkns[y].pipe_write_end);
//         printf("\nis_out = %d\n", pa_tkns[y].is_out);
//         printf("\nis_append = %d\n", pa_tkns[y].is_out_appnd);
//         printf("\nis_in = %d\n", pa_tkns[y].is_in);
//         printf("\nhere_doc = %d\n", pa_tkns[y].here_doc);
//         y++;
//     }

    executor (tokens,pa_tkns);
      
	return (0);
}