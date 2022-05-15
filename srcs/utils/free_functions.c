#include "../../includes/mini_shell.h"

int	free_env(void)
{
	ft_free_str_array(&g_env.env_var);
	return (0);
}

int	free_everything(t_pars_tokens *tokens)
{
	int	i;

	i = 0;
	while (g_env.count > 1 && i < g_env.count)
	{
		ft_free_str_array(&tokens[i].cmd);
		ft_free_str_array(&tokens[i].cmd_cpy);
		ft_free_str_array(&tokens[i].cmd_splitted);
		free_me(&tokens[i].cmd_full);
		i++;
	}
	if (g_env.count == 1)
	{
		free_2d_array(tokens[i].cmd);
		ft_free_str_array(&tokens[i].cmd_cpy);
		ft_free_str_array(&tokens[i].cmd_splitted);
		free_me(&tokens[i].cmd_full);
	}
	free(tokens);
	return (0);
}

// void	print_2d_array(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		ft_putstr_fd(arr[i], 2);
// 		ft_putstr_fd("\n", 2);
// 		i++;
// 	}
// }

int	ft_perror(int exit_status, char *msg)
{
	perror(msg);
	return (exit_status);
}

void	*ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		free_me(&split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

// void	print_strcut(t_pars_tokens *pa_tkns)
// {
// 	int	y;
// 	int j;

// 	y = 0;
// 	while (y < env.count)
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
