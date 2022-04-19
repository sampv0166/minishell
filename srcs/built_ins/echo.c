#include "../../includes/mini_shell.h"

extern t_env_var env;

static void print(char *str, int *qte)
{
	int i;
	int	len;
	char *val;
	char	*cat;
	int	j;

	i = 0;
	len = 0;
	cat = NULL;
	j = 0;
	if (!(*qte))
		*qte = 34;
	while (str[i])
	{
		if ((str[i] == '$' && (ft_isenv(str[i + 1]) || str[i + 1] == '?')) && *qte == 34)
		{
			cat = get_env_dollar(&str[i]);
			if (cat != NULL)
			{
				ft_putstr_fd(cat, 1);
				free(cat);
			}
			++i;
			while (ft_isenv(str[i]) || str[i] == '?')
				++i;
		}
		else
		{
			if (!(!i && str[i] == *qte) && !(str[i + 1] == '\0' && str[i] == *qte))
				ft_putchar_fd(str[i], 1);
			// else if (str[i] == *qte)
			// {
			// 	if (i > 0 && str[i + 1] != '\0')
			// 		ft_putchar_fd(str[i], 1);
			// }
			++i;
		}
	}
}

/*Work with n -flags complications
Examples: -n -n -n -n,  n_flag is false
-nnnnnnnnnnnnnnn, n_flag is true*/

static int n_flag_cmp(char **str, t_flags *flags)
{
	int i;
	int j;

	i = 1;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '-' && !j)
			{
				j++;
				while (str[i][j] == 'n')
					j++;
				if (str[i][j] != '\0')
					return (i);
				flags->newl_flag = 1;
			}
			else
				return (i);
		}
		i++;
	}
	return (i);
}

void echo(char **str)
{
	int i;
	t_flags flags;
	int qte;
	int	print_f;


	i = 1;
	print_f = 0;
	qte = 0;
	flags.newl_flag = 0;
	if (str[i])
	{
		/*First solve the problem with n flags before we print anything*/
		i = n_flag_cmp(str, &flags);
		while (str[i] != NULL)
		{
			print_f = 0;
			/*Checking for double or single quotes, First reason is to not print them, Second if there is a double
			quote or No quote and there is a $ in a str it should fetch the value of the env variable*/
			if (str[i][0] == 39 || str[i][0] == 34)
				qte = str[i][0];
			/*This  condition checks if I'm encountered with pipes or any redirections. If I do it will
			break out of while loop and will not print anything*/
			if (ft_strchr(str[i], '>') || ft_strchr(str[i], '<') || ft_strchr(str[i], '|'))
			{
				if (is_rdr(str[i]))
				{
					print_f = 1;
					break;
				}
				else if (ft_strchr(str[i], '|'))
				{
					if (!ft_strcmp(str[i], "|"))
					{
						print_f = 1;
						break;
					}
				}
			}
			/*The print_flag to check if Im not encountered with any pipe or redirections*/
			if (!print_f)
				print(str[i], &qte);
			i++;
			/*If first index of 2d array is finished in printing and the second index needs printing, then there should be a
			space between both the strings in display*/
			if (str[i] != NULL)
				ft_putchar_fd(' ', 1);
		}
	}
	/*If n_flag is true, it will not print a new line otherwise it will print*/
	if (!flags.newl_flag)
		ft_putchar_fd('\n', 1);
}