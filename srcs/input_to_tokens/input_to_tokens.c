/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:28:44 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:28:45 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

// void	print_strcut(t_pars_tokens *pa_tkns)
// {
// 	int	y;
// 	int j;

// 	y = 0;
// 	while (y < g_env.count)
// 	{
// 		j = 0;
// 		printf("\n struct = %d\n", y);
// 		printf("\n-------------cmd---------------------------\n");
// 		while (pa_tkns[y].cmd[j])
// 		{
// 			printf ("%d: %s ",j , pa_tkns[y].cmd[j]);
// 			j++;
// 		}
// 		printf("\n-------------cmd_splitted---------------------------\n");
// 		j = 0;
// 		while (pa_tkns[y].cmd_splitted[j])
// 		{
// 			printf ("%d: %s ", j, pa_tkns[y].cmd_splitted[j]);
// 			j++;
// 		}
// 		printf("\n-------------cmd_cpy---------------------------\n");
// 		j = 0;
// 		while (pa_tkns[y].cmd_cpy[j])
// 		{
// 			printf ("%d: %s ", j, pa_tkns[y].cmd_cpy[j]);
// 			j++;
// 		}
// 		printf("\n-------------cmd_full---------------------------\n");
// 		printf ("%s ",pa_tkns[y].cmd_full);
// 		printf("\npipe = %d\n", pa_tkns[y].pipe);
// 		printf("\npipe_read_end = %d\n", pa_tkns[y].pipe_read_end);
// 		printf("\npipe_write_end = %d\n", pa_tkns[y].pipe_write_end);
// 		printf("\nis_out = %d\n", pa_tkns[y].is_out);
// 		printf("\nis_append = %d\n", pa_tkns[y].is_out_appnd);
// 		printf("\nis_in = %d\n", pa_tkns[y].is_in);
// 		printf("\nhere_doc = %d\n", pa_tkns[y].here_doc);
// 		printf("\nfd_out = %d\n", pa_tkns[y].fd_out);
// 		y++;
// 	}
// }

int	input_to_tokens(char *input)
{
	t_pars_tokens	*pa_tkns;
	char			**tokens;

	tokens = tokens_split(input);
	if (!tokens)
		return (EXIT_FAILURE);
	pa_tkns = parser(tokens);
	ft_free_str_array(&tokens);
	expander(pa_tkns);
	executor(pa_tkns);
	free_everything(pa_tkns);
	return (g_env.stat_code);
}
