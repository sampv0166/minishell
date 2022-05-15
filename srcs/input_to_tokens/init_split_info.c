#include "../../includes/mini_shell.h"

void	split_by_redirection2(char **arr, char **tokens, t_split *split_info)
{
	split_info->len = ft_strlen (arr[split_info->i]);
	tokens[split_info->k] = ft_strdup(arr[split_info->i]);
	split_info->k++;
}

void	get_len_out_redirection2(char **arr, int *i, int *j, int *size)
{
	if (*j > 0)
	{
		if (arr[*i] && arr[*i][*j] && arr[*i][(*j) - 1]
			&& arr[*i][(*j) - 1] != ' '
			&& arr[*i][(*j) - 1] != '\0')
			(*size)++;
		if (arr[*i][(*j) + 1] != ' ' && arr[*i][(*j) + 1] != '\0')
			(*size)++;
	}
	else
		(*size)++;
}

void	get_len_out_redirection(char **arr, int *i, int *j, int *size)
{
	if (arr[*i] && arr[*i][*j] == '>' && arr[*i][(*j) + 1] == '>')
	{
		if (*j > 0)
		{
			if (arr[*i] && arr[*i][*j] && arr[*i][(*j) - 1] != ' '
				&& arr[*i][(*j) - 1] != '\0' )
				(*size)++;
			while (arr[*i] && arr[*i][*j] == '>')
			{
				if (arr[*i] && arr[*i][*j] && arr[*i][(*j) + 1] != '>')
					break ;
				(*j)++;
			}
			if (arr[*i][(*j) + 1] != ' ' && arr[*i][(*j) + 1] != '\0')
				(*size)++;
		}
		else
			(*size)++;
	}
	else if (arr[*i] && arr[*i][*j] == '>' && arr[*i][(*j) + 1] != '>')
		get_len_out_redirection2(arr, i, j, size);
}

void	init_split_info(t_split *split_info)
{
	split_info->i = 0;
	split_info->array_index = 0;
	split_info->len = 0;
	split_info->brk_flg = 1;
	split_info->k = 0;
	split_info->j = 0;
}
