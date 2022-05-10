#include "../../includes/mini_shell.h"

extern t_env_var	env;

static void	ft_init_exp(t_expand *flags)
{
	flags->i = 0;
	flags->k = 0;
	flags->qte = 0;
	flags->trig = 0;
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
	ch_home();
	chdir(pwd);
	free(pwd);
	return (ret);
}

void	qte_enc(char c, t_expand *flags)
{
	if (ft_isqt(c))
	{
		if (flags->trig == 1 && flags->qte == ft_isqt(c))
		{
			flags->qte = 0;
			flags->trig = 0;
		}
		else if (!(flags->qte))
		{
			flags->trig = 1;
			flags->qte = ft_isqt(c);
		}
	}
}

char	*value_exp(char *dol)
{
	char	**ptr;
	int		i;

	i = 1;
	ptr = ft_split(dol, ' ');
	free(dol);
	dol = ft_strdup(ptr[0]);
	while (ptr[i])
	{
		dol = ft_strjoin(dol, " ");
		dol = ft_strjoin(dol, ptr[i]);
		i++;
	}
	free_2d_array(ptr);
	return (dol);
}

char	*str_cpy(char *res, char *tmp, t_expand *flags)
{
	char	*cat;

	cat = ft_strdup(res);
	free(res);
	res = ft_calloc(ft_strlen(cat) + ft_strlen(tmp)
			- flags->k + 1, sizeof(char));
	flags->i = 0;
	while (cat[flags->i])
	{
		res[flags->i] = cat[flags->i];
		flags->i++;
	}
	res[flags->i] = 0;
	free(cat);
	return (res);
}

char	*get_stat_code(char *res, char *tmp, t_expand *flags)
{
	char	*cat;

	flags->k += 2;
	cat = ft_itoa(env.stat_code);
	res = ft_strjoin(res, cat);
	free(cat);
	res = str_cpy(res, tmp, flags);
	return (res);
}

char	*expansion_for_str(char *str, t_expand *flags)
{
	char	*dol;
	char	*cat;
	int		j;

	j = 0;
	cat = ft_strdup(str);
	++j;
	while (ft_isenv(cat[j]))
		j++;
	cat[j] = '\0';
	if (ft_isdigit(str[1]))
		flags->k += 2;
	else
		flags->k += ft_strlen(cat);
	j = get_env(&cat[1]);
	if (env.env_var[j] != NULL)
	{
		dol = get_env_dollar(cat);
		if (!flags->trig)
			dol = value_exp(dol);
		free(cat);
		return (dol);
	}
	free(cat);
	return (NULL);
}

char	*get_dir(char *res, char *tmp, t_expand *flags)
{
	char	*dol;

	dol = getting_tild();
	res = ft_strjoin(res, dol);
	free(dol);
	res = str_cpy(res, tmp, flags);
	return (res);
}

char	*parse_for_stat_exp(char *tmp, char *res, t_expand *flags)
{
	char	*res1;

	res1 = NULL;
	if (tmp[flags->k + 1] == '?')
		res = get_stat_code(res, tmp, flags);
	else
	{
		res1 = expansion_for_str(&tmp[flags->k], flags);
		if (res1 != NULL)
		{	
			res = ft_strjoin(res, res1);
			free(res1);
			res = str_cpy(res, tmp, flags);
		}
	}
	return (res);
}

char	*get_tild(char *res, char *tmp, t_expand *flags)
{
	flags->k++;
	res = get_dir(res, tmp, flags);
	return (res);
}

void	place_values(char *res, char *tmp, t_expand *flags)
{
	res[flags->i] = tmp[flags->k];
	flags->i++;
	flags->k++;
}

static int	check_exp(t_expand *flags, char *tmp)
{
	if ((flags->qte != 39 && (tmp[flags->k] == '$'
				&& tmp[flags->k + 1] == '?')) || (flags->qte != 39
			&& (tmp[flags->k] == '$' && ft_isenv(tmp[flags->k + 1]))))
		return (1);
	return (0);
}

char	*parse_str(char	*tmp)
{
	t_expand	flags;
	char		*res;

	ft_init_exp(&flags);
	res = ft_calloc(ft_strlen(tmp) + 1, sizeof(char));
	while (tmp[flags.k])
	{
		if (ft_isqt(tmp[flags.k]))
			qte_enc(tmp[flags.k], &flags);
		res[flags.i] = '\0';
		if (check_exp(&flags, tmp))
			res = parse_for_stat_exp(tmp, res, &flags);
		else if (tmp[flags.k] == '$' && ft_isqt(tmp[flags.k + 1])
			&& !flags.trig)
			flags.k++;
		else if ((!flags.k || (flags.k > 0 && (tmp[flags.k - 1] != '$')))
			&& (tmp[flags.k] == '~' && (tmp[flags.k + 1] == '/'
					|| tmp[flags.k + 1] == '\0')) && !flags.qte)
			res = get_tild(res, tmp, &flags);
		else
			place_values(res, tmp, &flags);
	}
	res[flags.i] = '\0';
	return (res);
}

char	**get_2d_exp(int y, t_pars_tokens *pa_tkns, int m)
{
	char	*tmp;
	char	*res;
	int		j;
	char	**full;

	full = (char **)malloc(sizeof(char *) * (get_len(pa_tkns[y].cmd) + 1));
	m = 0;
	j = 0;
	res = NULL;
	tmp = NULL;
	while (pa_tkns[y].cmd[j] != NULL)
	{
		tmp = ft_strdup(pa_tkns[y].cmd[j]);
		res = parse_str(tmp);
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
	return (full);
}

char	**get_2d_exp2(int y, t_pars_tokens *pa_tkns, int m)
{
	char	*tmp;
	char	*res;
	int		j;
	char	**full;

	full = (char **)malloc(sizeof(char *) * (get_len(pa_tkns[y].cmd_splitted) + 1));
	m = 0;
	j = 0;
	res = NULL;
	tmp = NULL;
	while (pa_tkns[y].cmd_splitted[j] != NULL)
	{
		tmp = ft_strdup(pa_tkns[y].cmd_splitted[j]);
		res = parse_str(tmp);
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
	return (full);
}

void	expander(t_pars_tokens *pa_tkns)
{
	int 	y;
	char	**full;
	char	**full_splitted;
	char 	**cmd_sp;
	//! SHORTEN THIS CODE!

	y = 0;
	while (y < env.count)
	{
    	pa_tkns[y].cmd_cpy = ft_2d_str_cpy(pa_tkns[y].cmd);
    	full_splitted = get_2d_exp2(y, pa_tkns, 0);
		ft_free_str_array(&pa_tkns[y].cmd_splitted);
    	pa_tkns[y].cmd_splitted = ft_2d_str_cpy(full_splitted);
    	free_2d_array(full_splitted);
		full = get_2d_exp(y, pa_tkns, 0);
		ft_free_str_array(&pa_tkns[y].cmd);
	    pa_tkns[y].cmd = ft_2d_str_cpy(full);
		free_2d_array(full);
		y++;
	}
	// y = 0;
	// pa_tkns[y].cmd_cpy = ft_2d_str_cpy(pa_tkns[y].cmd);
	// full = get_2d_exp(y, pa_tkns, 0);
	// y = 0;
	// cmd_sp = ft_2d_str_cpy(pa_tkns[y].cmd_splitted);
	// full_splitted = get_2d_exp2(y, pa_tkns, 0);
	// /*After succesfully taking all the commands with quotes if present, first we free the old command variable
	// then we duplicate the strings including quotes in our main command variable	and free the full-variable*/
	// free_2d_array(pa_tkns[y].cmd);
	// free_2d_array(pa_tkns[y].cmd_splitted);
	// pa_tkns[y].cmd = ft_2d_str_cpy(full);
	// pa_tkns[y].cmd_splitted = ft_2d_str_cpy(full_splitted);
	// free_2d_array(full);
	// free_2d_array(full_splitted);
	// print_2d_array(pa_tkns[y].cmd);
	// print_2d_array(pa_tkns[y].cmd_splitted);
	// exit(0);
}
