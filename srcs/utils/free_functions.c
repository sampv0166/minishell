#include "../../includes/mini_shell.h"

extern t_env_var env;

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

void free_split_info(t_split *split_info, t_split *split_infoo, char **tokens)
{
    ft_free_str_array(&split_info->arr);
    ft_free_str_array(&tokens);
}

void free_me (char **ptr)
{
    free(*ptr);
    *ptr = NULL;
}

void free_2d_array(char **arr)
{
    int i;

    i = 0;
    while(arr[i] != NULL)
    {
        free(arr[i]);
		arr[i] = NULL;
        i++;
    }
	free(arr); 
}

int free_env()
{
    ft_free_str_array(&env.env_var);
    // if (env.pwd)
    //     free_me (&env.pwd); 
    return (0);         
}

int free_everything(t_pars_tokens *tokens)
{
    int i;

    i = 0;
    while(env.count > 1 && i < env.count)
    {
		ft_free_str_array(&tokens[i].cmd);
        ft_free_str_array(&tokens[i].cmd_cpy);
		ft_free_str_array(&tokens[i].cmd_splitted);
        // free_2d_array(env.pa_tkns[i].cmd_cpy);
        // free_2d_array(env.pa_tkns[i].cmd_splitted);
        free_me(&tokens[i].cmd_full);
		// printf("%d\n", i);
        i++;
    }
    if (env.count == 1)
    {
		free_2d_array(tokens[i].cmd);
        ft_free_str_array(&tokens[i].cmd_cpy);
       ft_free_str_array(&tokens[i].cmd_splitted);
        free_me(&tokens[i].cmd_full);
    }
    //free(tokens);
    free(tokens);
    // free(tokens);
    return (0);
}


void print_2d_array(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        ft_putstr_fd(arr[i], 2);
         ft_putstr_fd("\n", 2);
        i++;
    }
}


int ft_perror(int exit_status, char *msg)
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

void print_strcut(t_pars_tokens *pa_tkns)
{
    int y;
    y = 0;
    while (y < env.count)
    {
        int j;
        j = 0;
        printf("\n struct = %d\n", y);
        printf("\n-------------cmd---------------------------\n");
        while (pa_tkns[y].cmd[j])
        {
            printf ("%d: %s ",j , pa_tkns[y].cmd[j]);
            j++;
        }
        printf("\n-------------cmd_splitted---------------------------\n");
        j = 0;
        while (pa_tkns[y].cmd_splitted[j])
        {
            printf ("%d: %s ", j, pa_tkns[y].cmd_splitted[j]);
            j++;
        }
		printf("\n-------------cmd_cpy---------------------------\n");
        j = 0;
        while (pa_tkns[y].cmd_cpy[j])
        {
            printf ("%d: %s ", j, pa_tkns[y].cmd_cpy[j]);
            j++;
        }
        printf("\n-------------cmd_full---------------------------\n");
        printf ("%s ",pa_tkns[y].cmd_full);
        printf("\npipe = %d\n", pa_tkns[y].pipe);
        printf("\npipe_read_end = %d\n", pa_tkns[y].pipe_read_end);
        printf("\npipe_write_end = %d\n", pa_tkns[y].pipe_write_end);
        printf("\nis_out = %d\n", pa_tkns[y].is_out);
        printf("\nis_append = %d\n", pa_tkns[y].is_out_appnd);
        printf("\nis_in = %d\n", pa_tkns[y].is_in);
        printf("\nhere_doc = %d\n", pa_tkns[y].here_doc);
        printf("\nfd_out = %d\n", pa_tkns[y].fd_out);
        y++;
    }
}
