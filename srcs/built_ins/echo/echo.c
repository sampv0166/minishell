#include "../../../includes/mini_shell.h"

/*Work with n -flags complications
Examples: -n -n -n -n,  n_flag is false
-nnnnnnnnnnnnnnn, n_flag is true*/

static int	n_flag_cmp(char **str, t_flags *flags, char **str_splitted)
{
	int		i;
	int		k;
	char	*tmp;

	i = 1;
	k = 0;
	flags->qte = 0;
	tmp = NULL;
	i = parse_str_echo(str, str_splitted);
	flags->rdr_pip_index = i;
	flags->end = i;
	i = 1;
	if (str[i][0] == '-')
	{
		while (str[i] != NULL)
		{
			tmp = ft_strdup(str[i]);
			k = operations(tmp, flags, &i);
			if (flags->trigger)
				return (k);
			free(tmp);
			i++;
		}
	}
	return (i);
}

void	echo(char **str, char **str_splitted)
{
	t_flags	flags;

	ft_init(&flags);
	flags.i = 1;
	if (str[flags.i])
	{
		/*First solve the problem with n flags before we print anything*/
		flags.i = n_flag_cmp(str, &flags, str_splitted);
		while (str[flags.i] != NULL && flags.i < flags.end)
		{
			flags.print_flag = 0;
			flags.qte = 0;
			/*Checking for double or single quotes, First reason is to not print them, Second if there is a double
			quote or No quote and there is a $ in a str it should fetch the value of the env variable*/
			// if (str[flags.i][0] == 39 || str[flags.i][0] == 34)
			// 	flags.qte = str[flags.i][0];
			/*This  condition checks if I'm encountered with pipes or any redirections. If I do it will
			break out of while loop and will not print anything*/
			// if (check_rdr_pipes(str[flags.i], &flags))
			// 	break ;
			/*The print_flag to check if Im not encountered with any pipe or redirections*/
			if (!flags.print_flag)
				ft_putstr_fd(str[flags.i], 1);
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
