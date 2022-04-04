#include "../../includes/mini_shell.h"

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
