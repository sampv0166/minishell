#include "../../../includes/mini_shell.h"

extern t_env_var	env;

static void	print(char *str, t_flags *flags)
{
	ft_putstr_fd(str, 1);
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
	while (str[k])
	{
		if (ft_isqt(str[k]))
		{
			flags->qte = str[k];
			break;
		}
		k++;
	}
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

static int	n_flag_cmp(char **str, t_flags *flags, char **str_splitted)
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
		if (!ft_strstr(str[i], "-n"))
		{
			j = i;
			while (str[j] != NULL)
			{
				if (check_qte_str(str_splitted[j]))
				{
					tmp = delimit_echo_qtes(str[j], flags);
					free(str[j]);
					str[j] = ft_strdup(tmp);
					free(tmp);
				}
				j++;
			}
			return (i);
		}
		tmp = delimit_echo_qtes(str[i], flags);
		free(str[i]);
		str[i] = ft_strdup(tmp);
		k = operations(tmp, flags, &i);
		if (flags->trigger)
			return (k);
		free(tmp);
		i++;
	}
	return (i);
}

void echo(char **str, char **str_splitted)
{
	t_flags	flags;

	ft_init(&flags);
	flags.i = 1;
	if (str[flags.i])
	{
		/*First solve the problem with n flags before we print anything*/
		flags.i = n_flag_cmp(str, &flags, str_splitted);
		while (str[flags.i] != NULL)
		{
			flags.print_flag = 0;
			flags.qte = 0;
			/*Checking for double or single quotes, First reason is to not print them, Second if there is a double
			quote or No quote and there is a $ in a str it should fetch the value of the env variable*/
			// if (str[flags.i][0] == 39 || str[flags.i][0] == 34)
			// 	flags.qte = str[flags.i][0];
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