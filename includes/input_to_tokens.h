/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_tokens.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:31:35 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:31:36 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_TO_TOKENS_H
# define INPUT_TO_TOKENS_H

# include "env_var.h"

char	**tokens_split(char *input);
int		input_to_tokens(char *input);
/*
** =============================================================================
** Split To Tokens Utils
** =============================================================================
*/
int		create_string_in_between_sngl_quotes(char *str, t_split *split_info);
int		create_string_in_between_dbl_quotes(char *str, t_split *split_info);
void	init_split_info(t_split *split_info);
void	inrement_i_len(t_split *split_info);
int		get_arr_len(char *str);
int		skip_and_increment_len_sngl_qts(char *str, int *i, int *len);
int		skip_and_increment_len_dbl_qts(char *str, int *i, int *len);
char	*ft_strchr_2(const char *str, int c);

/*
** =============================================================================
** Split By Pipe Redir Utils
** =============================================================================
*/
int		get_len(char **arr);
void	create_out_redirection_character(char **arr,
			t_split *split_info, char **tokens);
void	create_in_redirection_character(char **arr,
			t_split *split_info, char **tokens);
void	create_pipe_redirection_character(char **arr,
			t_split *split_info, char **tokens);

/*
** =============================================================================
** Syntax Check Utils
** =============================================================================
*/
bool	token_contains_quote(char *str);
bool	is_token_redir(char *str);
bool	is_token_pipe(char *str);
bool	is_special_charater_correct(char *str);
int		check_pipe_conditions(char **tokens, int i);
bool	is_token_syntax_valid(char **tokens);
/*
** =============================================================================
** Parcer utils
** =============================================================================
*/

int		check_cmds_qtes(char **str);
int		is_rdr(char *str);
void	set_pa_tokens(t_pars_tokens *pa_tkns, t_parser_info *pa_info);
void	allocate_cmd_memmory(t_parser_info *pa_info, char **tokens);
void	init_parser_info(t_parser_info *pa_info, char **tokens);

#endif