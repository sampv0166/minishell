#ifndef INPUT_TO_TOKENS_H
#define INPUT_TO_TOKENS_H

#include "env_var.h"

int input_to_tokens(char *input);
/*
** =============================================================================
** Split To Tokens Utils
** =============================================================================
*/
int     create_string_in_between_sngl_quotes(char *str, t_split *split_info);
int   create_string_in_between_dbl_quotes(char *str,t_split *split_info);
void init_split_info(t_split *split_info);
void   inrement_i_len(t_split *split_info);
int    get_arr_len(char *str);
int   skip_and_increment_len_sngl_qts(char *str, int *i, int *len);
int   skip_and_increment_len_dbl_qts(char *str, int *i, int *len);
char *ft_strchr_2(const char *str, int c);

/*
** =============================================================================
** Split By Pipe Redir Utils
** =============================================================================
*/
int get_len(char **arr);
void create_out_redirection_character(char **arr, t_split *split_info, char **tokens);
void create_in_redirection_character(char **arr, t_split *split_info, char **tokens);
void create_pipe_redirection_character(char **arr, t_split *split_info, char **tokens);

/*
** =============================================================================
** Syntax Check Utils
** =============================================================================
*/
bool is_token_syntax_valid (char **tokens);


/*
** =============================================================================
** Parcer utils
** =============================================================================
*/
void set_pa_tokens(t_pars_tokens *pa_tkns, t_parser_info *pa_info);
void allocate_cmd_memmory(t_parser_info *pa_info, char **tokens);
void init_parser_info(t_parser_info *pa_info, char **tokens);


#endif