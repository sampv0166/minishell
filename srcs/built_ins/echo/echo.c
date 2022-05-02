#include "../../../includes/mini_shell.h"

extern t_env_var	env;

static void	print(char *str, t_flags *flags)
{
	int	i;
	int	trig;

	i = 0;
	trig = 0;
	while (str[i])
	{
		if (ft_isqt(str[i]) && !trig)
		{
			flags->qte = str[i];
			trig = 1;
		}
		else if (ft_isqt(str[i]) == flags->qte && trig)
			trig = 0;
		else if (!ft_isqt(str[i]) || ft_isqt(str[i]) != flags->qte)
			ft_putchar_fd(str[i], 1);
		// else if (str[i] == *qte)
		// {
		// 	if (i > 0 && str[i + 1] != '\0')
		// 		ft_putchar_fd(str[i], 1);
		// }
		++i;
	}
}

/*Work with n -flags complications
Examples: -n -n -n -n,  n_flag is false
-nnnnnnnnnnnnnnn, n_flag is true*/

char	*delimit_echo_qtes(char *str, t_flags *flags)
{
	char	*tmp;
	int		k;
	int		j;

	tmp = NULL;
	j = 0;
	k = 0;
	if ((str[0] == 34) || (str[0] == 39))
		flags->qte = str[0];
	k = 0;
	j = 0;
	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[j])
	{
		if (str[j] != flags->qte)
		{
			tmp[k] = str[j];
			k++;
		}
		j++;
	}
	tmp[k] = '\0';
	return (tmp);
}

static int	n_flag_cmp(char **str, t_flags *flags)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 1;
	k = 0;
	j = 0;
	flags->qte = 0;
	tmp = NULL;
	while (str[i] != NULL)
	{
		tmp = delimit_echo_qtes(str[i], flags);
		k = operations(tmp, flags, &i);
		if (flags->trigger)
			return (k);
		free(tmp);
		i++;
	}
	return (i);
}

void echo(char **str)
{
	t_flags	flags;

	ft_init(&flags);
	flags.i = 1;
	if (str[flags.i])
	{
		/*First solve the problem with n flags before we print anything*/
		flags.i = n_flag_cmp(str, &flags);
		while (str[flags.i] != NULL)
		{
			flags.print_flag = 0;
			flags.qte = 0;
			/*Checking for double or single quotes, First reason is to not print them, Second if there is a double
			quote or No quote and there is a $ in a str it should fetch the value of the env variable*/
			if (str[flags.i][0] == 39 || str[flags.i][0] == 34)
				flags.qte = str[flags.i][0];
			else if (last_char(str[flags.i]) == 39
				|| last_char(str[flags.i]) == 34)
				flags.qte = last_char(str[flags.i]);
			/*This  condition checks if I'm encountered with pipes or any redirections. If I do it will
			break out of while loop and will not print anything*/
			if (check_rdr_pipes(str[flags.i], &flags))
				break ;
			/*The print_flag to check if Im not encountered with any pipe or redirections*/
			if (!flags.print_flag)
				print(str[flags.i], &flags);
			flags.i++;
			/*If first index of 2d array is finished in printing and the second index needs printing, then there should be a
			space between both the strings in display*/
			if (str[flags.i] != NULL)
				ft_putchar_fd(' ', 1);
		}
	}
	/*If n_flag is true, it will not print a new line otherwise it will print*/
	if (!flags.newl_flag)
		ft_putchar_fd('\n', 1);
}
