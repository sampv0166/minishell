#ifndef ENV_VAR_H
# define ENV_VAR_H

typedef struct s_env_var
{
    char **envp;
    char **env_var;
    char *pwd;
    char *prev_pwd;
    int   stat_code;
    
}            t_env_var;

/*
** =============================================================================
** ENV VAR FUNCTIONS
** =============================================================================
*/

int init_env_vars(char **envp, t_env_var *env);
char *get_env_value (t_env_var *env, char *var);

#endif