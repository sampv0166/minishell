/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:31:10 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:31:11 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
/*Checking for double or single quotes, First reason 
is to not print them, Second if there is a double
quote or No quote and there is a $ in a str it should 
fetch the value of the env variable*/
// if (str[flags.i][0] == 39 || str[flags.i][0] == 34)
// 	flags.qte = str[flags.i][0];
/*This  condition checks if I'm encountered with pipes 
or any redirections. If I do it will
break out of while loop and will not print anything*/
// if (check_rdr_pipes(str[flags.i], &flags))
// 	break ;
/*The print_flag to check if Im not encountered with 
any pipe or redirections*/

/*First solve the problem with n flags before we print anything*/

/*If first index of 2d array is finished in printing and the 
second index needs printing, then there should be a
space between both the strings in display*/

/*If n_flag is true, it will not print a new line otherwise it will print*/
void	echo(char **str, char **str_splitted)
{
	t_flags	flags;

	ft_init(&flags);
	flags.i = 1;
	if (str[flags.i])
	{
		flags.i = n_flag_cmp(str, &flags, str_splitted);
		while (str[flags.i] != NULL && flags.i < flags.end)
		{
			flags.print_flag = 0;
			flags.qte = 0;
			if (!flags.print_flag)
				ft_putstr_fd(str[flags.i], g_env.fd_out);
			flags.i++;
			if (str[flags.i] != NULL)
				ft_putchar_fd(' ', g_env.fd_out);
		}
	}
	if (!flags.newl_flag)
		ft_putchar_fd('\n', g_env.fd_out);
}
