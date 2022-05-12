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

char **find_input_file_names(t_pars_tokens *pa_tkns, int i);
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