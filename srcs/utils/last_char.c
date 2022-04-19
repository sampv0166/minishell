int	last_char(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
		i++;
	return (str[i]);
}