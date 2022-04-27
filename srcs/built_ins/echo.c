#include "../../includes/mini_shell.h"

extern t_env_var env;

static void print(char *str, int *qte)
{
	int i;
	int	trig;

	i = 0;
	trig = 0;
	if (!(*qte))
		*qte = 34;
	while (str[i])
	{
		trig = 0;
		if (str[i] == *qte)
			trig = 1;
		else if (!trig && !(!i && str[i] == *qte) && !(str[i + 1] == '\0' && str[i] == *qte))
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

static int n_flag_cmp(char **str, t_flags *flags)
{
	int i;
	int j;
	int	k;
	int	qte;
	char	*tmp;

	i = 1;
	k = 0;
	j = 0;
	qte = 0;
	tmp = NULL;
	while (str[i] != NULL)
	{
		if ((str[i][0] == 34) || (str[i][0] == 39))
			qte = str[i][0];
		k = 0;
		j = 0;
		tmp = ft_calloc(ft_strlen(str[i]) + 1, sizeof(char));
		while (str[i][j])
		{
			if (str[i][j] != qte)
			{
				tmp[k] = str[i][j];
				k++;
			}
			j++;
		}
		tmp[k] = '\0';
		j = 0;
		while (tmp[j])
		{
			if (tmp[j] == '-' && !j && tmp[j + 1] == 'n')
			{
				j++;
				while (tmp[j] == 'n')
					j++;
				if (tmp[j] != '\0')
				{
					if (tmp[j] == 34 || tmp[j] == 39)
					{
						flags->newl_flag = 1;
						i++;
					}
					free(tmp);
					return (i);
				}
				flags->newl_flag = 1;
			}
			else
			{
				free(tmp);
				return (i);
			}
		}
		free(tmp);
		i++;
	}
	return (i);
}

int	is_rdr_flag(char *str)
{
	if (!ft_strcmp(str, "<") && env.pa_tkns->is_in)
		return (1);
	else if (!ft_strcmp(str, ">") && env.pa_tkns->is_out)
		return (1);
	else if (!ft_strcmp(str, ">>") && env.pa_tkns->is_out_appnd)
		return (1);
	else if (!ft_strcmp(str, "<<") && env.pa_tkns->here_doc)
		return (1);
	return (0);
}

void echo(char **str)
{
	int i;
	t_flags flags;
	int qte;
	int	print_f;
	char	*tmp;
	int		trigger;

	i = 1;
	trigger = 0;
	print_f = 0;
	qte = 0;
	tmp = NULL;
	flags.newl_flag = 0;
	if (str[i])
	{
		/*First solve the problem with n flags before we print anything*/
		i = n_flag_cmp(str, &flags);
		while (str[i] != NULL)
		{
			print_f = 0;
			qte = 0;
			/*Checking for double or single quotes, First reason is to not print them, Second if there is a double
			quote or No quote and there is a $ in a str it should fetch the value of the env variable*/
			if (str[i][0] == 39 || str[i][0] == 34)
				qte = str[i][0];
			else if (last_char(str[i]) == 39 || last_char(str[i]) == 34)
				qte = last_char(str[i]);
			/*This  condition checks if I'm encountered with pipes or any redirections. If I do it will
			break out of while loop and will not print anything*/
			if (ft_strchr(str[i], '>') || ft_strchr(str[i], '<') || ft_strchr(str[i], '|'))
			{
				if (is_rdr_flag(str[i]))
				{
					print_f = 1;
					break;
				}
				else if (ft_strchr(str[i], '|'))
				{
					if (!ft_strcmp(str[i], "|") && env.pa_tkns->pipe)
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