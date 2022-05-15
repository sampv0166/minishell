#include "../../includes/mini_shell.h"

int	read_buf(char **buf, char **in)
{
	*buf = readline("");
	if (*buf == NULL)
	{
		free_me(in);
		return (1);
	}
	return (0);
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

void	get_len_in_redirection2(char **arr, int *i, int *j, int *size)
{
	if (*j > 0)
	{
		if (arr[*i][(*j) - 1] != ' ' && arr[*i][(*j) - 1] != '\0')
			(*size)++;
		if (arr[*i][(*j) + 1] != ' ' && arr[*i][(*j) + 1] != '\0')
			(*size)++;
	}
	else
		(*size)++;
}

void	get_len_in_redirection(char **arr, int *i, int *j, int *size)
{
	if (arr[*i] && arr[*i][*j] && arr[*i][*j] == '<'
		&& arr[*i][(*j) + 1] == '<')
	{
		if (*j > 0)
		{
			if (arr[*i][(*j) - 1] != ' ' && arr[*i][(*j) - 1] != '\0')
			(*size)++;
			while (arr[*i][*j] == '<')
			{
				if (arr[*i] && arr[*i][*j] && arr[*i][(*j) + 1] != '<')
					break ;
				(*j)++;
			}
			if (arr[*i][(*j) + 1] != ' ' && arr[*i][(*j) + 1] != '\0')
				(*size)++;
		}
		else
			(*size)++;
	}
	else if (arr[*i] && arr[*i][*j] == '<' && arr[*i][(*j) + 1] != '<')
		get_len_in_redirection2(arr, i, j, size);
}

void	get_len_pipe(char **arr, int *i, int *j, int *size)
{
	if (arr[*i] && (arr[*i][*j] == '|'))
	{
		if (*j > 0)
		{
			if (arr[*i] && arr[*i][*j] && (arr[*i][(*j) - 1] != ' '
				&& arr[*i][(*j) - 1] != '\0'))
				(*size)++;
		}
		while (arr[*i][*j] == '|')
		{
			if (arr[*i] && arr[*i][*j] && arr[*i][(*j) + 1] != '|')
				break ;
			(*j)++;
		}
		if (arr[*i][(*j) + 1] != ' ' && arr[*i][(*j) + 1] != '\0')
			(*size)++;
	}
}

/*
    ! why this function ?  
    count how many arrays needed to store tokens if redirections and pipe are not seperated by space
    !expected input : char **arr   
    echo "hello world" > file  |  wc -l
    1       2          3  4    5  6   7
    ! expected output : int len
    7
*/
int	get_len(char **arr)
{
	int	size;
	int	i;
	int	j;

	size = 0;
	i = 0;
	j = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i] && (arr[i][j]))
		{
			get_len_out_redirection(arr, &i, &j, &size);
			get_len_in_redirection(arr, &i, &j, &size);
			get_len_pipe(arr, &i, &j, &size);
			j++;
		}
		size++;
		i++;
	}
	return (size);
}
