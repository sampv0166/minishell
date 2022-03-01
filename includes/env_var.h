#ifndef ENV_VAR_H
# define ENV_VAR_H


typedef struct s_env_var
{
    char **envp;
    char **env_var;
    char *pwd;
    char *prev_pwd;
    
}            t_env_var;

/*
** =============================================================================
** ENV VAR FUNCTIONS
** =============================================================================
*/

t_env_var *init_env_vars(char **envp);
char *get_env_value (t_env_var *env, char *var);


#endif