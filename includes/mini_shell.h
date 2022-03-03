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

/*
** =============================================================================
** String Functions
** =============================================================================
*/
int		ft_strcmp(char *s1, char *s2);

/*
** =============================================================================
** BuiltIn Functions
** =============================================================================
*/
int cd(char *path) ;
int pwd(char *path);
void	echo(char **str);

/*
** =============================================================================
** Signals
** =============================================================================
*/
void	handle_signals(void);

#endif