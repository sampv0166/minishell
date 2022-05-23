/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:31:38 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:31:39 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "env_var.h"

typedef struct s_pars_tokens
{
	char	**cmd;
	char	*cmd_full;
	char	**cmd_splitted;	
	char	**cmd_cpy;
	char	**cmd_rdr;
	int		pipe;
	int		is_in;
	char	**redir;
	int		is_out;	
	int		is_out_appnd;
	int		fd_in;
	int		fd_out;			
	int		here_doc;		
	int		here_doc_fd;
	int		pipe_read_end;	
	int		pipe_write_end;	
}				t_pars_tokens;
char	*get_abs_cmd(char *cmd);
#endif