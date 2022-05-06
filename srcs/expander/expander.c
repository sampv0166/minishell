#include "../../includes/mini_shell.h"

extern t_env_var env;

char	*getting_tild(void)
{
	char	*pwd;
	char	s[1000];
	char	*ret;

	ret = NULL;
	pwd = ft_strdup(getcwd(s, 1000));
	ch_tild();
	ret = ft_strdup(getcwd(s, 1000));
	// ft_putendl_fd(ret, 1);
	ch_home();
	chdir(pwd);
	free(pwd);
	return (ret);
}

void	qte_enc(char c, int *trig, int *qte)
{
	if (ft_isqt(c))
	{
		if (*trig == 1 && *qte == ft_isqt(c))
		{
			*qte = 0;
			*trig = 0;
		}
		else if (!(*qte))
		{
			*trig = 1;
			*qte = ft_isqt(c);
		}
	}
}

void expander(t_pars_tokens *pa_tkns)
{

    //! SHORTEN THIS CODE!
     char    *tmp;
    char    *dol;
    int     qte;
	int y;
    int j;
    int i;
    int k;
    int l;
    char    *cat;
	char    *res;
	int		m;
	char	*res1;
	int		trig;
    y = 0;
    i = 0;
    k = 0;
    j = 0;
    qte = 0;
    l = 0;
	trig = 0;
    tmp = NULL;
    cat = NULL;
	res = NULL;
	res1 = NULL;
	char	**full;
    dol = NULL;
	m = 0;
	pa_tkns[y].cmd_splitted = (char **)malloc(sizeof(char *) * (get_len(pa_tkns[y].cmd) + 1));
	while (pa_tkns[y].cmd[j] != NULL)
	{
		pa_tkns[y].cmd_splitted[j] = ft_strdup(pa_tkns[y].cmd[j]);
		j++;
	}
	pa_tkns[y].cmd_splitted[j] = NULL;
	j = 0;
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
				qte_enc(tmp[k], &trig, &qte);
			if ((qte != 39 && (tmp[k] == '$' && tmp[k + 1] == '?')) || (qte != 39 && (tmp[k] == '$' && ft_isenv(tmp[k + 1]))))
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
					free(res);
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
			else if (tmp[k] == '$' && ft_isqt(tmp[k + 1]) && !trig)
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
}