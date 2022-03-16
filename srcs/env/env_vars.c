#include "../../includes/mini_shell.h"

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

char *get_env_value (t_env_var *env, char *var)
{
  int  i;
  char *val;


  i  = 0;
  val = NULL; 

  while (env->env_var[i] != NULL)
  {
    	if (ft_strcmp(var, env->env_var[i]) == -61)
		  {
			  val = ft_strchr(env->env_var[i++], '=') + 1;
			  if (ft_strlen(val) == 0)
				    val = ft_calloc(1, sizeof (char));
			  else
				    val = ft_strdup(val);
			  break ;
		  }
      i++;
  }
  return (val);
}

t_env_var *init_env_vars(char **envp)
{
    t_env_var *env;

    env = malloc (sizeof (t_env_var));
    if(env != NULL)
    {
        env->envp = envp;
        env->env_var = save_env(envp);
        env->pwd = get_env_value(env, "PWD");
        if(env->env_var != NULL)
            return (env);
    }
    return (NULL);
}