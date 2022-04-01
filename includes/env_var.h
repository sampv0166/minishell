#ifndef ENV_VAR_H
# define ENV_VAR_H

#include "executor.h"




typedef struct s_parser_info
{
    int pipes_count;
    int i;
    int k;
    int len;
    char **arr;
    char **arr1;
    char *str;
    int j;
}       t_parser_info;

typedef struct s_env_var
{
    char **envp;
    char **env_var;
    char *pwd;
    char *prev_pwd;
    int   stat_code;
    int count;
    t_pars_tokens *pa_tkns;
    t_parser_info *pa_info;
}            t_env_var;

/*
** =============================================================================
** ENV VAR FUNCTIONS
** =============================================================================
*/

void init_env_vars(char **envp);
char *get_env_value (char *var);

int executor(t_pars_tokens *pa_tkns);
#endif