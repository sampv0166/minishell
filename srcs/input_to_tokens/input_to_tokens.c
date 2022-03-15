#include "../../includes/mini_shell.h"


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
		else if (str[i] != ' ')
		{
            if(str[i] == '\"')
            {

                i++;
                if(ft_strchr_2(str + i, '\"'))
                {
                   while(str[i] && str[i] != '\"')
                        i++;
                    len++;
                    if(str[i] == '\"')
                        i++;
                }
                else
                {
                    len++;
                    break ;
                }
            }
            else if(str[i] == '\'')
            {
             i++;
                if(ft_strchr_2(str + i, '\''))
                {
                   while(str[i] && str[i] != '\'')
                        i++;
                    len++;
                    if(str[i] == '\'')
                        i++;
                }
                else
                {
                    len++;
                    break ;
                }
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

char **split_to_tokens(char *str)
{
    char **arr;
    int arr_len;
	size_t	i;
	size_t	array_index;
    int len;

	i = 0 ;
	array_index = 0;
    len = 0;
    arr_len = get_arr_len(str);
    arr = malloc (sizeof (char *) * arr_len + 1);
    
    while (str[i] != '\0')
    {
      
	    if (str[i] == ' ')
			i++;

		else if (str[i] && str[i] != ' ')
		{
            if(str[i] && str[i] == '\"')
            {
                i++;
                len++;
                if(str[i] && ft_strchr_2(str + i, '\"'))
                {
                   while(str[i] && str[i] != '\"')
                   {
                        i++;
                        len++;
                   }
                    if(str[i] == '\"')
                    {
                     i++;
                     len++;
                    }
                    arr[array_index++] = ft_substr(str, i - len, len);
			        len = 0;   
                }
                else
                {
                    while(str[i] && str[i] != '\"')
                        len++;
                    arr[array_index++] = ft_substr(str, i - len, len);
			        len = 0;         
                    break ;
                }
            }
            else if(str[i] && str[i] == '\'')
            {  
                
                i++;
                len++;
                          
                if(str[i] && ft_strchr_2(str + i, '\''))
                {

                   while(str[i] && str[i] != '\'')
                   {
                        i++;
                        len++;
                   }
                    if(str[i] == '\'')
                    {
                     i++;
                     len++;
                    }
                    arr[array_index++] = ft_substr(str, i - len, len);
			        len = 0;   
                }
                else
                {
                    while(str[i] && str[i] != '\'')
                        len++;
                    arr[array_index++] = ft_substr(str, i - len, len);
			        len = 0;         
                    break ;
                }   
            }
            else
            {
                while (str[i] && str[i] != ' ')
                {
                    i++;
			        len++;
                }
			    arr[array_index++] = ft_substr(str, i - len, len);
			    len = 0; 
                if(str[i] == 0)
                    break ;  
            }
		}
    }
    arr[array_index] = NULL;
   return (arr);
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
            if(tokens[i] && tokens[i + 1] != NULL)
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

int syntax_error()
{
    return(EXIT_SUCCESS);
}

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
            if (arr[i][j] == '>' && arr[i][j + 1] == '>')
            {
                if (arr[i][j - 1] != ' ' && arr[i][j - 1] != '\0' ) 
                    size++;
                if (arr[i][j + 1] != ' ' && arr[i][j + 1] != '\0' ) 
                    size++;    
            }
            else if (arr[i][j] == '>' && arr[i][j + 1] != '>')
            {
                if (arr[i][j - 1] != ' ' && arr[i][j - 1] != '\0' ) 
                    size++;
                if (arr[i][j + 1] != ' ' && arr[i][j + 1] != '\0' ) 
                    size++;    
            } 
            if (arr[i][j] == '<' && arr[i][j + 1] == '<')
            {
                if (arr[i][j - 1] != ' ' && arr[i][j - 1] != '\0' ) 
                    size++;
                if (arr[i][j + 1] != ' ' && arr[i][j + 1] != '\0' ) 
                    size++;          
            }
            else if (arr[i][j] == '<' && arr[i][j + 1] != '<')
             {
                if (arr[i][j - 1] != ' ' && arr[i][j - 1] != '\0' ) 
                    size++;
                if (arr[i][j + 1] != ' ' && arr[i][j + 1] != '\0' ) 
                    size++;        
             }
            if(arr[i][j] == '|')
            {
                if (arr[i][j - 1] != ' ' && arr[i][j - 1] != '\0' ) 
                    size++;
                if (arr[i][j + 1] != ' ' && arr[i][j + 1] != '\0' ) 
                    size++;       
            }      
            j++;
        }
        size++;
        i++;
    }
    return (size);
}

char **split_by_pipe_redir(char **arr)
{
    char **tokens;
    int i;
    int j;
    i = 0;
    j = 0;
    int k;
    int len;

    k = 0;
    len = 0;
    tokens = (char **) malloc (sizeof (char *) * get_len(arr) + 1);
    tokens[get_len(arr)] = NULL;

    // getlen = 4

    // arr [][][][][\0]
    //     0  1 2 3  4
    
    // echo
    // "print somenthing">file

    while (arr[i])
    {
        j = 0;
        len = 0;
        if (!token_contains_quote(arr[i]))
        {
            while (arr[i][j])
            {
              
                len = 0;
                if (arr[i][j] == '>' && arr[i][j + 1] == '>')
                {
                    tokens[k++] = ft_strdup(">>");
                    j = j + 2;   
                }
                if (arr[i][j] == '>' && arr[i][j + 1] != '>')
                {
                    tokens[k++] = ft_strdup(">");
                    j++;   
                }
                if (arr[i][j] == '<' && arr[i][j + 1] == '<')
                {
                    tokens[k++] = ft_strdup("<<");
                    j = j + 2;   
                }
                if (arr[i][j] == '<' && arr[i][j + 1] != '<')
                {
                    tokens[k++] = ft_strdup(">");
                    j++;   
                } 
                if (arr[i][j] == '|')
                {
                    tokens[k++] = ft_strdup("|");
                    j++;   
                }
                while(arr[i][j] && arr[i][j] != '>' && arr[i][j] != '<' && arr[i][j] != '|') 
                {
                    len++;
                    j++;
                }
                if(len > 0)
                {
                    tokens[k++] = ft_substr(arr[i], j - len, len); 
                }                                  
            }
        }
        else
        {
            len = ft_strlen (arr[i]);
            tokens[k++] = ft_strdup(arr[i]);
        }
        i++;
    }
    tokens[k] = NULL;;
    return (tokens);
}

// echo
// "print something">

// echo
// "print somenthing"
// >
// file

int input_to_tokens(char *input, t_env_var *env)
{
    char **tokens;
    int ret;
    // if(!is_input_valid(input))
    //     return (syntax_error());  

    tokens =  split_to_tokens(input);
    int  i;
    i = 0;

    tokens = split_by_pipe_redir(tokens);
    // if(!is_token_syntax_valid(tokens))
    //     exit(0);
    t_pars_tokens *pa_tkns;
    pa_tkns = parser(tokens);
   // exit (1);
    int y;
    y = 0;
    while (pa_tkns[y].cmd)
    {
        int j;
        j = 0;
        printf("\n struct = %d\n", y);
        printf("\n-------------cmd---------------------------\n");
        while (pa_tkns[y].cmd[j])
        {
            printf ("%s ",pa_tkns[y].cmd[j]);
            j++;
        }
       printf("\n-------------cmd_splitted---------------------------\n");
        j = 0;
        while (pa_tkns[y].cmd_splitted[j])
        {
            printf ("%s ",pa_tkns[y].cmd_splitted[j]);
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
        y++;
    }
    executor (tokens, env, pa_tkns);
	return (0);
}