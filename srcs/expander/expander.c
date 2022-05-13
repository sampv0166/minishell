#include "../../includes/mini_shell.h"

extern t_env_var	env;


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
	// char 	**cmd_sp;
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
		free_2d_array(pa_tkns[y].cmd);
	    pa_tkns[y].cmd = ft_2d_str_cpy(full);
		free_2d_array(full);
		y++;
	}
}
