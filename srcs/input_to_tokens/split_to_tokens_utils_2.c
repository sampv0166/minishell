
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
	if(str[*i] && ft_strchr_2(str + *i, '\''))
    {
        while(str[*i] && str[*i] != '\'')
          (*i)++;   
		if(str[*i] == '\'')
			(*i)++;
		while (str[*i])
		{
			if (str[*i] == ' ' || str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
				break;
			else if (str[*i] == '\'')
			{
				(*i)++;
				while(str[*i] && str[*i] != '\'')
					(*i)++;
				if(str[*i] == '\'')
					(*i)++;
			}
			else if (str[*i] == '\"')
			{
				(*i)++;
				while(str[*i] && str[*i] != '\"')
					(*i)++;
				if(str[*i] == '\"')
					(*i)++;
			}
			else
				(*i)++;
		}
		(*len)++;
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
    skip characters untill we encounter the next double quote and increment len
    !expected input : char *str , int i, int len   
    
    !return values
    returns 0 if there is no closing qutoe
    returns 1 if there is a closing quote
*/
int    skip_and_increment_len_dbl_qts(char *str, int *i, int *len)
{
    (*i)++;
    if(str[*i] && ft_strchr_2(str + *i, '\"'))
    {
        while(str[*i] && str[*i] != '\"')
          (*i)++;   
		if(str[*i] == '\"')
			(*i)++;
		while (str[*i])
		{
			if (str[*i] == ' ' || str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
				break;
			else if (str[*i] == '\'')
			{
				(*i)++;
				while(str[*i] && str[*i] != '\'')
					(*i)++;
				if(str[*i] == '\'')
					(*i)++;
			}
			else if (str[*i] == '\"')
			{
				(*i)++;
				while(str[*i] && str[*i] != '\"')
					(*i)++;
				if(str[*i] == '\"')
					(*i)++;
			}
			else
				(*i)++;	
		}
		(*len)++;
    }
    else
    {
        (*len)++;
        return (0);
    }
    return (1);
}