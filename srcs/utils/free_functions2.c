#include "../../includes/mini_shell.h"

void	ft_free_str_array(char ***arr)
{
	int	i;

	i = 0;
	while (*arr && (*arr)[i])
	{
		free_me(&(*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

// void	free_split_info(t_split *split_info,
// 	t_split *split_infoo, char **tokens)
// {
// 	ft_free_str_array(&split_info->arr);
// 	ft_free_str_array(&tokens);
// }

void	free_me(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}
