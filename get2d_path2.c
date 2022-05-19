void	get_2d_path2(t_pars_tokens *pa_tokens, int i)
{
	char	**cpy;
	char	**tmp;
	int		count;
	int		f;
	int		j;

	count = 0;
	j = 0;
	f = 0;
	cpy = ft_2d_str_cpy(pa_tokens[i].cmd);
	while (pa_tokens[i].cmd[f])
	{
		tmp = ft_split(pa_tokens[i].cmd[f], ' ');
		count += get_2d_arr_len2(tmp);
		free_2d_array(tmp);
		f++;
	}
	f = 0;
	free_2d_array(pa_tokens[i].cmd);
	pa_tokens[i].cmd = (char **)malloc(sizeof(char *) * (count + 1));
	count = 0;
	while (cpy[f] != NULL)
	{
		tmp = ft_split(cpy[f], ' ');
		j = 0;
		while (tmp[j] != NULL)
		{
			pa_tokens[i].cmd[count] = ft_strdup(tmp[j]);
			delimit_qtes(pa_tokens[i].cmd[count]);
			count++; 
			j++;
		}
		free_2d_array(tmp);
		f++;
	}
	pa_tokens[i].cmd[count] = NULL;
	free_2d_array(cpy);
}