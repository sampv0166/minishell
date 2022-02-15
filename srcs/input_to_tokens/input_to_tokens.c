#include "../includes/mini_shell.h"


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
    printf ("\nlen == %d\n", arr_len);
    arr = malloc (sizeof (char *) * arr_len + 1);
    
    while (str[i])
    {
	    if (str[i] == ' ')
			i++;
		else if (str[i] != ' ')
		{
            if(str[i] == '\"')
            {
                i++;
                len++;
                if(ft_strchr_2(str + i, '\"'))
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
            else if(str[i] == '\'')
            {
                i++;
                len++;
                if(ft_strchr_2(str + i, '\''))
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
        if(str[i] == '\'' || str[i] == "\"")
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
        if(ft_strnstr(str, "|", 1))
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

    while (tokens[i])
    {
        if (!token_contains_quote(tokens[i]))
        {
            if(tokens[i + 1] == NULL)
            {
                if(is_token_redir(tokens[i]))
                    return (false);
                if(is_token_pipe(tokens[i]))
                    return (false);    
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

int input_to_tokens(char *input)
{
    char **tokens;
    int ret;

    if(!is_input_valid(input))
        return (syntax_error());
    tokens =  split_to_tokens(input);
    int  i;
    i = 0;
    while(tokens[i])
    {
          printf ("\ntoken = %s\n", tokens[i++]);
    }
    if(!is_token_syntax_valid(tokens))
        exit(0);
   // parse(token);
}
