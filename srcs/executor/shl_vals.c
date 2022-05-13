
#include "../../includes/mini_shell.h"

extern t_env_var env;

char *set_path(char ***path_split, char **abs_path, char **dup)
{
    ft_free_split(*path_split);
    env.split = *path_split;
    free_me(abs_path);
    return (*dup);
}

void    placing_vals_SHLVL(char *str)
{
    int i;
    char    *tmp;

    i = get_env("SHLVL");
    tmp = NULL;
    if (env.env_var[i] == NULL)
    {
        tmp = ft_strdup("SHLVL=");
        tmp = ft_strjoin(tmp, str);
        env.env_var = new_env(tmp);
        free(tmp);
    }
    else
    {
        free(env.env_var[i]);
        env.env_var[i] = ft_strdup("SHLVL=");
        env.env_var[i] = ft_strjoin(env.env_var[i], str);
    }
    free(str);
}

void    increment_s_vals(void)
{
    int     i;
    char    *tmp;
    char    *str;

    str = NULL;
    tmp = ft_strdup("$");
    tmp = ft_strjoin(tmp, "SHLVL");
    i = get_env("SHLVL");
    if (env.env_var[i] == NULL)
        str = ft_strdup("0");
    else
        str = get_env_dollar(tmp);
    free(tmp);
    i = ft_atoi(str);
    i++;
    free(str);
    str = ft_itoa(i);
    placing_vals_SHLVL(str);
}