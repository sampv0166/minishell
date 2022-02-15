#include "../includes/mini_shell.h"

int get_env_arr_len(char **arr)
{
  int len;

  len = 0;
  while (arr && arr[len])
  {
    len++;
  }
  return (len);
}

char **save_env(char **env_var)
{
  char **env_v;
  int i;
  int arr_len;

  i = 0;
  if(env_var == NULL)
    return (NULL);
  arr_len  = get_env_arr_len(env_var);  
  env_v = malloc (sizeof (char *) * arr_len + 1);
  if(env_v == NULL)
    return (NULL);
  while (env_var[i])
  {
    env_v[i] = ft_strdup (env_var[i]);
    i++;
  }
  return (env_v);
}

// TODO : get_env_value(PWD)

t_env_var *init_env_vars(char **envp)
{
    t_env_var *env;

    env = malloc (sizeof (t_env_var));
    if(env != NULL)
    {
        env->envp = envp;
        //copy envp to env.env_var for later use
        env->env_var = save_env(envp);
        if(env->env_var != NULL)
            return (env);
    }
    return (NULL);
}