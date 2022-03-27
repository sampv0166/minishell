#ifndef ENV_VAR_H
# define ENV_VAR_H

typedef struct s_env_var
{
    char **envp;
    char **env_var;
    char *pwd;
    char *prev_pwd;
    int   stat_code;

    int count ;
    
}            t_env_var;

/*
** =============================================================================
** ENV VAR FUNCTIONS
** =============================================================================
*/

void init_env_vars(char **envp);
char *get_env_value (char *var);

#endif