#include "../../includes/mini_shell.h"

int syntax_error()
{
    return(EXIT_SUCCESS);
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
    if(ft_strlen(str) > 1)
    {
        if(*str == '|')
            return (false);
    }
    return (true);
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
    int i;
    i = 0;

    while (tokens[i] != NULL)
    { 
        if (!token_contains_quote(tokens[i]) && !(is_inbuilt(tokens[0])))
        {
            if(tokens[i] && tokens[i + 1] == NULL)
            {
                if(is_token_redir(tokens[i]))
                    return (false);
                if(!is_token_pipe(tokens[i]))
                    return (false);    
            }
            if(!is_special_charater_correct(tokens[i]))
                return (false);
        }
        i++;
    }
    return (true);
} 
