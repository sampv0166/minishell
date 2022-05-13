#ifndef MINI_SHELL_H
#define MINI_SHELL_H
# define STDERR			2

/*
** =============================================================================
** Colors
** =============================================================================
*/

# define PURPLE "\033[1;35m"
# define BLUE "\033[1;34m"
# define WHITE "\033[1;37m"
# define LIGHT_BLUE "\033[1;36m"
# define GREEN "\033[1;32m"

/*
** =============================================================================
** Headerfiles
** =============================================================================
*/

#include<unistd.h>
#include<stdio.h>
#include "../libft/libft.h"
#include<sys/wait.h>
#include<readline/readline.h>
#include <readline/history.h>
# include <stdbool.h>
#include "./input_to_tokens.h"
#include "./env_var.h"
#include <signal.h>
#include"executor.h"
#include<fcntl.h>


typedef struct	s_flags
{
	int	newl_flag;
	int	print_flag;
	int	i;
	int	qte;
	int	trigger;
	int	end;
	int	rdr_pip_index;
}				t_flags;

typedef struct	s_expand
{
	int		k;
	int		trig;
	int		i;
	int		qte;
}				t_expand;

/*
** =============================================================================
** String Functions
** =============================================================================
*/

char	**ft_2d_str_cpy(char **str);
void	ft_putstr_2d(char **str);
int		length_2d(char **str);
int		last_char(char *str);
int		ft_isqt(char c);
int		check_qte_str(char *str);
int		ft_isenv(char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strstr(char *str, char *to_find);
t_pars_tokens *parser (char **tokens);
void 	ch_home(void);
void	ch_tild(void);
void	delimit_qtes(char *str);

/*
** =============================================================================
** BuiltIn Functions
** =============================================================================
*/

void			free_all(char **str);
 /*
 ** =============================================================================
 ** ECHO
 ** =============================================================================
 */
void			check_qtes(char *tmp, int j, int *i, t_flags *flags);
int				operations(char *tmp, t_flags *flags, int *i);
int				is_rdr_flag(char *str);
void			ft_init(t_flags *flags);
int				check_old_pwd(char **var);
int				check_rdr_pipes(char *str, t_flags *flags);
void 			echo(char **str, char **str_splitted);
 /*
 ** =============================================================================
 ** EXPORT
 ** =============================================================================
 */
char			**declare_s(char **str);
void			exp_one_arg(void);
char			**new_env(char *str);
void			export_new_env(char *var, char *tmp);
int				op_not(char c);
char			*fetch_var(char *var, int *i);
int				export_error(char *value, char *var);
void			replace_env(int g_env, char *var);
int				exp_op(char *var, char *value, int g_env);
int				export(char **str);
 /*
 ** =============================================================================
 ** CD
 ** =============================================================================
 */
void			chge_pwd(char *pwd);
void			chge_old_pwd(char *old_pwd);
int				chge_tilde(char *pwd);
int				chge_c_dir(char *pwd);
int				cd(char **str);
 /*
 ** =============================================================================
 ** PWD
 ** =============================================================================
 */
int				pwd(char **str);
 /*
 ** =============================================================================
 ** ENV
 ** =============================================================================
 */
char			*get_env_dollar(char *str);
int				env_var(void);
 /*
 ** =============================================================================
 ** UNSET
 ** =============================================================================
 */
int				unset(char **str);
 /*
 ** =============================================================================
 ** EXIT
 ** =============================================================================
 */

 int read_buf(char **buf, char **in);

unsigned char 	ft_exit(char **str, int pipe);
int     		is_inbuilt(char *cmd);
int     		ft_perror(int exit_status, char *msg);
int	    		handle_inbuilt_redir(t_pars_tokens *pa_toks,int i);
bool 			token_contains_quote(char *str);

char			**new_env(char *str);
void 			print_2d_array(char **arr);
void 			free_me (char **ptr);
void 			free_2d_array(char **arr);
void			ft_free_str_array(char ***arr);
int 		get_2d_arr_len(char **arr);
int 		get_2d_arr_len2(char **arr);
char		*parse_str(char	*tmp);
void 		expander(t_pars_tokens *pa_tkns);

char **split_to_tokens(char *input);

void	*ft_free_split(char **split);

char **find_input_file_names(t_pars_tokens *pa_tkns, int i);


void init_and_dup_fd();
void init_redir_helper_fds();
void restore_fds();
void close_fds(t_pars_tokens *pa_tkns, int i, int f);
void wait_for_child_and_restore_fds_(pid_t *pid);

char *get_abs_cmd(char *cmd);
static int init(char ***path_splitted, int *i);
char	*ft_strjoin2(char *saved_line, char *buffer);
static char *get_abs_cmd_path(char **abs_cmd_path,char *path_splitted, char *cmd);

void    placing_vals_SHLVL(char *str);
void    increment_s_vals(void);
int execute_cmd(t_pars_tokens *pa_tokens, int i, char **path);

int handle_in_and_here_doc(t_pars_tokens *pa_tkns, int i);

int handle_pipes(t_pars_tokens *pa_tokens, int i);
int  handle_output_redirections(char **cmd_split, t_pars_tokens *pa_tokens, int tkn_idx);
char *set_path(char ***path_split, char **abs_path, char **dup);

void find_cmd(t_pars_tokens *pa_tkns, int i,int *j);
void increment_j(t_pars_tokens *pa_tkns, int i, int *j);

int is_redir(t_pars_tokens *pa_tok, int i);
int set_fds(char **cmd_split,  int *i, int *fd);



void get_cmd_len (t_pars_tokens *pa_tkns,  int i, int *j, int *len);
void get_file_len (t_pars_tokens *pa_tkns,  int i, int *j, int *len);
void close_redir_fd(int *fd);


int	is_rdr(char *str);
int	exit_close_fds(int fd1, int fd2, int exit_status);
int	cmd_w_flags(char *str);
int read_line(char *buf, char **join, int end1, char *heredoc);
int read_here_doc(char **cmd_split, t_parser_info *pa_info, t_pars_tokens *pa_tkns);
void init_pa_tkns(t_pars_tokens *pa_tkns, t_parser_info *pa_info);
void init_pa_tkns_info(t_pars_tokens *pa_tkns, t_parser_info *pa_info);
void set_pipe_type(t_pars_tokens *pa_tkns, t_parser_info *pa_info);
void set_redirection_type(t_pars_tokens *pa_tkns, t_parser_info *pa_info, char **tokens);
/*
 ** =============================================================================
 ** EXPANDER
 ** =============================================================================
 */
char	*get_tild(char *res, char *tmp, t_expand *flags);
char	*parse_for_stat_exp(char *tmp, char *res, t_expand *flags);
char	*get_dir(char *res, char *tmp, t_expand *flags);
char	*expansion_for_str(char *str, t_expand *flags);
char	*get_stat_code(char *res, char *tmp, t_expand *flags);
void	ft_init_exp(t_expand *flags);
char	*getting_tild(void);
void	qte_enc(char c, t_expand *flags);
char	*value_exp(char *dol);
char	*str_cpy(char *res, char *tmp, t_expand *flags);

/*
** =============================================================================
** Signals
** =============================================================================
*/

void	handle_signals(void);
/*
** =============================================================================
** Free Functions
** =============================================================================
*/

void free_split_info(t_split *split_info, t_split *split_infoo, char **tokens);
int free_everything(t_pars_tokens *pa_tkns);
int	is_inbuilt(char *cmd);
#endif