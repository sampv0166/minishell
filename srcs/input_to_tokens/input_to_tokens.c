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

char	*getting_tild(void)
{
	char	*pwd;
	char	s[1000];
	char	*ret;

	ret = NULL;
	pwd = ft_strdup(getcwd(s, 1000));
	ch_tild();
	ret = ft_strdup(getcwd(s, 1000));
	ft_putendl_fd(ret, 1);
	ch_home();
	chdir(pwd);
	free(pwd);
	return (ret);
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
    char    *tmp;
    char    *dol;
    int     qte;
    qte = 0;
	int y;
    y = 0;
    int j;
    j = 0;
    int i;
    i = 0;
    int k;
    k = 0;
    int l;
    char    *cat;
	char    *res;
	int		m;
	int		trig;
    l = 0;
	trig = 0;
    tmp = NULL;
    cat = NULL;
	res = NULL;
	char	**full;
    dol = NULL;
	m = 0;
	full = (char **)malloc(sizeof(char *) * (get_len(pa_tkns[y].cmd) + 1));
    while (pa_tkns[y].cmd[j] != NULL)
    {
		qte = 0;
		k = 0;
		i = 0;
		tmp = ft_strdup(pa_tkns[y].cmd[j]);
		res = ft_calloc(ft_strlen(tmp) + 1, sizeof(char));
		while (tmp[k])
		{
			/*Taking quotes in the account for $-values or ~-values*/
			if (ft_isqt(tmp[k]))
			{
				if (trig == 1 && qte == ft_isqt(tmp[k]))
				{
					qte = 0;
					trig = 0;
				}
				else if (!qte)
				{
					trig = 1;
					qte = ft_isqt(tmp[k]);
				}
			}
			if ((tmp[k] == '$' && (ft_isenv(tmp[k + 1]) || tmp[k + 1] == '?')) && qte != 39)
			{
				if (tmp[k + 1] == '?')
				{
					/*$? the exit code*/
					k += 2;
					cat = ft_itoa(env.stat_code);
					res[i] = '\0';
					res = ft_strjoin(res, cat);
					free(cat);
					cat = ft_strdup(res);
					res = ft_calloc(ft_strlen(cat) + ft_strlen(tmp) - k + 1, sizeof(char));
					i = 0;
					while (cat[i])
					{
						res[i] = cat[i];
						i++;
					}
					res[i] = '\0';
				}
				else
				{
					l = 0;
					/*taking the variable after the dollar*/
					cat = ft_strdup(&tmp[k]);
					++l;
					while (ft_isenv(cat[l]))
						l++;
					cat[l] = '\0';
					if (ft_isdigit(tmp[k + 1]))
						k += 2;
					else
						k += ft_strlen(cat);
					l = get_env(&cat[1]);
					/*fetching values*/
					if (env.env_var[l] != NULL)
					{
						dol = get_env_dollar(cat);
						res[i] = '\0';
						res = ft_strjoin(res, dol);
						i = ft_strlen(res);
						free(dol);
						free(cat);
						cat = ft_strdup(res);
						free(res);
						res = ft_calloc(ft_strlen(cat) + ft_strlen(tmp) - k + 1, sizeof(char));
						i = 0;
						while (cat[i])
						{
							res[i] = cat[i];
							i++;
						}
					}
				}
				free(cat);
			}
			/*Iterating for quote after dollar or for digits after dollar or for alphabets*/
			else if (tmp[k] == '$' && ft_isqt(tmp[k + 1]) && !ft_isqt(tmp[k - 1]))
				k++;
			else if ((tmp[k] == '~' && (tmp[k + 1] == '/' || tmp[k + 1] == '\0')) && !qte)
			{
				/*Fetching the values for ~*/
				k++;
				dol = getting_tild();
				res[i] = '\0';
				res = ft_strjoin(res, dol);
				free(dol);
				cat = ft_strdup(res);
				free(res);
				res = ft_calloc(ft_strlen(cat) + ft_strlen(tmp) - k + 2, sizeof(char));
				i = 0;
				while (cat[i])
				{
					res[i] = cat[i];
					i++;
				}
				free(cat);
			}
			else
			{
				res[i] = tmp[k];
				i++;
				k++;
			}
		}
		res[i] = '\0';
		free(tmp);
		if (*res)
		{
			/*If the string is not null it will duplicate the value of res in 2d array named as full*/
			full[m] = ft_strdup(res);
			m++;
		}
		free(res);
		j++;
    }
	full[m] = NULL;
	/*After succesfully taking all the commands with quotes if present, first we free the old command variable
	then we duplicate the strings including quotes in our main command variable	and free the full-variable*/
	m = 0;
	j = 0;
	while (pa_tkns[y].cmd[j] != NULL)
	{
		free(pa_tkns[y].cmd[j]);
		j++;
	}
	j = 0;
	while (full[m] != NULL)
	{
		pa_tkns[y].cmd[j] = ft_strdup(full[m]);
		free(full[m]);
		j++;
		m++;
	}
	pa_tkns[y].cmd[j] = NULL;
	free(full);
	y = 0;
    while (y < env.count)
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
        printf("\nfd_out = %d\n", pa_tkns[y].fd_out);
        y++;
       // exit(0);
    }
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
