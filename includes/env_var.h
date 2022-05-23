/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:31:41 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:52:52 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_H
# define ENV_VAR_H

# include "executor.h"

typedef struct s_split
{
	char	**arr;
	size_t	i;
	size_t	array_index;
	int		len;
	int		brk_flg;
	int		k;
	int		j;
}				t_split;

typedef struct s_parser_info
{
	int		pipes_count;
	int		i;
	int		k;
	int		len;
	char	**arr;
	char	**arr1;
	char	*str;
	int		j;
}				t_parser_info;

typedef struct s_env_var
{
	char			**envp;
	char			**env_var;
	char			*pwd;
	char			*prev_pwd;
	int				stat_code;
	int				count;
	t_pars_tokens	*pa_tkns;
	t_parser_info	*pa_info;
	t_split			*split_info;
	char			**split;
	int				trigger;
	int				tmp_in;
	int				tmp_out;
	int				fd_in;
	int				fd_out;
	int				open_fd_in;
	int				open_fd_out;
	int				open_heredoc_fdin;
	int				fd_pipe_out_open;
	int				fd_pipe_in_open;
	int				s_pid;
	int				here_doc;
	int				n_trig;
}				t_env_var;

/*
** =============================================================================
** ENV VAR FUNCTIONS
** =============================================================================
*/

int		init_env_vars(char **envp);
char	*get_env_value(char *var);
int		free_env(void);
int		executor(t_pars_tokens *pa_tkns);
int		get_env(char *str);
#endif